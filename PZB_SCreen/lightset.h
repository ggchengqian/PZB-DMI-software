#ifndef CLIGHTSET_H
#define CLIGHTSET_H

#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QDebug>

namespace Ui {
class CLightSet;
}

class CLightSet : public QWidget
{
    Q_OBJECT

public:
    explicit CLightSet(QWidget *parent = 0);
    ~CLightSet();


private slots:
    void on_addBtn_clicked();
    void on_subBtn_clicked();
    void on_manualBtn_clicked();
    void on_autoBtn_clicked();

    void on_backBtn_clicked();

signals:
    void setLightLevel(int);
    void backToSetting();

private:
    Ui::CLightSet *ui;
    QFile *m_serial;
    QList<QLabel*> labellist;
    int value;

    void setLight(int val);
    void writeSerial(int val);

};

#endif // CLIGHTSET_H
