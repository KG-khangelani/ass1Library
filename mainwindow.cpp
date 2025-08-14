#include "mainwindow.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QDate>
#include <QUuid>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buildUi();
    refreshTable();
}

void MainWindow::buildUi()
{
    setWindowTitle("Ithala Lencwadi - Library");
    resize(1000, 700);

    central = new QWidget(this);
    auto *root = new QVBoxLayout(central);

    // Top: search and actions
    auto *topRow = new QHBoxLayout();
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search by title/author/ID...");
    searchBtn = new QPushButton("Search", this);
    borrowBtn = new QPushButton("Borrow", this);
    returnBtn = new QPushButton("Return", this);
    borrowBtn->setEnabled(false);
    returnBtn->setEnabled(false);

    topRow->addWidget(searchEdit);
    topRow->addWidget(searchBtn);
    topRow->addStretch();
    topRow->addWidget(borrowBtn);
    topRow->addWidget(returnBtn);

    // Middle: table view with model + proxy
    model = new QStandardItemModel(this);
    model->setColumnCount(6);
    model->setHorizontalHeaderLabels({"Type", "ID", "Title", "Author", "Extra", "Borrowed"});

    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxy->setDynamicSortFilter(true);

    tableView = new QTableView(this);
    tableView->setModel(proxy);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Bottom: add item form
    auto *formGroup = new QGroupBox("Add Book or Magazine", this);
    formLayout = new QFormLayout(formGroup);

    typeCombo = new QComboBox(this);
    typeCombo->addItems({"Book", "Magazine"});

    titleEdit = new QLineEdit(this);
    authorEdit = new QLineEdit(this);

    extraLabel = new QLabel("Genre", this);
    genreEdit = new QLineEdit(this);
    issueSpin = new QSpinBox(this);
    issueSpin->setRange(0, 100000);
    issueSpin->setVisible(false); // default is Book

    addBtn = new QPushButton("Add", this);

    formLayout->addRow("Type", typeCombo);
    // ID is auto-generated; no input field needed
    formLayout->addRow("Title", titleEdit);
    formLayout->addRow("Author", authorEdit);
    formLayout->addRow(extraLabel, genreEdit); // switches to issueSpin for magazines
    formLayout->addRow("", addBtn);

    // Wire up signals
    connect(typeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onTypeChanged(int)));
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddItem);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::applyFilter);
    connect(borrowBtn, &QPushButton::clicked, this, &MainWindow::onBorrow);
    connect(returnBtn, &QPushButton::clicked, this, &MainWindow::onReturn);
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);

    // Compose
    root->addLayout(topRow);
    root->addWidget(tableView);
    root->addWidget(formGroup);

    setCentralWidget(central);
}

void MainWindow::onTypeChanged(int idx)
{
    const bool isBook = (idx == 0);
    if (isBook)
    {
        extraLabel->setText("Genre");
        if (formLayout)
        {
            int row = -1;
            QFormLayout::ItemRole role = QFormLayout::FieldRole;
            formLayout->getWidgetPosition(issueSpin, &row, &role);
            if (row >= 0)
            {
                formLayout->setWidget(row, QFormLayout::FieldRole, genreEdit);
            }
        }
        genreEdit->setVisible(true);
        issueSpin->setVisible(false);
    }
    else
    {
        extraLabel->setText("Issue #");
        if (formLayout)
        {
            int row = -1;
            QFormLayout::ItemRole role = QFormLayout::FieldRole;
            formLayout->getWidgetPosition(genreEdit, &row, &role);
            if (row >= 0)
            {
                formLayout->setWidget(row, QFormLayout::FieldRole, issueSpin);
            }
        }
        genreEdit->setVisible(false);
        issueSpin->setVisible(true);
    }
}

