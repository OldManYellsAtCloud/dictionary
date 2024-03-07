#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include "dictionary.h"
#include <QAbstractListModel>
#include <QObject>
#include <memory>

class EntryModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QHash<int, QByteArray> friendlyRoleNames;
    std::unique_ptr<Dictionary> d;
    std::vector<DictionaryEntry::Entry> wordEntries;

public:
    explicit EntryModel(QString language, QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    enum RoleNames {
        originalTextRole = Qt::UserRole,
        translationTextRole = Qt::UserRole + 1,
        entryTypeRole = Qt::UserRole + 2,
        nicheRole = Qt::UserRole + 3
    };
};

#endif // ENTRYMODEL_H
