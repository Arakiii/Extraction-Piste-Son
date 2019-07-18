#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modifnote.h"
#include "application.h"

/*!Variable
 */
QString NomFichier;
QString NomEnregistrer;
QString AffichagePrevisualisation;
QString AffichageModification;
QString NomPDF;
QString NomImage;
QString TextTools;

int printer;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
     , _midiOutput(new CxxMidi::Output::Default(0))
     , _midiPlayer(new CxxMidi::Player::Asynchronous(_midiOutput))
     , _midiFile(0)
     , _playerHeartbeatCallback(_midiPlayer)
     , _sliderLocked(false)
{


    ui->setupUi(this);
    this->setFixedSize(983,596);
    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPause->setEnabled(false);
    ui->sliderTimeline->setEnabled(false);
    ui->doubleSpinBoxSpeed->setEnabled(false);

    ui->EnregistrerPDF->setEnabled(false);
    ui->Imprimer->setEnabled(false);
    ui->BoutonConversion->setEnabled(false);
    ui->BoutonPartition->setEnabled(false);
    ui->BoutonModifier->setEnabled(false);



//--------------------------------------------Code Milon-----------------------------------------------------
ui->BoutonPlayMilon->setIcon(QIcon(":/Icon/play.png"));
ui->BoutonPauseMilon->setIcon(QIcon(":/Icon/pause.png"));
//--------------------------------------------Code Milon-----------------------------------------------------

    _midiPlayer->setCallbackHeartbeat(&_playerHeartbeatCallback);
        connect(&_playerHeartbeatCallback,SIGNAL(playerTimeChanged(CxxMidi::Time::Point)),
                this,SLOT(updateTimeCode(CxxMidi::Time::Point)),Qt::QueuedConnection);

        _midiPlayer->setCallbackFinished(&_playerFinishedCallback);
        connect(&_playerFinishedCallback,SIGNAL(playerFinished()),
                this,SLOT(playerFinished()),Qt::QueuedConnection);

        connect(ui->doubleSpinBoxSpeed,SIGNAL(valueChanged(double)),
                this,SLOT(onSpeedChange(double)));


        connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(onPlayClicked()));
        ui->pushButtonPlay->setIcon(QIcon(":/Icon/PlayIcon.png"));

       connect(ui->pushButtonPause,SIGNAL(clicked()), this,SLOT(onPauseClicked()));
        ui->pushButtonPause->setIcon(QIcon(":/Icon/PauseIcon.png"));

        connect(ui->sliderTimeline,SIGNAL(sliderPressed()),
                this,SLOT(onTimeSliderPressed()));

        connect(ui->sliderTimeline,SIGNAL(sliderReleased()),
                this,SLOT(onTimeSliderReleased()));



        // first argument is file name
        if(QApplication::arguments().size() >=2 )
        {
            QString fileName = QApplication::arguments().at(1);
            this->openFile(fileName);
        }

        // second argument is output num
        if(QApplication::arguments().size() >=3)
        {
            int num = QApplication::arguments().at(2).toInt();
            this->setOutput(num);
            _outputsActionGroup->actions()[num]->setChecked(true);
        }

        // auto play
        if( QApplication::arguments().size() >= 2)
            _midiPlayer->play();


/*! \brief Changement du nom de la fenetre et de l'icone du projet
 */

    setWindowTitle(tr("Extraction Piste Son"));
    setWindowIcon(QIcon(":/Icon/ZbouiHD.png"));

/*! \brief Mise en place du fichier ui (Mis en place de l'IHM)
 */



//Creer le menu situé en haut de la fenetre qui permet d'acceder a differente fonction

    this->CreerMenu();

//Création d'un toolstip (Infobulle) ce situant sur la prévisualisation afin de guider l'utilisateur

    TextTools = "Cette affichage est intéractif. Cliquez pour voir son contenu en plus grand !";
    ui->BoutonPrevisualisation->setToolTip(TextTools);

//Connection du bouton Previsualisation a la fonction "ClickLabel" afin de permettre un zoom de la partition

    connect(ui->BoutonPrevisualisation,SIGNAL(clicked()),this , SLOT(ClickLabel()));

//Lancement d'une fenetre d'information au lancement du programme afin de partager des information avec l'utilisateur

    Information();

}



// Creation d'un menu qui permet d'accéder a divers fonction


