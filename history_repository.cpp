#include "history_repository.h"


void history_repository::load()
{
    mDatabase.open();

    QSqlQuery query;
    query.exec("SELECT * FROM history");

    while (query.next())
    {
        int id = query.value(0).toInt();
        QString type_operation = query.value(1).toString();
        int count = query.value(2).toInt();
        int type_shell = query.value(3).toInt();
        QString date = query.value(4).toString();

        historyItem item(type_operation.toStdString(), count, QDateTime::fromString(date), type_shell);
        m_items.insert(0, item);
    }

    mDatabase.close();
}

void history_repository::add(historyItem item)
{
    m_items.insert(0, item);

    mDatabase.open();

    QSqlQuery my_query;
    my_query.prepare("INSERT INTO history (type_operation, count, type_shell, date) VALUES (:type_operation, :count, :type_shell, :date);");
    my_query.bindValue(":type_operation",QString::fromStdString(item.get_type_operation()));
    my_query.bindValue(":count",item.get_count());
    my_query.bindValue(":type_shell",item.get_type_shell());
    my_query.bindValue(":date",item.get_date().toString());

    my_query.exec();

    mDatabase.close();
}
