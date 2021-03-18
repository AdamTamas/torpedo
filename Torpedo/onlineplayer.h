#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H
#include "baseplayer.h"
#include <map>
#include <QTcpSocket>

class onlineplayer : public baseplayer
{
    Q_OBJECT
public:
    onlineplayer(NewGameData newdata);
    ~onlineplayer();
    virtual Coordinate makeShot() override;
    virtual void getShot(Coordinate c) override;
    virtual void shotResponse(bool hit) override;
    void connect();

public slots:

protected:
    Coordinate _lastShot;
    QTcpSocket *socket;
};

#endif // ONLINEPLAYER_H
