#ifndef LIBRARYUTILS_STORAGE_STORAGE_H
#define LIBRARYUTILS_STORAGE_STORAGE_H

#include <QList>
#include <QString>
#include <type_traits>
#include <algorithm>

#include "libraryitem.h"

namespace LibraryUtils
{
    namespace StorageNS
    { // Avoid clash with std::storage, etc.

        // A lightweight, header-only container for managing LibraryItem-derived objects.
        // T must publicly derive from LibraryItem.
        template <typename T>
        class Storage
        {
            static_assert(std::is_base_of<LibraryItem, T>::value,
                          "Storage<T>: T must derive from LibraryItem");

        public:
            using Container = QList<T>;
            using iterator = typename Container::iterator;
            using const_iterator = typename Container::const_iterator;

            Storage() = default;

            // Add item if an item with the same ID doesn't exist. Returns true if added.
            bool add(const T &item)
            {
                if (containsId(item.getID()))
                    return false;
                items_.append(item);
                return true;
            }

            // Remove by ID. Returns true if something was removed.
            bool removeById(const QString &id)
            {
                auto it = std::find_if(items_.begin(), items_.end(), [&](const T &i)
                                       { return i.getID() == id; });
                if (it != items_.end())
                {
                    items_.erase(it);
                    return true;
                }
                return false;
            }

            // Remove by predicate; returns count removed.
            template <typename Pred>
            int removeIf(Pred pred)
            {
                int removed = 0;
                for (auto it = items_.begin(); it != items_.end();)
                {
                    if (pred(*it))
                    {
                        it = items_.erase(it);
                        ++removed;
                    }
                    else
                    {
                        ++it;
                    }
                }
                return removed;
            }

            // Find by ID. Returns pointer-to-item or nullptr if not found.
            T *findById(const QString &id)
            {
                auto it = std::find_if(items_.begin(), items_.end(), [&](const T &i)
                                       { return i.getID() == id; });
                return it != items_.end() ? &(*it) : nullptr;
            }

            const T *findById(const QString &id) const
            {
                auto it = std::find_if(items_.cbegin(), items_.cend(), [&](const T &i)
                                       { return i.getID() == id; });
                return it != items_.cend() ? &(*it) : nullptr;
            }

            // Find the index by ID, or -1 if not found.
            int indexOfId(const QString &id) const
            {
                for (int idx = 0; idx < items_.size(); ++idx)
                {
                    if (items_[idx].getID() == id)
                        return idx;
                }
                return -1;
            }

            // Generic search using a predicate. Returns a copy of matches.
            template <typename Pred>
            QList<T> findAll(Pred pred) const
            {
                QList<T> out;
                for (const auto &item : items_)
                {
                    if (pred(item))
                        out.append(item);
                }
                return out;
            }

            // Convenience helpers using common LibraryItem fields.
            QList<T> findAllByTitle(const QString &title) const
            {
                return findAll([&](const T &i)
                               { return i.getTitle().compare(title, Qt::CaseInsensitive) == 0; });
            }

            QList<T> findAllByAuthor(const QString &author) const
            {
                return findAll([&](const T &i)
                               { return i.getAuthor().compare(author, Qt::CaseInsensitive) == 0; });
            }

            bool containsId(const QString &id) const { return findById(id) != nullptr; }

            // Accessors
            const Container &items() const noexcept { return items_; }
            Container &items() noexcept { return items_; }

            int size() const noexcept { return items_.size(); }
            bool isEmpty() const noexcept { return items_.isEmpty(); }
            void clear() noexcept { items_.clear(); }

        private:
            Container items_;
        };

    } // namespace StorageNS
} // namespace LibraryUtils

#endif // LIBRARYUTILS_STORAGE_STORAGE_H
