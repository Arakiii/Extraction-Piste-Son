#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//---------------Include Class---------------

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QLineEdit>
#include <QSound>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <Qt>
#include <QApplication>
#include <QFile>
#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QScrollArea>
#include <QTextBrowser>
#include <QTextStream>
#include <QVariant>
#include <QMouseEvent>
#include <QPdfWriter>
#include <QPainter>
#include <QProcess>
#include <QPrinter>
#include <QtSvg>
#include <QMediaPlayer>
#include <QActionGroup>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QScrollArea>
#include <QTabWidget>
#include <cxxmidi/file.hpp>
#include <cxxmidi/output/default.hpp>
#include <cxxmidi/player/asynchronous.hpp>
#include <cxxmidi/time/point.hpp>
#include "playerheartbeatcallback.h"
#include "playerfinishedcallback.h"
#include "Htmlhelp.h"

//---------------Include Class---------------

//---------------Fichier Include---------------

#include <windows.h>
#include <AboutDialog.h>



//---------------Fichier Include---------------
/*! \brief Espace de nom Ui
*/
namespace Ui {


class MainWindow;
}
/*! \file mainwindow.h
Fichier principale du projet contenant toute les fontions permettant le bon fonctionnement du projet
le fichier utilise différent include faisant parti des classes de Qt ainsi que diverse bibliothèque tiers telle que CxxMidi
\author Serre
\date 12/04/2019 Création de la version 0.5
\date 17/04/2019 Mise en place du fichier CHM
*/

class MainWindow : public QMainWindow
{
    /*! \class MainWindow
     *  \brief MainWindow class

/*! \fn Le compilateur de méta-objets, moc, est le programme qui gère les extensions C++ de Qt.
*/
    Q_OBJECT

public:
/*! \fn Constructeur de la Fonction MainWindow <br>
Fonction principale qui permet le bon fonctionnement de l'ihm en créant la fenetre <br>
Le spécificateur de fonction explicite contrôle les conversions de types implicites indésirables.
*/
    explicit MainWindow(QWidget *parent = nullptr);

/*! \fn Destructeur de la fonction MainWindow
*/
    ~MainWindow();


private slots:

