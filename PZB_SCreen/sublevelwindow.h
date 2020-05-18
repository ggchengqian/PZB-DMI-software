#ifndef CSUBLEVELWINDOW_H
#define CSUBLEVELWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>

namespace Ui {
class CSubLevelWindow;
}

class CSubLevelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CSubLevelWindow(QWidget *parent = 0);
    ~CSubLevelWindow();

    enum
    {
        Brightness, Train_Running_Number, DataEntry, Driver_ID, Test
    };

private slots:

signals:
    void signalSetting(int);

private:
    Ui::CSubLevelWindow *ui;

    QButtonGroup *setting_Btn;
};

#endif // CSUBLEVELWINDOW_H
