#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include "dictionary.h"
#include <settingslib.h>
#include <QAbstractListModel>
#include <QObject>
#include <memory>

#define SETTINGS_PATH  "/etc"

class EntryModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QHash<int, QByteArray> friendlyRoleNames;
    std::unique_ptr<Dictionary> d;
    std::vector<DictionaryEntry::Entry> wordEntries;
    std::unique_ptr<SettingsLib> settings;

public:
    explicit EntryModel(QObject *parent = nullptr);
    explicit EntryModel(QString language, QObject *parent = nullptr);
    ~EntryModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE void switchLanguage(QVariant language);
    Q_INVOKABLE void getTranslations(QVariant word);
    void clearModel();

    enum RoleNames {
        originalTextRole = Qt::UserRole,
        translationTextRole = Qt::UserRole + 1,
        entryTypeRole = Qt::UserRole + 2,
        nicheRole = Qt::UserRole + 3
    };

    QHash<int, QByteArray> roleNames() const;
};

#endif // ENTRYMODEL_H
