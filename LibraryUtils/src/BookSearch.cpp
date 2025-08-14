#include "LibraryUtils/Searching/BookSearch.h"
#include "book.h"

namespace LibraryUtils
{
    namespace Searching
    {

        QList<Book> BookSearch::byTitle(const QList<Book> &items, const QString &titleLower)
        {
            QList<Book> out;
            for (const Book &b : items)
                if (b.getTitle().toLower() == titleLower)
                    out.append(b);
            return out;
        }

        QList<Book> BookSearch::byAuthor(const QList<Book> &items, const QString &authorLower)
        {
            QList<Book> out;
            for (const Book &b : items)
                if (b.getAuthor().toLower() == authorLower)
                    out.append(b);
            return out;
        }

        QList<Book> BookSearch::byId(const QList<Book> &items, const QString &idLower)
        {
            QList<Book> out;
            for (const Book &b : items)
                if (b.getID().toLower() == idLower)
                    out.append(b);
            return out;
        }

    } // namespace Searching
} // namespace LibraryUtils
