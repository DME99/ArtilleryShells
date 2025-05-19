#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QDir>

class database_manager {
public:
    static database_manager& instance();
    QSqlDatabase& database() { return mDatabase; }

private:
    database_manager(const QString& path);
    ~database_manager();

    QSqlDatabase mDatabase;
};


#endif // DATABASE_MANAGER_H
