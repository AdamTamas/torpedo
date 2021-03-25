#ifndef WIDGETCHAT_H
#define WIDGETCHAT_H

#include <QDialog>
#include <QPushButton>
#include <QPlainTextEdit>

class widgetChat : public QDialog // online catlakozás beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit widgetChat(QWidget *parent = 0);


protected:
    QPushButton* _sendButton;
    QPushButton* _cancelButton;
    QPlainTextEdit* _messengeField;
    QPlainTextEdit* _chatField;
    void setHeight (QPlainTextEdit *ptxt, int nRows);

private slots:
    void _send(); // eseménykezelők a modell eseményeire

private:
};

#endif // WIDGETCHAT_H
