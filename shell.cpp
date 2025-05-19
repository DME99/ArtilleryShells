#include "shell.h"


shell::shell(int type, int instock, int used)
{
    m_type = type;
    m_instock = instock;
    m_used = used;
}

shell::shell(int id, int type, int instock, int used)
{
    m_id = id;
    m_type = type;
    m_instock = instock;
    m_used = used;
}

void shell::add_instock(int count)
{
    m_instock += count;

    notify_all("add", count);
}


void shell::add_used(int count)
{
    m_instock -= count;
    m_used += count;

    notify_all("remove", count);
}

void shell::subscribe(subsriber *subs)
{
    if (!m_subscribers.contains(subs)) {
        m_subscribers.push_back(subs);
    }
}

void shell::unsubscribe(subsriber *subs)
{
    if (m_subscribers.contains(subs)) {
        m_subscribers.removeOne(subs);
    }
}

void shell::notify_all(std::string type_operation, int count)
{
    for(subsriber* subs : m_subscribers) {
        subs->change_count(type_operation, count, m_type);
    }
}
