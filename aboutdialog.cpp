
#include "AboutDialog.h"

#include <QApplication>
#include <QFile>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QTextBrowser>
#include <QTextStream>
#include <QVariant>


// AboutDialog Permet d'afficher une fenetre secondaire contenant divers information
// a propos du logiciel et de leur créateur ainsi que les logiciels et bibliothèque tiers

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{

    setMinimumWidth(550);
    setMaximumHeight(450);
    setWindowTitle(tr("About"));
    setWindowIcon(QIcon(":/Icon/AboutIcon.png"));
    QGridLayout* layout = new QGridLayout(this);

    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":/Icon/AboutIcon.png").scaledToWidth(80, Qt::SmoothTransformation));
    icon->setFixedSize(80, 80);
    layout->addWidget(icon, 0, 0, 3, 1);

    QLabel* title = new QLabel("<h1>Extraction Piste Son</h1>");
    layout->addWidget(title, 0, 1, 1, 2);
    title->setStyleSheet("color: black");

    QLabel* version = new QLabel("Version: 1.0");
    layout->addWidget(version, 1, 1, 1, 2);
    version->setStyleSheet("color: black");

    QScrollArea* a = new QScrollArea(this);
    QString contributors = "<p>";
    QString delim = "";
    foreach (QString contributor, *loadContributors()) {
        contributors = contributors + delim + contributor;
        delim = "<br/>";
    }
    contributors = contributors + "</p>";

    QLabel* content = new QLabel("<html>"
                                 "<body>"
                                 "<h3>Auteur</h3>"
                                 "<p>"
                                 "Serre Lucas<br>"
                                 "Email: lucas.serre@imerir.com<br>"
                                 "Website: <a href=\"www.nocturnalgaming.live\">www.nocturnalgaming.live</a><br>"
                                 "</p>"
                                 "<h3>Contributeur</h3>"
                                 "<p>"
                                 "Lucas Serre<br>"
                                 "Camille Milon<br>"
                                 "Killian Wybauw<br>"
                                 "</p>"

        "<h3>Credits</h3>"
        "<p>"
        "IHM réalisé par Lucas Serre<br>"
        "</p>"
        "<h3>Bibliothèques tierces</h3>"
        "<p>"
        "RtMidi (Copyright (c) 2003-2014 Gary P. Scavone)<br>"
        "MidiEditor (Copyright (C) 2010  Markus Schwenk)<br>"
        "CxxMidi v0.2 (Copyright (c) 2003-2014 Gary P. Scavone)<br>"
        "</p>"
        "</body>"
        "</html>");
    a->setWidgetResizable(true);
    a->setWidget(content);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(a, 2, 1, 2, 2);
    content->setStyleSheet("color: black; background-color: white; padding: 5px");

    content->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    content->setOpenExternalLinks(true);

    layout->setRowStretch(3, 1);
    layout->setColumnStretch(1, 1);

    QFrame* f = new QFrame(this);
    f->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    layout->addWidget(f, 4, 0, 1, 3);

    QPushButton* close = new QPushButton("Close");
    layout->addWidget(close, 5, 2, 1, 1);
    connect(close, SIGNAL(clicked()), this, SLOT(hide()));
}

QList<QString>* AboutDialog::loadContributors()
{

    QList<QString>* list = new QList<QString>();

    QFile file(":/CONTRIBUTORS");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return list;

    QTextStream in(&file);
    while (!in.atEnd()) {
        list->append(in.readLine());
    }

    return list;
}
