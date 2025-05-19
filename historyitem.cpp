#include "historyitem.h"


historyItem::historyItem(std::string type_operation, int count, QDateTime date, int type_shell)
{
    m_type_operation = type_operation;
    m_count = count;
    m_date = date;
    m_type_shell = type_shell;
}
