#ifndef NEWGAMEOPTIONSWIDGET_H
#define NEWGAMEOPTIONSWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>

class newgameoptionswidget : public QDialog // Új játékhoz beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit newgameoptionswidget(QWidget *parent = 0);

protected:
    std::vector<QComboBox*> _shipQuantitiesComboBoxes;
    QPushButton* _okButton;
    QPushButton* _cancelButton;


private:
    int _maxShipSize = 5;
    int _maxShipQuantity = 3;
    int _maxBoardSize = 16;
};


#endif // NEWGAMEOPTIONSWIDGET_H
