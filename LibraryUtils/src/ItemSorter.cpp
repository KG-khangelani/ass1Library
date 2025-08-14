#include "LibraryUtils/Sorting/ItemSorter.h"
#include <algorithm>
#include "book.h"
#include "magazine.h"

using std::sort;

namespace LibraryUtils
{
    namespace Sorting
    {

        void ItemSorter::sortBooks(QList<Book> &items, const QString &sortBy)
        {
            if (sortBy == "title")
            {
                sort(items.begin(), items.end(), [](const Book &a, const Book &b)
                     { return a.getTitle() < b.getTitle(); });
            }
            else if (sortBy == "author")
            {
                sort(items.begin(), items.end(), [](const Book &a, const Book &b)
                     { return a.getAuthor() < b.getAuthor(); });
            }
        }

        void ItemSorter::sortMagazines(QList<Magazine> &items, const QString &sortBy)
        {
            if (sortBy == "title")
            {
                sort(items.begin(), items.end(), [](const Magazine &a, const Magazine &b)
                     { return a.getTitle() < b.getTitle(); });
            }
            else if (sortBy == "issue")
            {
                sort(items.begin(), items.end(), [](const Magazine &a, const Magazine &b)
                     { return a.getIssueNo() < b.getIssueNo(); });
            }
        }

    } // namespace Sorting
} // namespace LibraryUtils