void MainWindow::refreshTable()
{
    // Gather items from library and populate model
    const auto books = library.getBooksCatalogue();
    const auto mags = library.getMagazinesCatalogue();
    model->setRowCount(0);

    auto appendRow = [&](const QList<QStandardItem *> &row)
    {
        model->appendRow(row);
    };

    for (const auto &b : books)
    {
        QList<QStandardItem *> row;
        row << new QStandardItem("Book")
            << new QStandardItem(b.getID())
            << new QStandardItem(b.getTitle())
            << new QStandardItem(b.getAuthor())
            << new QStandardItem(b.getGenre())
            << new QStandardItem(b.getIsBorrowed() ? "Yes" : "No");
        appendRow(row);
    }
    for (const auto &m : mags)
    {
        QList<QStandardItem *> row;
        row << new QStandardItem("Magazine")
            << new QStandardItem(m.getID())
            << new QStandardItem(m.getTitle())
            << new QStandardItem(m.getAuthor())
            << new QStandardItem(QString::number(m.getIssueNo()))
            << new QStandardItem(m.getIsBorrowed() ? "Yes" : "No");
        appendRow(row);
    }
    tableView->resizeColumnsToContents();
    onSelectionChanged();
}

void MainWindow::applyFilter(const QString &text)
{
    // Use proxy to filter across all columns
    QRegularExpression rx(QRegularExpression::escape(text), QRegularExpression::CaseInsensitiveOption);
    proxy->setFilterRegularExpression(rx);
    proxy->setFilterKeyColumn(-1); // all columns
}

void MainWindow::onAddItem()
{
    const bool isBook = (typeCombo->currentIndex() == 0);
    if (isBook)
    {
        QJsonObject obj;
        const QString id = library.generateUniqueId(true);
        obj.insert("id", id);
        obj.insert("title", titleEdit->text());
        obj.insert("author", authorEdit->text());
        obj.insert("genre", genreEdit->text());
        obj.insert("isBorrowed", false);
        Book b(obj);
        if (!library.addBook(b))
        {
            QMessageBox::warning(this, "Duplicate", "Book exists.");
            return;
        }
        // Optionally notify user; kept silent to avoid blocking dialogs
    }
    else
    {
        QJsonObject obj;
        const QString id = library.generateUniqueId(false);
        obj.insert("id", id);
        obj.insert("title", titleEdit->text());
        obj.insert("author", authorEdit->text());
        obj.insert("issueNumber", QString::number(issueSpin->value()));
        obj.insert("isBorrowed", false);
        Magazine m(obj);
        if (!library.addMagazine(m))
        {
            QMessageBox::warning(this, "Duplicate", "Magazine exists.");
            return;
        }
        // Optionally notify user; kept silent to avoid blocking dialogs
    }
    // Clear fields and refresh
    titleEdit->clear();
    authorEdit->clear();
    if (typeCombo->currentIndex() == 0)
    {
        genreEdit->clear();
    }
    else
    {
        issueSpin->setValue(0);
    }
    titleEdit->setFocus();
    refreshTable();
}

void MainWindow::onSearch()
{
    applyFilter(searchEdit->text());
}

void MainWindow::onBorrow()
{
    auto sel = tableView->selectionModel()->selectedRows();
    if (sel.isEmpty())
        return;
    const QModelIndex proxyIndex = sel.first();
    const QModelIndex srcIndex = proxy->mapToSource(proxyIndex);
    const QString id = model->item(srcIndex.row(), 1)->text();
    const QString type = model->item(srcIndex.row(), 0)->text();

    const bool isBook = (type == "Book");
    library.borrowById(id, isBook);
    refreshTable();
}

void MainWindow::onReturn()
{
    auto sel = tableView->selectionModel()->selectedRows();
    if (sel.isEmpty())
        return;
    const QModelIndex proxyIndex = sel.first();
    const QModelIndex srcIndex = proxy->mapToSource(proxyIndex);
    const QString id = model->item(srcIndex.row(), 1)->text();
    const QString type = model->item(srcIndex.row(), 0)->text();

    const bool isBook = (type == "Book");
    library.returnById(id, isBook);
    refreshTable();
}

void MainWindow::onSelectionChanged()
{
    auto sel = tableView->selectionModel() ? tableView->selectionModel()->selectedRows() : QModelIndexList{};
    if (sel.isEmpty())
    {
        borrowBtn->setEnabled(false);
        returnBtn->setEnabled(false);
        return;
    }
    const QModelIndex proxyIndex = sel.first();
    const QModelIndex srcIndex = proxy->mapToSource(proxyIndex);
    const QString borrowed = model->item(srcIndex.row(), 5)->text();
    const bool isBorrowed = borrowed.compare("Yes", Qt::CaseInsensitive) == 0;
    borrowBtn->setEnabled(!isBorrowed);
    returnBtn->setEnabled(isBorrowed);
}
