#pragma once
#include <QList>
#include <QString>

class Book;

namespace LibraryUtils
{
    namespace Searching
    {

        class BookSearch
        {
        public:
            static QList<Book> byTitle(const QList<Book> &items, const QString &titleLower);
            static QList<Book> byAuthor(const QList<Book> &items, const QString &authorLower);
            static QList<Book> byId(const QList<Book> &items, const QString &idLower);
        };

    } // namespace Searching
} // namespace LibraryUtils
