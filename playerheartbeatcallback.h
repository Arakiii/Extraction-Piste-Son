#ifndef PLAYERHEARTBEATCALLBACK_H
#define PLAYERHEARTBEATCALLBACK_H

#include <QObject>

#include <cxxmidi/player/abstract.hpp>
#include <cxxmidi/callback.hpp>
#include <cxxmidi/time/point.hpp>


/*! \file playerheartbeatcallback.h
Permet le bon fontionnement du slider gérant la notion du temps afin de pouvoir ce déplacer dans la musique
Ainsi qu'un bon de fonctionnement du lecteur MIDI
Ce fichier ce sert de la bibliothèque "CxxMidi" Afin de permet le bon fonctionnement des fonctions
\author Serre
\date 12/04/2019 Création du fichier
*/

class PlayerHeartbeatCallback : public QObject , public CxxMidi::Callback
{
/*! \brief Le compilateur de méta-objets, moc, est le programme qui gère les extensions C++ de Qt.
*/
    Q_OBJECT

public:

/*! \brief Fonction PlayerHeartbeatCallback <br>
Permet la creation de la fonction qui permet le bon fonctionnement du controle de temps (timeline)
*/
    PlayerHeartbeatCallback(CxxMidi::Player::Abstract *player_,QObject *parent_=0);

/*! \brief  Le premier () est le nom de l'opérateur -
c'est l'opérateur qui est appelé lorsque vous utilisez () sur l'objet.
Le second () est pour les paramètres, il n'y en a pas.
*/
    virtual void operator ()();

signals:
/*! \brief Il s'agit d'un signal qui permet de modifier l'endroit ou l'on se trouve dans la musique et de ce déplacer a n'importe quelle moment
*/
    void playerTimeChanged(CxxMidi::Time::Point time_);

private:
/*! \brief Il s'agit d'une fonction reprise de la bibliothèque "CxxMidi" qui permet le bon fonctionnement du lecteur MIDI
*/
    CxxMidi::Player::Abstract *_player;
};

#endif // PLAYERHEARTBEATCALLBACK_H
