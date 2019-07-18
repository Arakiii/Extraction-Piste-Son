#include "application.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtGui>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QtWidgets/QFileDialog>
Application::Application()
{

}


using namespace std;

unsigned long RecupererFrequence(char* buffer)
{
    unsigned long FrequenceRecu;
    FrequenceRecu = *((unsigned long*)(buffer + 24)); //forçage en unsigned long pour prendre directement les 4 octets correspondant à la fréquence d'échantillonnage
    return FrequenceRecu;
}

void ExploiterExcel()
{
    HANDLE file;
    OFSTRUCT OpenBuff;
    file = (HANDLE)OpenFile("C:\\Users\\Kiwy\\Desktop\\pisteessai\\Batterie32b16boucles.csv", &OpenBuff, OF_READ);
    long tab[30]; // tableau qui contiendra l'entête du fichier WAVE
    DWORD retour;
    ReadFile(file, tab, 30, &retour, NULL);
}

int LireEnteteWAVE(QString file)
{

    QFile fichier(file); //On creer un objet QFile

 QTextStream flux(&fichier); //On creer un objet QTextStream à partir de l'objet QFile


        QString donnees = fichier.readAll();

    /*file = QFileDialog::getOpenFileName("C:\\Users\\Kiwy\\Desktop\\pisteessai\\4mesureBatt.wav",tr("Ouvrir Fichier"), ".", tr("Fichier MIDI (*.wav)"));
    char tab[30]; // tableau qui contiendra l'entête du fichier WAVE
    DWORD retour;
    file = QFileDialog::getReadFile(file, tab, 30, &retour, NULL);*/
    unsigned long FrequenceEchantillonnage;
    char* buffer;
    FrequenceEchantillonnage = *((unsigned long*)(buffer + 24)); //forçage en unsigned long pour prendre directement les 4 octets correspondant à la fréquence d'échantillonnage
    return FrequenceEchantillonnage;
    //retour: FrequenceE = 44100Hz
}

void EcrireFichierMIDI()
{
    HANDLE file;
    OFSTRUCT OpenBuff;
    DWORD Verification = NULL;
    DWORD Ecrit = NULL ;
    CreateFileA("C:\\Users\\milon\\Desktop\\test1.mid", GENERIC_READ | GENERIC_WRITE, Verification, NULL, 1, FILE_ATTRIBUTE_NORMAL, NULL);
    file = (HANDLE)OpenFile("C:\\Users\\milon\\Desktop\\test1.mid", &OpenBuff, OF_WRITE);
    unsigned char fichier[99]; // tableau qui contiendra les éléments à mettre dans le fichier MIDI
    fichier[0] = 77 ;
    fichier[1] = 84 ;
    fichier[2] = 104 ;
    fichier[3] = 100 ;
    fichier[4] = 0;
    fichier[5] = 0;
    fichier[6] = 0;
    fichier[7] = 6;
    fichier[8] = 0;
    fichier[9] = 0;
    fichier[10] = 0;
    fichier[11] = 1;
    fichier[12] = 0;
    fichier[13] = 192;
    fichier[14] = 77;
    fichier[15] = 84;
    fichier[16] = 114;
    fichier[17] = 107;	//En tête du fichier MIDI à ne pas modifier
    fichier[18] = 0;	//
    fichier[19] = 0;	//
    fichier[20] = 0;	//
    fichier[21] = 77;	// taille du fichier après fichier[17]
    fichier[22] = 0 ;	//
    fichier[23] = 144;  // Première note:
    fichier[24] = 65;	//
    fichier[25] = 50;	//
    fichier[26] = 131;
    fichier[27] = 0;
    fichier[28] = 144;  // Deuxième note:
    fichier[29] = 65;	//
    fichier[30] = 50;	//
    fichier[31] = 0;
    fichier[32] = 128;
    fichier[33] = 65;	//
    fichier[34] = 0;	//
    fichier[35] = 131;
    fichier[36] = 0;
    fichier[37] = 144;  // Troisième note:
    fichier[38] = 65;	//
    fichier[39] = 50;	//
    fichier[40] = 0;
    fichier[41] = 128;
    fichier[42] = 65;	//
    fichier[43] = 0;	//
    fichier[44] = 131;
    fichier[45] = 0;
    fichier[46] = 144;  // Quatrième note:
    fichier[47] = 65;	//
    fichier[48] = 50;	//
    fichier[49] = 0;
    fichier[50] = 128;
    fichier[51] = 65;	//
    fichier[52] = 0;	//
    fichier[53] = 131;
    fichier[54] = 0;
    fichier[55] = 144;  // Cinquième note:
    fichier[56] = 65;	//
    fichier[57] = 50;	//
    fichier[58] = 0;
    fichier[59] = 128;
    fichier[60] = 65;	//
    fichier[61] = 0;	//
    fichier[62] = 131;
    fichier[63] = 0;
    fichier[64] = 144;  // Sixième note:
    fichier[65] = 65;	//
    fichier[66] = 50;	//
    fichier[67] = 0;
    fichier[68] = 128;
    fichier[69] = 65;	//
    fichier[70] = 0;	//
    fichier[71] = 131;
    fichier[72] = 0;
    fichier[73] = 144;  // Septième note:
    fichier[74] = 65;	//
    fichier[75] = 50;	//
    fichier[76] = 0;
    fichier[77] = 128;
    fichier[78] = 65;	//
    fichier[79] = 0;	//
    fichier[80] = 131;
    fichier[81] = 0;
    fichier[82] = 144;  // Première note:
    fichier[83] = 65;	//
    fichier[84] = 50;	//
    fichier[85] = 0;
    fichier[86] = 128;
    fichier[87] = 65;	//
    fichier[88] = 0;	//
    fichier[89] = 131;
    fichier[90] = 0;
    fichier[91] = 128;
    fichier[92] = 65;
    fichier[93] = 0;
    fichier[94] = 131;
    fichier[95] = 0;
    fichier[96] = 255;
    fichier[97] = 47;
    fichier[98] = 0;
    WriteFile(file, fichier, 99, &Ecrit, NULL);
    //delete[] note;

}
