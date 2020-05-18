#ifndef CDRIVERID_H
#define CDRIVERID_H

#include <QWidget>
#include "numberkeyboard.h"

namespace Ui {
class CDriverID;
}

class CDriverID : public QWidget
{
    Q_OBJECT

public:
    explicit CDriverID(QWidget *parent = 0);
    ~CDriverID();
    bool eventFilter(QObject *watched, QEvent *event);
    void setDriverIDVal(int value);

private slots:
    void on_cancelBtn_clicked();
    void callKeyBoard();
    void slotNumber(int num);
    void slotpoint();
    void slotBackspace();

    void on_okBtn_clicked();

signals:
    void backToSetting();
    void senddriverID(int);

private:
    Ui::CDriverID *ui;
    CNumberKeyboard *numkey;
};

#endif // CDRIVERID_H
