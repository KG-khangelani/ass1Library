#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include "library.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onTypeChanged(int idx);
    void onAddItem();
    void onSearch();
    void onBorrow();
    void onReturn();
    void onSelectionChanged();

private:
    void buildUi();
    void refreshTable();
    void applyFilter(const QString &text);

    // UI elements
    QWidget *central = nullptr;
    QTableView *tableView = nullptr;
    QStandardItemModel *model = nullptr;
    QSortFilterProxyModel *proxy = nullptr;
    QComboBox *typeCombo = nullptr;
    QLineEdit *titleEdit = nullptr;
    QLineEdit *authorEdit = nullptr;
    QLabel *extraLabel = nullptr;
    QLineEdit *genreEdit = nullptr; // for Book
    QSpinBox *issueSpin = nullptr;  // for Magazine
    QLineEdit *searchEdit = nullptr;
    QPushButton *addBtn = nullptr;
    QPushButton *searchBtn = nullptr;
    QPushButton *borrowBtn = nullptr;
    QPushButton *returnBtn = nullptr;
    QFormLayout *formLayout = nullptr; // form used for add item

    // Data
    Library library;
};

#endif // MAINWINDOW_H
