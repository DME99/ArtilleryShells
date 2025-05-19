#ifndef HISTORY_REPOSITORY_H
#define HISTORY_REPOSITORY_H
#include "historyitem.h"
#include <QVector>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QVariant"
#include "database_manager.h"

class history_repository
{
private:
    QVector<historyItem> m_items;
    QSqlDatabase& mDatabase;

public:
    history_repository() : mDatabase(database_manager::instance().database()) {
        load();
    }

    void load();

    QVector<historyItem> getAll() const {
        return m_items;
    }

    void add(historyItem item);
};

#endif // HISTORY_REPOSITORY_H
