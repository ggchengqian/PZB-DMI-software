#ifndef CFUNCTIONTEST_H
#define CFUNCTIONTEST_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QPainter>

namespace Ui {
class CFunctionTest;
}

class CFunctionTest : public QWidget
{
    Q_OBJECT

public:
    explicit CFunctionTest(QWidget *parent = 0);
    ~CFunctionTest();
    void paintEvent(QPaintEvent *);

    void setText(QString messagetext);
    void setTestRequeststat(int value);
    void setFuncTestinf(int value);
    QList<QPushButton*> butlist;
    QTimer *requestTimeout;

signals:
    void backToMainwid();
private slots:
    void slotOvertime();

    void on_pushButton_clicked();

private:
    Ui::CFunctionTest *ui;
};

#endif // CFUNCTIONTEST_H
