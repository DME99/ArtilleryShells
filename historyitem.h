#ifndef HISTORYITEM_H
#define HISTORYITEM_H
#include <string>
#include <QDateTime>

class historyItem
{
private:
    std::string m_type_operation;
    int m_count;
    QDateTime m_date;
    int m_type_shell;

public:
    historyItem(std::string type_operation, int count, QDateTime date, int type_shell);
    historyItem() {}

    std::string get_type_operation() const {
        return m_type_operation;
    }

    int get_count() const {
        return m_count;
    }

    QDateTime get_date() const {
        return m_date;
    }

    int get_type_shell() const {
        return m_type_shell;
    }
};

#endif // HISTORYITEM_H
