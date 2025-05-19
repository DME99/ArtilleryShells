#ifndef SUBSRIBER_H
#define SUBSRIBER_H
#include <string>

class subsriber
{
public:
    virtual void change_count(std::string type_operation, int count, int type_shell) = 0;
};

#endif // SUBSRIBER_H