    void OuvrirFichier();
    void EnregistrerSous();
    void Plein_Ecran();

/** \fn void OuvrirDialogue() <br>
 *  \brief Fonction permettant l'ouverture d'un dialogue pour questionner l'utilisateur sur la satifaction de la géneration de la partition (Oui ou Non)
 */
    void OuvrirDialogue();

/*! \fn Fonction on_BoutonOuvrir_clicked <br>
Fonction permettant l'ouverture a l'aide d'un clique sur un bouton d'ouvrir une fenetre d'ouverture de fichier avec certain paramètre pris en compte
*/
    void on_BoutonOuvrir_clicked();
/*! \fn Fonction about <br>
Fonction permettant l'ouverture d'une fenetre additionnel contenant les information secondaire a propos de l'application et de ces créateurs
*/
    void about();
/*! \fn Fonction Notice <br>
Fonction permettant l'ouverture d'une fenetre additionnel contenant la notice d'utilisation du programme afin de facilité la tache de l'utilisateur
*/
    void Notice();
/*! \fn Fonction on_BoutonDeveloppeur_clicked <br>
Fonction permettant l'ouverture a l'aide d'un clique sur un bouton l'ouverture d'un logiciel développeur afin d'effectuer des taches que l'utilisateur n'est pas censé avoir accès
*/
    void on_BoutonDeveloppeur_clicked();
/*! \fn Fonction on_BoutonConversion_clicked <br>
Fonction permettant l'ouverture a l'aide d'un clique sur un bouton d'une serie de commande permettant de récupérer diverse information afin de pouvoir réalisé la conversion du fichier MIDI en Partition
*/
    void on_BoutonConversion_clicked();
/*! \fn Fonction on_BoutonPartition_clicked <br>
Fonction permettant l'ouverture a l'aide d'un clique sur un bouton d'un fichier de partition au choix selon l'envie de l'utilisateur
*/
    void on_BoutonPartition_clicked();
/*! \fn Fonction Previsualisation <br>
Fonction permettant d'afficher après la convertision dans un label un aperçu de la partition
*/
    void Previsualisation();
/*! \fn Fonction ClickLabel <br>
Fonction permettant d'afficher a l'aide d'un clique sur le label de prévisualisation la partition généré
*/
    void ClickLabel();
/*! \fn Fonction WritePdf <br>
Fonction permettant de créer un PDF a l'aide de l'image généré par la conversion qui est en pdf (Résumé : Png to Pdf)
*/
    void WritePdf();
/*! \fn Fonction Information <br>
Fonction permettant a l'ouverture du logiciel d'informer l'utilisateur sur la situation du projet
*/
    void Information();
/*! \fn Fonction AffichageEdition <br>
Fonction permettant d'afficher le fichier généré avec la conversion contenant le contenu du fichier midi sur une timeline dans un label
*/
    void AffichageEdition();
/*! \fn Fonction on_BoutonSonore_clicked <br>
Fonction permettant d'effectuer un test son avec un fichier Wav
*/
    void on_BoutonSonore_clicked();
/*! \fn Fonction SuiteConversion <br>
Fonction permettant d'effectuer le second script dans la conversion qui permet de créer le fichier avec les notes dans une timeline
*/
    void SuiteConversion();
/*! \fn Fonction on_EnregistrerPDF_clicked <br>
Fonction qui reprend la fonction WritePdf mais l'implémente dans un bouton
*/
    void on_EnregistrerPDF_clicked();
/*! \fn Fonction on_BoutonModifier_clicked <br>
Fonction permettant d'ouvrir un logiciel d'edition temporaire
*/
    void on_BoutonModifier_clicked();
/*! \fn Fonction openFile <br>
Fonction qui reprend le meme principe que l'ouverture d'un fichier mais en plus de le lire l'introduit dans le lecteur MIDI
*/
    void openFile();
/*! \fn Fonction openFile(const QString& path_) <br>
Fonction qui lit les détails du fichier MIDI et récuperer les information sur le temps , le tempo et prépare le lecteur MIDI a la lecture du fichier
*/
    void openFile(const QString& path_);
/*! \fn Fonction onPlayClicked <br>
Fonction permettant lors d'un clique de lancer la lecture du fichier MIDI qui a était introduit dans le lecteur auparavent
*/
    void onPlayClicked();
/*! \fn Fonction onPauseClicked <br>
Fonction permettant lors d'un clique de mettre pause à la lecture du fichier MIDI qui a était introduit dans le lecteur auparavent
*/
    void onPauseClicked();
/*! \fn Fonction playerFinished <br>
Fonction permettant de réinitialiser le lecteur a zéro a la fin de la lecture
*/
    void playerFinished();
/*! \fn Fonction updateTimeCode(CxxMidi::Time::Point time_) <br>
Fonction permettant de raffraichir la timeline toute les 100 milliseconde
*/
    void updateTimeCode(CxxMidi::Time::Point time_);
/*! \fn Fonction onSpeedChange(double speed_) <br>
Fonction permettant a l'aide d'une spinbox de modifier la vitesse de la musique (de 0.10 à 1)
*/
    void onSpeedChange(double speed_);
/*! \fn Fonction onTimeSliderReleased <br>
Fonction permettant de réalisé les déplacement dans le temps de la musique selon l'endroit de la musique et selon certaint critère
*/
    void onTimeSliderReleased();
/*! \fn Fonction onTimeSliderPressed <br>
Fonction permettant de bloquer le slider lors d'un clique sur le slider
*/
    void onTimeSliderPressed();
/*! \fn Fonction setOutput(int num_) <br>
Fonction permettant de selectionner l'output ou le son va sortir (Dans notre cas sur la carte son du PC)
*/
    void setOutput(int num_);
/*! \fn Fonction onOutputSelected(QAction* action_) <br>
Fonction permettant charge l'output selectionner
*/
    void onOutputSelected(QAction* action_);

    void ApercuAvantImpression();

    void on_Imprimer_clicked();



//----------------------------------------------Code MILON---DEBUT-----------------------------------------------

    void Ouvrir_fichier2();

    void AffichageCle();

    void AffichageNote2();

    void on_BoutonOuvrirMilon_clicked();

    void on_BoutonSaveMilon_clicked();

    void on_BoutonModifierMilon_clicked();
//----------------------------------------------CODE MILON---FIN-----------------------------------------------

//----------------------------------------------CODE WYBAUW---DEBUT----------------------------------------------

    void Ouvrir_fichier3();


    void on_BoutonOuvrirWybauw_clicked();

    void on_IsolerFreqBasseWybauw_clicked();
//----------------------------------------------CODE WYBAUW---FIN----------------------------------------------

protected:
//----------------------------------------------Code MILON---DEBUT-----------------------------------------------
    //void paintEvent(QPaintEvent *e);
    QLabel *label1Milon;
    QLabel *labeltest;
//----------------------------------------------Code MILON---FIN-----------------------------------------------
private:
  QActionGroup * _outputsActionGroup;
    QLabel *label2;
    QLabel *label1;
    void CreerMenu();
    Ui::MainWindow *ui;

    CxxMidi::Time::Point _currentTimePoint;
    CxxMidi::Time::Point _finalTimePoint;

    CxxMidi::Output::Default* _midiOutput;
    CxxMidi::Player::Asynchronous* _midiPlayer;
    CxxMidi::File* _midiFile;

    PlayerHeartbeatCallback _playerHeartbeatCallback;
    PlayerFinishedCallback _playerFinishedCallback;

    bool _sliderLocked;
};

#endif // MAINWINDOW_H