void MainWindow::CreerMenu()
{
//Creation d'un onglet "Fichier"

    QMenu* fileMenu= this->menuBar()->addMenu(tr("&Fichier"));

//Fonction "Ouvrir"

   QAction *action = fileMenu->addAction(tr("&Ouvrir"));
   connect(action,SIGNAL(triggered()),
   this,SLOT(on_BoutonOuvrir_clicked()));
   action->setShortcut(QKeySequence("Ctrl+O"));
   action->setIcon(QIcon(":/Icon/OpenIcon.png"));

//Fonction "Enregistrer sous"

    QAction *actionSave = fileMenu->addAction(tr("&Enregistrer sous"));
    connect(actionSave,SIGNAL(triggered()),
    this,SLOT(EnregistrerSous()));
    actionSave->setShortcut(QKeySequence("Ctrl+S"));
    actionSave->setIcon(QIcon(":/Icon/SaveIcon.png"));


//Fonction "Enregister en PDF"

    QAction *actionPDF = fileMenu->addAction(tr("&Enregistrer en PDF"));
    connect(actionPDF,SIGNAL(triggered()),
    this,SLOT(WritePdf()));
    actionPDF->setIcon(QIcon(":/Icon/PdfIcon.png"));

//Création d'un séparateur

    fileMenu->addSeparator();

//Fonction "Quitter"

    QAction *actionQuit = fileMenu->addAction(tr("&Quitter"));
    QObject::connect(actionQuit,SIGNAL(triggered()),
    QApplication::instance(),SLOT(quit()));
    actionQuit->setShortcut(QKeySequence("Ctrl+Q"));
    actionQuit->setIcon(QIcon(":/Icon/QuitIcon.png"));

// Creation d'un onglet "Affichage"

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

//Fonction "Plein écran"

    QAction *actionFullScreen = new QAction("Plein écran", this);
    connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(Plein_Ecran()));
    menuAffichage->addAction(actionFullScreen);
    actionFullScreen->setShortcut(QKeySequence("Ctrl+F11"));
    actionFullScreen->setIcon(QIcon(":/Icon/FullScreenIcon.png"));

//Création d'un onglet "Aide"

    QMenu* menuAide = this->menuBar()->addMenu(tr("&Aide"));

//Fonction "Notice"

    QAction *actionNotice = menuAide->addAction(tr("&Notice"));
    connect(actionNotice,SIGNAL(triggered()),this, SLOT(Notice()));
    menuAide->addAction(actionNotice);

//Fonction "About"

    QAction *actionAbout = menuAide->addAction(tr("&A Propos"));
    connect(actionAbout,SIGNAL(triggered()),this, SLOT(about()));
    menuAide->addAction(actionAbout);
    actionAbout->setIcon(QIcon(":/Icon/AboutIcon.png"));

//Fonction "About QT"

    QAction *actionAboutQt = menuAide->addAction(tr("&A Propos de Qt"));
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    menuAide->addAction(actionAboutQt);
    actionAboutQt->setIcon(QIcon(":/Icon/qt-creator.jpg"));

}


void MainWindow::OuvrirFichier()
{
//Création d'un dialog pour Ouvrir un fichier (ici un fichier MIDI)

    QString fileName = QFileDialog::getOpenFileName(this,tr("Ouvrir Fichier"), ".", tr("Fichier MIDI (*.mid *.midi)"));

    if( fileName.size() )
    {
        this->openFile(fileName);
        _midiPlayer->output();
    }


}

void MainWindow::EnregistrerSous()
{
//Création d'un dialog pour Enregistrer un fichier (ici deux choix possible: MIDI ou PDF)

    WritePdf();

}

void MainWindow::Plein_Ecran()
{
//Commande pour Activer/Désactiver le mode Pleine écran

    isFullScreen() ? showNormal() : showFullScreen();
}



void MainWindow::on_BoutonOuvrir_clicked()
{
//Création d'un dialog pour ouvrir un fichier (Ici un fichier MIDI)

    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open file"), ".", tr("MIDI files (*.mid *.midi)"));
    if( fileName.size() )
    {
        this->openFile(fileName);
        _midiPlayer->output();
    }



    if(!fileName.isEmpty()&& !fileName.isNull())
    {
        ui->pushButtonPlay->setEnabled(true);
        ui->pushButtonPause->setEnabled(false);
        ui->sliderTimeline->setEnabled(false);
        ui->doubleSpinBoxSpeed->setEnabled(true);
        ui->BoutonConversion->setEnabled(true);
    }



//Modification du label_Acces afin de permettre d'afficher le chemin d'accès

    ui->labelCheminAcces->setText(fileName);

//Création d'une variable Nomfichier Afin de pouvoir récuperer le chemin d'accès pour future utilisation
    NomFichier=fileName;


}

