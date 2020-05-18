#ifndef CRUNNINGNUM_H
#define CRUNNINGNUM_H

#include <QWidget>
#include "numberkeyboard.h"

namespace Ui {
class CRunningNum;
}

class CRunningNum : public QWidget
{
    Q_OBJECT

public:
    explicit CRunningNum(QWidget *parent = 0);
    ~CRunningNum();
    bool eventFilter(QObject *watched, QEvent *event);
    void setRunningNumVal(int value);

private slots:
    void on_cancelBtn_clicked();
    void callKeyBoard();
    void slotNumber(int num);
    void slotpoint();
    void slotBackspace();

    void on_okBtn_clicked();

signals:
    void backToSetting();
    void sendrunningnum(int);

private:
    Ui::CRunningNum *ui;
    CNumberKeyboard *numkeyboard;
};

#endif // CRUNNINGNUM_H
