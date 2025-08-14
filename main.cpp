#include <QApplication>
#include <QString>
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Library Management System");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setOrganizationDomain("librarymanagementsystem.com");

    MainWindow w;
    w.show();
    return app.exec();
}