void MainWindow::on_BoutonDeveloppeur_clicked()
{
//Fait apparaitre le mode développeur (Logiciel de travail)

    system("D:\\Snir2\\Serre\\Extraction_piste_son_V05\\Software\\Working_Software\\qtmidieditor.exe");

}


void MainWindow::on_BoutonConversion_clicked()
{
//Création, d'un dialog Enregistrer sous afin de récuperer le nom du fichier que l'on souhaite créer

QFileDialog dialog(NULL, tr("Enregistrer sous"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Sheet File"));
    if (dialog.exec())
    {
        QString fileName = dialog.selectedFiles().at(0);


//Nom du fichier mis dans une variable "NomEnregistrer"

        NomEnregistrer=fileName;

    }


//Mise en place de la ligne de code pour le cmd afin de réalisé la création de la partition
//Fonctionnement de la commande ==> "sheet.exe songs/sample.mid sample"
//"Sheet.exe" = Logiciel mis en place pour réaliser la mise en page de la partition
//"songs/sample.mid" = Chemin d'accès du fichier midi
//"Sample" = Nom du fichier de partition que l'on souhaite créer


    QString CurrentDir = QDir::currentPath();
    QString Nameexe2 = "Sheet.exe";
    QString exe = CurrentDir + "/Software/" + Nameexe2;
    qDebug() << exe;

QString s2 = NomFichier;
QString s3 = s2.toLocal8Bit().data();
QString s4 = NomEnregistrer;
QString s5 = s4.toLocal8Bit().data();
QString s6 = exe +" "+ s3 +" "+s5;
QString s7 = s4 +"_1.png";
QString s8 = s4 +".svg";
system(s6.toLocal8Bit().data());
AffichagePrevisualisation=s7;
Previsualisation();
OuvrirDialogue();

ui->EnregistrerPDF->setEnabled(true);
ui->Imprimer->setEnabled(true);
ui->BoutonPartition->setEnabled(true);
ui->BoutonModifier->setEnabled(true);
}



//Fonction qui permet d'ouvrir une partition au choix
void MainWindow::on_BoutonPartition_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open file"), ".", tr("Image (*.png);;Any files (*)"));
    label1 = new QLabel;

    label1->setPixmap(QPixmap(fileName));

    label1->show();

}




//Test ouvrir dialogue a choix multiple

void MainWindow::OuvrirDialogue()

{
    int reponse = QMessageBox::question(this, "Partition", "Souhaitez-vous imprimer la partition ?", QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Partition", "Lancement de l'impression");

        SuiteConversion();
        ApercuAvantImpression();
    }
    else if (reponse == QMessageBox::No)
    {

        SuiteConversion();
    }
}

//Fonction pour la fenetre "A Propos"

void MainWindow::about()
{
    AboutDialog* d = new AboutDialog(this);
    d->setModal(true);
    d->show();
}

void MainWindow::Notice()
{
    /*
    AboutNotice* d = new AboutNotice(this);
    d->setModal(true);
    d->show();
    */
QString CurrentDir = QDir::currentPath();
QString NameChm = "Extraction_piste_son_projet.chm";
QString DirChm = CurrentDir + "/Manual/" + NameChm;
qDebug() << DirChm;
QByteArray ba = DirChm.toLocal8Bit();
  const char *c_str2 = ba.data();
system(c_str2);
qDebug() << c_str2;
//system("pause");



}


//Fonction pour la prévisualisation de la partition dans un label

void MainWindow::Previsualisation()
{
    ui->labelPrevisualisation->setPixmap(QPixmap(AffichagePrevisualisation).scaledToWidth(261, Qt::SmoothTransformation));
    ui->labelPrevisualisation->setFixedSize(261,341);
    ui->labelPrevisualisation->show();

}


//Fonction pour agrandir l'image de la partition qui est contenu dans le label

void MainWindow::ClickLabel()
{

label2 = new QLabel;

label2->setPixmap(QPixmap(AffichagePrevisualisation).scaledToWidth(840, Qt::SmoothTransformation));
label2->setFixedSize(840,1090);
label2->show();

}


//Fonction pour jouer un fichier audio (Ici un fichier .wav)

void MainWindow::on_BoutonSonore_clicked()
{
    QSound *son = new QSound("D:\\Snir2\\Serre\\Extraction_piste_son_V05\\APP01.WAV");
    son->play();
}

//Fonction pour créer un fichier PDF à partir d'une image

void MainWindow::WritePdf()
{

    QString fileName2 = QFileDialog::getOpenFileName(this,
    tr("Ouvrir Image"), ".", tr("Image (*.png);;Any files (*)"));
    NomImage = fileName2;


    QFileDialog dialog(NULL, tr("Enregistrer en PDF"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Format PDF (*.pdf)"));

    if (dialog.exec())
    {
        QString fileName3 = dialog.selectedFiles().at(0);
        if(QFileInfo(fileName3).suffix().isEmpty())
        fileName3 += ".pdf";
        NomPDF = fileName3;
    }


    const QString fileName(NomPDF);
    const QImage image(NomImage);
    const QPoint imageCoordinates(0,0);

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    QPainter painter(&pdfWriter);
    painter.scale(11.0, 11.0);

    for (int i=0; i<=1; ++i)
    {
        painter.drawImage(imageCoordinates, image);
    }
}

//Lancement de la fonction "WritePdf" Sur le click d'un bouton
void MainWindow::on_EnregistrerPDF_clicked()
{
    WritePdf();
}


//Lancement du logiciel de modification (Temporaire / WIP)

void MainWindow::on_BoutonModifier_clicked()
{
    //LOGICIEL TEMPORAIRE ---------------- WORK IN PROGRESS

    system("D:\\Snir2\\Serre\\Extraction_piste_son_V05\\Software\\MidiEditor.exe");

    //LOGICIEL TEMPORAIRE ---------------- WORK IN PROGRESS
}

//Fonction qui permet l'affichage du dialogue se situant au lancement du programme afin de guider l'utilisateur

void MainWindow::Information()
{


    QMessageBox::information(this,
        tr("Extraction Piste Son"),
        tr("Projet réalisé en 200 Heures pour le diplome BTS SNIR à Dhuoda"));

    QMessageBox::information(this,
        tr("Extraction Piste Son"),
        tr("Il s'agit de la première version officiel. Il existe encore des problèmes qui peuvent nuire a votre expérience sur le logiciel. Une notice est disponible afin de vous guidez dans le programme"));



}

//Fonction ------------W I P---------------"Aperçu avant impression"

void MainWindow::ApercuAvantImpression()
{
    QImage image(AffichagePrevisualisation);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPrinter::A4);
        QPrintDialog *dialog = new QPrintDialog(&printer);
        if (dialog->exec() == QDialog::Accepted)
        {               QPainter painter (&printer);
                        painter.begin(&printer);
                        painter.drawImage (QRect(0,0,5000,7000),image);
                        painter.end();

        }
}



//Fonction ------------W I P---------------"Aperçu avant impression"


//Fonction "Affichage Edition"

void MainWindow::AffichageEdition()
{
    QSvgRenderer renderer(QString(AffichageModification));
    ui->labelEdition->setPixmap(QPixmap(AffichageModification).scaledToWidth(681, Qt::SmoothTransformation));
    ui->labelEdition->setFixedSize(681,411);
    ui->labelEdition->show();

}

//Méthode pour effectuer le script de l'affichage de l'edition
void MainWindow::SuiteConversion()
{
    QString CurrentDir = QDir::currentPath();
    QString Nameexe1 = "Mid2svg.exe";
    QString exe = CurrentDir + "/Software/Piano_roll/" + Nameexe1;
    qDebug() << exe;
    QString s2 = NomFichier;
    QString s3 = s2.toLocal8Bit().data();
    QString s4 = NomEnregistrer;
    QString s5 = s4.toLocal8Bit().data();
    QString s6 = exe +" "+ s3 +" > "+s5+".svg";
    QString s7 = s5+".svg";
    system(s6.toLocal8Bit().data());
    AffichageModification=s7;
    AffichageEdition();
}

void MainWindow::onOutputSelected(QAction* action_)
{
    int num = action_->text().split(".")[0].toInt();
    this->setOutput(num);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), ".", tr("MIDI files (*.mid *.midi);;Any files (*)"));
    if( fileName.size() )
    {
        this->openFile(fileName);
        _midiPlayer->play();
    }
}

