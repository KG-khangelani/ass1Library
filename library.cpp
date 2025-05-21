// #include <iostream>
#include "library.h"
#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QJsonValueRef>

using namespace std;

Library::Library() {}

void Library::loadData(QString &path) {
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open: " << path;
            return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    if (!doc.isArray()) {
        qWarning() << "Expected JSON array in: " << path;
        return;
    }

    for (QJsonValueRef item : doc.array()) {
        // list
    }

}
