#include<QTimer>
#include "plongeur.h"

plongeur::plongeur(QWidget *parent) : QWidget(parent) {

}

void plongeur::afficherplongeur(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du serveur
    QPixmap pixmap5(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/plongeur.png");


    QLabel *label35 = new QLabel(rightPanel);  // Utiliser 'leftPanel' comme parent
    label35->setPixmap(pixmap5);
    label35->setScaledContents(true);

    // Positionner correctement l'image dans 'leftPanel'
    label35->setGeometry(250, 50, 20, 60);
    label35->setStyleSheet("border: none;");
    label35->setFrameStyle(QFrame::NoFrame);
    label35->setFocusPolicy(Qt::NoFocus);


    // S'assurer que le label est visible et au premier plan
    label35->raise();
    label35->show();
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(250, 400);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(350, 400);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    // Déplacer le cuisinier avec l'animation et l'effet de marche
    int delayBeforeMove = 0;  // Par exemple, 2 secondes (2000 ms)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label35, startPos, endPos, duration);
    });

    // Démarrer le timer avec le délai spécifié
    timer->start(delayBeforeMove);}
