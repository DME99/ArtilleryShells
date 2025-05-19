#include "database_manager.h"


database_manager::database_manager(const QString& path) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(path);
}

database_manager::~database_manager() {
    mDatabase.close();
}

database_manager& database_manager::instance() {
    static database_manager instance(QDir::currentPath()+QString("/shellDB.db"));
    return instance;
}
