#include "chefdepartie.h"

#include "human.h"  // Inclure la classe human
#include <QTimer>
chefdepartie::chefdepartie(QWidget *parent) : QWidget(parent) {

}

void chefdepartie::afficherchefpartie(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_partie.png");

    QLabel *label36 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label36->setPixmap(pixmap4);
    label36->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label36->setGeometry(250, 200, 30, 40);
    label36->setStyleSheet("border: none;");
    label36->setFrameStyle(QFrame::NoFrame);
    label36->setFocusPolicy(Qt::NoFocus);


    // S'assurer que le label est visible et au premier plan
    label36->raise();
    label36->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(250, 200);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(100, 200);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    int delayBeforeMove = 5200;  // Par exemple, 2 secondes (2000 ms)

    // Créer un QTimer pour démarrer l'animation après le délai
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label36, startPos, endPos, duration);
    });

    // Démarrer le timer avec le délai spécifié
    timer->start(delayBeforeMove);}
