#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <QFileDialog>
#include <QProcess>

class Application
{
public:
    Application();
    void EcrireFichierMIDI();
    int LireEnteteWAVE(QString);
    //unsigned long RecupererFrequence(char*);
    void ExploiterExcel();
};

#endif // APPLICATION_H
