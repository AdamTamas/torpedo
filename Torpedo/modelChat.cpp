#include "modelChat.h"
#include <time.h>

modelChat::modelChat()
{

}

void modelChat::senndMessenge(QString s){
    messenge newMessenge{"Én",s,time(NULL)};
    messenges.push_back(newMessenge);
}

void modelChat::readmessenge(){

}
