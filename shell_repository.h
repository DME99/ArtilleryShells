#ifndef SHELL_REPOSITORY_H
#define SHELL_REPOSITORY_H

#include "shell.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QVariant"
#include "database_manager.h"

class shell_repository
{
private:
    QVector<shell*> m_shells;
     QSqlDatabase& mDatabase;

public:
    shell_repository() : mDatabase(database_manager::instance().database()) {
        load_shells();
    }

    void load_shells();

    QVector<shell*> getAll() {
        return m_shells;
    }

    void add_shell(shell* sh);
    void update(shell* sh);

    shell* find(int type);

    void sort_by_instock();
};

#endif // SHELL_REPOSITORY_H
