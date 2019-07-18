#ifndef PLAYERFINISHEDCALLBACK_H
#define PLAYERFINISHEDCALLBACK_H

#include <QObject>

#include <cxxmidi/player/abstract.hpp>
#include <cxxmidi/callback.hpp>

/*! \file playerfinishedcallback.h
Permet de réinitialiser le lecteur afin d'éviter qu'il reste bloqué
Ce fichier ce sert de la bibliothèque "CxxMidi" Afin de permet le bon fonctionnement des fonctions
\author Serre
\date 12/04/2019 Création du fichier
*/

class PlayerFinishedCallback: public QObject, public CxxMidi::Callback
{
/*! \brief Le compilateur de méta-objets, moc, est le programme qui gère les extensions C++ de Qt.
*/
    Q_OBJECT

public:
/*! \brief Fonction PlayerFinishedCallback <br>
Permet la creation de la fonction qui nous servira a empecher un bloquage du lecteur et de le rappeler
*/

    PlayerFinishedCallback(QObject *parent_=0);

/*! \brief  Le premier () est le nom de l'opérateur -
c'est l'opérateur qui est appelé lorsque vous utilisez () sur l'objet.
Le second () est pour les paramètres, il n'y en a pas.
*/

    virtual void operator()();

signals:
/*! \brief Il s'agit d'un signal qui s'effectue quand le lecteur a fini sa lecture
*/

    void playerFinished();

};

#endif // PLAYERFINISHEDCALLBACK_H
