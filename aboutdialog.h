#ifndef ABOUTDIALOG_H_
#define ABOUTDIALOG_H_

#include <QDialog>
#include <QList>
#include <QObject>
#include <QString>
#include <QWidget>

/*! \file aboutdialog.h
Gère l'accès (lecture) de la fenetre de dialog
Doit effectuer les opérations de lecture de la fenetre de dialog
Celle si contient les information concernant les développeur de l'application "Extraction_piste_son_V05" ainsi
que divers information sur les application tiers utilisé
\author Serre
\date 03/04/2019 Création du fichier
*/


class AboutDialog : public QDialog {
/*! \brief Le compilateur de méta-objets, moc, est le programme qui gère les extensions C++ de Qt.
 */
    Q_OBJECT

public:
/*! \brief Fonction AboutDialog <br>
  Permet la creation de la fenetre de dialog contenant les information voulu
 */
    AboutDialog(QWidget* parent = 0);

private:
/*! \brief Defini la fonction "loadContributors" <br>
  Permet de récuperer les information venant d'un fichier texte afin d'integrer les contributeurs
 */
    QList<QString>* loadContributors();
};

#endif