void MainWindow::openFile(const QString& path_)
{
    if(_midiPlayer->isPlaying())
        _midiPlayer->pause();

    if(_midiFile)
        delete _midiFile;

    _midiFile = new CxxMidi::File(path_.toStdString().c_str());
    _midiPlayer->setFile(_midiFile);

    _finalTimePoint = _midiFile->duration().toPoint();
    ui->labelTotal->setText(_finalTimePoint.toTimecode().c_str());

    this->centralWidget()->setDisabled(false);
}

void MainWindow::onPlayClicked()
{
    _midiPlayer->play();
ui->sliderTimeline->setEnabled(true);
ui->pushButtonPause->setEnabled(true);
}

void MainWindow::onPauseClicked()
{
    _midiPlayer->pause();
ui->sliderTimeline->setEnabled(false);
ui->pushButtonPause->setEnabled(false);

}

void MainWindow::playerFinished()
{
    _midiPlayer->goTo(CxxMidi::Time::Point::zero());
    _midiPlayer->play();
}

void MainWindow::updateTimeCode(CxxMidi::Time::Point time_)
{
    _currentTimePoint = time_;
    ui->labelTime->setText(time_.toTimecode().c_str());

    if(!_sliderLocked)
    {
        double normPos = _currentTimePoint / _finalTimePoint;
        ui->sliderTimeline->setValue(100*normPos);
    }
}

