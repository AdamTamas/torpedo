#ifndef CONNECTGAMEOPTIONSWIDGET_H
#define CONNECTGAMEOPTIONSWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QPlainTextEdit>

class widgetConnectGameOptions : public QDialog // online catlakozás beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit widgetConnectGameOptions(QWidget *parent = 0);
    QString hostname() const;
    quint16 port() const;

protected:
    void setHeight (QPlainTextEdit *ptxt, int nRows);
    QPushButton* _okButton;
    QPushButton* _cancelButton;
    QPlainTextEdit* _IP;
    //QPlainTextEdit* _Port;

private slots:
    void _connectGameSlot(); // eseménykezelők a modell eseményeire


private:
    QString mHostname;
    quint16 mPort;
};


#endif // CONNECTGAMEOPTIONSWIDGET_H
