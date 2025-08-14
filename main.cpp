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
