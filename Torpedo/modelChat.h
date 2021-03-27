#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QVector>
#include "basebuildingblocks.h"



class modelChat
{
public:
    modelChat();
    std::vector<messenge> messenges;    // az üzenetek vektora
    void senndMessenge(QString s);
private:
    void readmessenge();
};

#endif // MODELCHAT_H
