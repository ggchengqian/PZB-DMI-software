#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QTextCodec>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    CMainWindow *w = new CMainWindow;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addWidget(w);
    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(800,480);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->rotate(90);
    view->show();

    //w->show();

    return a.exec();
}
