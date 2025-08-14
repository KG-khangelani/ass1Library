#pragma once
#include <QString>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class Book;
class Magazine;

namespace LibraryUtils
{
    namespace Persistence
    {

        class FileStorage
        {
        public:
            static bool loadAll(const QString &filePath, QList<Book> &books, QList<Magazine> &mags);
            static bool saveAll(const QString &filePath, const QList<Book> &books, const QList<Magazine> &mags);

        private:
            static QJsonArray toJsonArray(const QList<Book> &books, const QList<Magazine> &mags);
        };

    } // namespace Persistence
} // namespace LibraryUtils
