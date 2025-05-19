#include "history.h"


void history::add_history_item(std::string type_operation, int count, int type_shell, QDateTime date)
{
    history_repo.add(historyItem(type_operation, count, date, type_shell));
}



void history::change_count(std::string type_operation, int count, int type_shell)
{
    add_history_item(type_operation, count, type_shell, QDateTime::currentDateTime());
}
