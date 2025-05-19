#ifndef HISTORY_H
#define HISTORY_H
#include "historyitem.h"
#include "subsriber.h"
#include "history_repository.h"
#include <QVector>

class history : public subsriber
{
private:
    history_repository history_repo;

public:
    void add_history_item(std::string type_operation, int count, int type_shell, QDateTime date);

    void change_count(std::string type_operation, int count, int type_shell);

    QVector<historyItem> get_items() const {
        return history_repo.getAll();
    }
};

#endif // HISTORY_H
