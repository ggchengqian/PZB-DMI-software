#ifndef NUMBERKEYBOARD_H
#define NUMBERKEYBOARD_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CNumberKeyboard;
}

class CNumberKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit CNumberKeyboard(QWidget *parent = 0);
    ~CNumberKeyboard();

signals:
    void signalNumber(int);
    void signalBackspace();
    void signalpoint();

private:
    Ui::CNumberKeyboard *ui;
    QList<QPushButton*> numberlist;
    int nWidth;
    int nHeight;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // NUMBERKEYBOARD_H
