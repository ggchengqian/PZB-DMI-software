#ifndef DATAENTRY_H
#define DATAENTRY_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QPalette>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "numberkeyboard.h"

namespace Ui {
class DataEntry;
}

class DataEntry : public QWidget
{
    Q_OBJECT

public:
    explicit DataEntry(QWidget *parent = 0);
    ~DataEntry();
    void callKeyBoard();
    void setZDstatus(int value);
    void setTrainData(int index,int value);

protected:
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void slotNumber(int num);
    void slotBackspace();
    void slotpoint();
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_btable_clicked();
    void slotOvertime();

signals:
    void backToSetting();
    void signalVerification(int value);

private:
    Ui::DataEntry *ui;
    QList<QLabel*> field_list;
    QList<QLineEdit*> field_data_list;
    QList<QPushButton*> Key_list;
    CNumberKeyboard *keyboard;
    QTimer *PZBcommTimeou;
    bool lineeditstatus;
};

#endif // DATAENTRY_H
