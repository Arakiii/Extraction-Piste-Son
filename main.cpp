#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<CxxMidi::Time::Point>("CxxMidi::Time::Point");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
/*
    qDebug() << qApp->applicationDirPath();
    if (!QDir::setCurrent(QStringLiteral("/usr/lib")))
        qDebug() << "Could not change the current working directory";
    qDebug() << qApp->applicationDirPath();
*/
    return a.exec();
}
