#include "entrymodel.h"
#include <settingslib.h>

EntryModel::EntryModel(QObject *parent): EntryModel{"de", parent}
{
}

EntryModel::EntryModel(QString language, QObject *parent)
    : QAbstractListModel{parent}
{
    settings = std::make_unique<SettingsLib>(SETTINGS_PATH);

    friendlyRoleNames[originalTextRole] = "originalText";
    friendlyRoleNames[translationTextRole] = "translationText";
    friendlyRoleNames[entryTypeRole] = "entryType";
    friendlyRoleNames[nicheRole] = "niche";
    switchLanguage(language);
}

EntryModel::~EntryModel()
{
    d.reset();
    settings.reset();
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

void EntryModel::switchLanguage(QVariant language) {
    clearModel();
    std::string languageString = language.toString().toStdString();
    std::string dictPath = settings->getValue("language", languageString);
    d.reset();
    d = std::make_unique<Dictionary>(dictPath);
}

void EntryModel::getTranslations(QVariant word)
{
    clearModel();
    auto tmp = d->getEntries(word.toString().toStdString());

    emit beginInsertRows(QModelIndex(), 0, tmp.size() - 1);
    wordEntries = tmp;
    emit endInsertRows();
}

void EntryModel::clearModel()
{
    emit beginRemoveRows(QModelIndex(), 0, wordEntries.size() - 1);
    wordEntries.clear();
    emit endRemoveRows();
}

QHash<int, QByteArray> EntryModel::roleNames() const
{
    return friendlyRoleNames;
}

