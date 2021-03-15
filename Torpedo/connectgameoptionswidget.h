#ifndef CONNECTGAMEOPTIONSWIDGET_H
#define CONNECTGAMEOPTIONSWIDGET_H

#include <QDialog>
#include <QPushButton>

class connectgameoptionswidget : public QDialog // online catlakozás beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit connectgameoptionswidget(QWidget *parent = 0);


protected:
    QPushButton* _okButton;
    QPushButton* _cancelButton;

private slots:
    void _connectGameSlot(); // eseménykezelők a modell eseményeire

private:
};


#endif // CONNECTGAMEOPTIONSWIDGET_H
