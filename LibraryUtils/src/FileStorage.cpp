#include "LibraryUtils/Persistence/FileStorage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

#include "book.h"
#include "magazine.h"

namespace LibraryUtils
{
    namespace Persistence
    {

        bool FileStorage::loadAll(const QString &filePath, QList<Book> &books, QList<Magazine> &mags)
        {
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qWarning() << "Failed to open:" << filePath;
                return false;
            }

            const auto doc = QJsonDocument::fromJson(file.readAll());
            if (!doc.isArray())
            {
                qWarning() << "Expected JSON array in:" << filePath;
                return false;
            }

            books.clear();
            mags.clear();

            const QJsonArray jsonArray = doc.array();
            for (const QJsonValue &value : jsonArray)
            {
                if (!value.isObject())
                    continue;
                QJsonObject item = value.toObject();

                if (item.contains("genre"))
                {
                    books.append(Book(item));
                    continue;
                }

                if (item.contains("issue") && !item.contains("issueNumber"))
                {
                    item.insert("issueNumber", item["issue"]);
                    item.remove("issue");
                }
                if (item.contains("issueNumber"))
                {
                    mags.append(Magazine(item));
                }
            }
            return true;
        }

        QJsonArray FileStorage::toJsonArray(const QList<Book> &books, const QList<Magazine> &mags)
        {
            QJsonArray jsonArray;

            for (const Book &b : books)
            {
                QJsonObject item;
                item["id"] = b.getID();
                item["title"] = b.getTitle();
                item["author"] = b.getAuthor();
                item["isBorrowed"] = b.getIsBorrowed();
                item["genre"] = b.getGenre();
                jsonArray.append(item);
            }

            for (const Magazine &m : mags)
            {
                QJsonObject item;
                item["id"] = m.getID();
                item["title"] = m.getTitle();
                item["author"] = m.getAuthor();
                item["isBorrowed"] = m.getIsBorrowed();
                item["issueNumber"] = m.getIssueNo();
                jsonArray.append(item);
            }

            return jsonArray;
        }

        bool FileStorage::saveAll(const QString &filePath, const QList<Book> &books, const QList<Magazine> &mags)
        {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                qWarning() << "Failed to open:" << filePath;
                return false;
            }

            const QJsonArray array = toJsonArray(books, mags);
            QJsonDocument doc(array);
            file.write(doc.toJson(QJsonDocument::Indented));
            file.close();
            return true;
        }

    } // namespace Persistence
} // namespace LibraryUtils
