#ifndef SHELL_H
#define SHELL_H
#include "subsriber.h"
#include <string>
#include <QVector>

class shell
{
private:
    int m_id;
    int m_type;
    int m_instock;
    int m_used;
    QVector<subsriber*> m_subscribers;

public:
    shell(int type, int instock, int used=0);
    shell(int id, int type, int instock, int used);
    shell() {}

    int get_type() const {
        return m_type;
    }

    int get_instock() const {
        return m_instock;
    }

    int get_used() const {
        return m_used;
    }

    int get_total() const {
        return m_instock + m_used;
    }

    int get_id() const {
        return m_id;
    }

    void set_id(int id) {
        m_id = id;
    }

    void add_instock(int count);
    void add_used(int count);

    void subscribe(subsriber* subs);
    void unsubscribe(subsriber* subs);
    void notify_all(std::string type_operation, int count);
};

#endif // SHELL_H
