#include "library.h"
#include <iostream>
#include <QApplication>
#include <string>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QToolBar>
#include <QPushButton>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Library Management System");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setOrganizationDomain("librarymanagementsystem.com");

    Library ithala_lencwadi = Library();

    // Simple GUI window to verify Widgets setup
    QMainWindow w;
    w.setWindowTitle("Ithala Lencwadi by Khangelani");
    w.resize(800, 600);

    QLabel *label = new QLabel("Ithala Lencwadi");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px; font-weight: bold;");
    w.setCentralWidget(label);

    QListWidget *listWidget = new QListWidget();
    listWidget->setSpacing(4);
    listWidget->setUniformItemSizes(false);

    QListView *listView = new QListView();
    listView->setSpacing(4);
    listView->setUniformItemSizes(false);
    listView->setModel(new QSortFilterProxyModel());

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(listView);
    w.setCentralWidget(listWidget);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(listView->model());
    listView->setModel(proxyModel);

    QLineEdit *searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Search...");
    // searchBox->setStyleSheet("padding: 5px; font-size: 14px; border: 1px solid #ccc; border-radius: 4px;");
    searchBox->setMinimumSize(QSize(200, 30));
    layout->addWidget(searchBox);

    QPushButton *addButton = new QPushButton("Add Book");
    addButton->setToolTip("Add a new book to the library");
    addButton->setStyleSheet("background-color: lightblue; color: black; font-weight: bold;");
    addButton->setMinimumSize(QSize(100, 30));
    QPushButton *removeButton = new QPushButton("Remove Book");
    QPushButton *editButton = new QPushButton("Edit Book");

    QToolBar *toolbar = w.addToolBar("Main Toolbar");
    toolbar->addWidget(searchBox);
    toolbar->addWidget(addButton);
    toolbar->setMinimumSize(QSize(800, 40));
    toolbar->setMovable(false);
    // toolbar->setStyleSheet("background-color: #f0f0f0;");
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->addWidget(searchBox);
    toolbarLayout->addWidget(addButton);
    toolbarLayout->addWidget(removeButton);
    toolbarLayout->addWidget(editButton);
    toolbarLayout->setSpacing(4);
    toolbar->setLayout(toolbarLayout);

    for (Book &book : ithala_lencwadi.getBooksCatalogue())
    {
        QListWidgetItem *listWidgetItem = new QListWidgetItem(book.getTitle());
        listWidget->addItem(listWidgetItem);

        QWidget *row = new QWidget(listWidget);
        QVBoxLayout *v = new QVBoxLayout(row);
        // v->setContentsMargins(10, 8, 10, 8);
        v->setSpacing(2);

        QLabel *titleLabel = new QLabel(book.getTitle(), row);
        QFont tf = titleLabel->font();
        tf.setPointSize(11);
        tf.setBold(true);
        titleLabel->setFont(tf);
        v->addWidget(titleLabel);

        QLabel *authorLabel = new QLabel(book.getAuthor(), row);
        QFont af = authorLabel->font();
        af.setPointSize(11);
        // authorLabel->setSizeHint(QSize(0, 20));
        authorLabel->setFont(af);
        v->addWidget(authorLabel);

        QLabel *genreLabel = new QLabel(book.getGenre(), row);
        QFont gf = genreLabel->font();
        gf.setPointSize(11);
        genreLabel->setFont(gf);
        v->addWidget(genreLabel);

        QHBoxLayout *hl = new QHBoxLayout();
        hl->setSpacing(2);
        hl->addWidget(genreLabel);
        hl->addWidget(authorLabel);
        // genreLabel->setLayout(hl);
        v->addLayout(hl);

        listWidgetItem->setSizeHint(row->sizeHint());
        listWidget->setItemWidget(listWidgetItem, row);
    }
    w.setCentralWidget(listWidget);
    w.show();
    return app.exec();
}
