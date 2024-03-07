#include "entrymodel.h"
#include <settingslib.h>

EntryModel::EntryModel(QString language, QObject *parent)
    : QAbstractListModel{parent}
{
    std::string dictPath = SettingsLib{}.getValue("language", language.toStdString());
    d = std::make_unique<Dictionary>(dictPath);

    friendlyRoleNames[originalTextRole] = "originalText";
    friendlyRoleNames[translationTextRole] = "translationText";
    friendlyRoleNames[entryTypeRole] = "entryType";
    friendlyRoleNames[nicheRole] = "niche";
}

int EntryModel::rowCount(const QModelIndex &parent) const
{
    return wordEntries.size();
}

QVariant EntryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= wordEntries.size())
        return QVariant();

    switch(role){
    case originalTextRole:
        return QString::fromStdString(wordEntries.at(index.row()).original);
    case translationTextRole:
        return QString::fromStdString(wordEntries.at(index.row()).translation);
    case nicheRole:
        return QString::fromStdString(wordEntries.at(index.row()).niche);
    case entryTypeRole:
        return quint64(wordEntries.at(index.row()).entryType);
    }
    return QVariant();
}
