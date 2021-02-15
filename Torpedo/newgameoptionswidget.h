#ifndef NEWGAMEOPTIONSWIDGET_H
#define NEWGAMEOPTIONSWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QListWidget>

class newgameoptionswidget : public QDialog // Új játékhoz beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit newgameoptionswidget(QWidget *parent = 0);

protected:
    QPushButton* _okButton;
    QPushButton* _cancelButton;
};

#endif // NEWGAMEOPTIONSWIDGET_H
