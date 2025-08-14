#pragma once
#include <QString>
#include <QList>

class Book;
class Magazine;

namespace LibraryUtils
{
    namespace Sorting
    {

        class ItemSorter
        {
        public:
            static void sortBooks(QList<Book> &items, const QString &sortBy);
            static void sortMagazines(QList<Magazine> &items, const QString &sortBy);
        };

    } // namespace Sorting
} // namespace LibraryUtils