void MainWindow::onSpeedChange(double speed_)
{
    _midiPlayer->setSpeed(speed_);
}

void MainWindow::onTimeSliderPressed()
{
    _sliderLocked = true;
}

void MainWindow::onTimeSliderReleased()
{
    double val = ui->sliderTimeline->value();
    double size = ui->sliderTimeline->maximum();
    double pos = val/size;
    CxxMidi::Time::Point tp =  _midiFile->duration().toPoint();
    tp*=pos;


    bool wasPlaying = _midiPlayer->isPlaying();
    _midiPlayer->pause();
    _midiPlayer->goTo(tp);
    if(wasPlaying)
        _midiPlayer->play();

    _sliderLocked = false;



}

void MainWindow::setOutput(int num_)
{
    bool wasPlaying = _midiPlayer->isPlaying();

    if(wasPlaying)
        _midiPlayer->pause();
    CxxMidi::Time::Point tp = _midiPlayer->currentTimePos();
    _midiOutput->openPort(num_);
    _midiPlayer->goTo(tp);
    if(wasPlaying)
        _midiPlayer->play();
}

//Fonction permettant l'impression

void MainWindow::on_Imprimer_clicked()
{
    ApercuAvantImpression();
}






















// ----------------------------------------------CODE MILON---DEBUT----------------------------------------------






QString cledesol;
QString cledefa;




void MainWindow::Ouvrir_fichier2()
{

    QString nomfichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Document texte (*.mid)"); //Onglet pour ouvrir le fichier
    QFile fichier(nomfichier); //On creer un objet QFile


        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) //Ouverture du fichier en lecture seul et le type de donnée est du texte. On vérifie que le fichier s'ouvre bien
             {QMessageBox::critical(this, "Erreur de lecture", "Nous n'avons pas réussi à lire le fichier.");
                 return;}
        else QMessageBox::information(this, "Lecture du fichier", "Le fichier est désormais ouvert.");


        QTextStream flux(&fichier); //On creer un objet QTextStream à partir de l'objet QFile


            this->openFile(nomfichier);
            _midiPlayer->output();
            if(!nomfichier.isEmpty()&& !nomfichier.isNull())
            {
                ui->pushButtonPlay->setEnabled(true);
                ui->pushButtonPause->setEnabled(false);
                ui->sliderTimeline->setEnabled(false);
                ui->doubleSpinBoxSpeed->setEnabled(true);
                ui->BoutonConversion->setEnabled(true);
            }
    ui->labelCheminAcces->setText(nomfichier);

        //labeltest = new QLabel(this); //On creer un nouveau label
        //labeltest->setText(QString(fichier.readAll())); //Le label affiche le contenu du fichier ouvert précédemment
        //labeltest->setGeometry(QRect(70, 220, 341, 41)); //Le label crée est dans un rectangle de la dimension choisie en paramètre
        //labeltest->show(); //Affiche le label

        QString donnees = fichier.readAll();
        int taille = donnees.size();
        QPushButton *Noteno[50];
        int decallagex = 0;
        int decallagey = 0;
        int i;
        for(i=0; taille>i; i++)
      {

             Noteno[i] = new QPushButton(this);
             QChar note = donnees.at(i);

             decallagex = i*25 + 55;

        switch(note.toLatin1()) // En fonction de la note, déplacement sur l'axe des ordonnées
        {
            case 'C':
                decallagey = 108;

            break;

            case 'D':
                decallagey = 103;

            break;

            case 'E':
                decallagey = 100;

            break;

            case 'F':
                decallagey = 97;

            break;

            case 'G':
                decallagey = 93;
            break;

            case 'A':
                decallagey = 90;
            break;

            case 'B':
                decallagey = 86;
            break;

        }
/*
            Noteno[i]->setIcon(QPixmap(":/Icon/noire.png").scaledToWidth(9, Qt::SmoothTransformation));
            Noteno[i]->setIconSize(QSize(95,95));
            Noteno[i]->setGeometry(QRect(decallagex,210,25,41));
            Noteno[i]->setFlat(true);

           Noteno[i]->show();

            labeltest = new QLabel(this); //On creer un nouveau label
            labeltest->setText(donnees); //Le label affiche le contenu du fichier ouvert précédemment
            labeltest->setGeometry(QRect(720, 250, 341, 41)); //Le label crée est dans un rectangle de la dimension choisie en paramètre
            labeltest->show(); //Affiche le label
*/

       }

}

