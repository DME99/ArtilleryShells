#include "shell_repository.h"



void shell_repository::load_shells()
{
    mDatabase.open();

    QSqlQuery query;
    query.exec("SELECT * FROM shell");

    while (query.next())
    {
        int id = query.value(0).toInt();
        int type = query.value(1).toInt();
        int instock = query.value(2).toInt();
        int used = query.value(3).toInt();

        shell* sh = new shell(id, type, instock, used);
        m_shells.push_back(sh);
    }

    mDatabase.close();
}

void shell_repository::add_shell(shell* sh)
{

    m_shells.push_back(sh);

    mDatabase.open();

    QSqlQuery my_query;
    my_query.prepare("INSERT INTO shell (type, instock, used) VALUES (:type, :instock, :used);");
    my_query.bindValue(":type", sh->get_type());
     my_query.bindValue(":instock", sh->get_instock());
    my_query.bindValue(":used", sh->get_used());

    my_query.exec();

     int id = my_query.lastInsertId().toInt();
     sh->set_id(id);

    mDatabase.close();
}

void shell_repository::update(shell *sh)
{
    mDatabase.open();

    QSqlQuery my_query;
    my_query.prepare("UPDATE shell set type = :type, instock = :instock, used = :used WHERE id = :id;");
    my_query.bindValue(":type", sh->get_type());
    my_query.bindValue(":instock", sh->get_instock());
    my_query.bindValue(":used", sh->get_used());
    my_query.bindValue(":id", sh->get_id());
    my_query.exec();

    mDatabase.close();
}

shell *shell_repository::find(int type)
{
    for(int i = 0; i < m_shells.size(); i++) {
        if (m_shells[i]->get_type() == type) {
            return m_shells[i];
        }
    }
    return nullptr;
}

void shell_repository::sort_by_instock()
{
    for(int i = 0; i < m_shells.size(); i++) {
        for(int j = 0; j < m_shells.size() - 1; j++) {
            if (m_shells[j]->get_instock() > m_shells[j+1]->get_instock()) {
                std::swap(m_shells[j], m_shells[j + 1]);
            }
        }
    }
}