/*void MainWindow:: paintEvent(QPaintEvent *e) //Méthode affichant la portée. Elle affiche ainsi 2 rectangles : un vide et un rempli par des lignes horizontales.
{
    QPainter painter(this);
{
    int left = 200;
    int top = 100;
    int width = 460;
    int height = 30;


    // r1 and r2 are same
    QRect r1(left, top, width, height);

    painter.setPen(Qt::black);
    painter.drawRect(r1);
    QBrush brush(Qt::black, Qt::HorPattern);
    painter.fillRect(r1, brush);
}
}

*/

void MainWindow::AffichageCle() //Affiche la clé
{

     cledefa=":/Icon/cledefa.png";
     cledesol=":/Icon/cledesol.png";

     ui->labelCle->setPixmap(QPixmap(cledesol).scaledToWidth(14, Qt::SmoothTransformation));
     ui->labelCle->setFixedSize(55,41);
     ui->labelCle->show();

}


void MainWindow::AffichageNote2() //Affiche les notes
{

     ui->labelNote->setPixmap(QPixmap().scaledToWidth(14, Qt::SmoothTransformation));
     ui->labelNote->setFixedSize(41,41);
     ui->labelNote->show();

}


void MainWindow::on_BoutonOuvrirMilon_clicked() //Ouvre le navigateur pour ouvrir un fichier
{
     Ouvrir_fichier2();

}

void MainWindow::on_BoutonSaveMilon_clicked() //Permet de suavegarder le fichier modifié
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Version de Milon?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      QString path = QFileDialog::getSaveFileName(this, "Enregistrer sous...", QDir::homePath(), "Texte (*.txt)");
    } else {
        WritePdf();
    }
  }



void MainWindow::on_BoutonModifierMilon_clicked()
{
    modifnote *fenetre = new modifnote;
    fenetre->show();
}



//----------------------------------------------CODE MILON---FIN--------------------------------------------





//----------------------------------------------CODE WYBAUW---DEBUT-----------------------------------------


void MainWindow::Ouvrir_fichier3()
{

    Application execution;
    int Frequence=0;

    QString nomfichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Document texte (*.mid)"); //Onglet pour ouvrir le fichier
   // Frequence =  execution.LireEnteteWAVE(nomfichier);

    QFile fichier(nomfichier); //On creer un objet QFile


        if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) //Ouverture du fichier en lecture seul et le type de donnée est du texte. On vérifie que le fichier s'ouvre bien
             {QMessageBox::critical(this, "Erreur de lecture", "Nous n'avons pas réussi à lire le fichier.");
                 return;}
        else QMessageBox::information(this, "Lecture du fichier", "Le fichier est désormais ouvert.");
       QSpinBox *precisionSpinBox = new QSpinBox;
           precisionSpinBox->setRange(0, 100);
           precisionSpinBox->setValue(Frequence);
}


void MainWindow::on_BoutonOuvrirWybauw_clicked()
{
    Application execution;
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Musique"), "/home", tr("Audio Files (*.wav)"));
    int Frequence;
    //Frequence = execution.LireEnteteWAVE(fileName);
}


void MainWindow::on_IsolerFreqBasseWybauw_clicked()
{
    QProcess process1;
    process1.start("C:\\Users\\milon\\Desktop\\test.bat");
}


//----------------------------------------------CODE WYBAUW---FIN--------------------------------------------




































//Destructeur de classe

MainWindow::~MainWindow()
{
    delete ui;
}









