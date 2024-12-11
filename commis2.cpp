#include "commis2.h"

#include "human.h"  // Inclure la classe human
#include <QTimer>
commis2::commis2(QWidget *parent) : QWidget(parent) {

}

void commis2::affichercommis2(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_partie.png");

    QLabel *label38 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label38->setPixmap(pixmap4);
    label38->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label38->setGeometry(260, 200, 30, 40);
    label38->setStyleSheet("border: none;");
    label38->setFrameStyle(QFrame::NoFrame);
    label38->setFocusPolicy(Qt::NoFocus);


    // S'assurer que le label est visible et au premier plan
    label38->raise();
    label38->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(260, 200);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(50, 450);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    int delayBeforeMove = 5200;  // Par exemple, 2 secondes (2000 ms)

    // Créer un QTimer pour démarrer l'animation après le délai
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label38, startPos, endPos, duration);
    });

    // Démarrer le timer avec le délai spécifié
    timer->start(delayBeforeMove);}
// Créer un QTimer pour déclencher l'affichage de l'image à la fin du mouvement
// QTimer::singleShot(duration, [=]() {
//     // Créer un QLabel pour afficher une image à la position finale
//     QLabel *finalLabel = new QLabel(rightPanel);
//     QPixmap finalPixmap(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/gants.png");
//     finalLabel->setPixmap(finalPixmap);
//     finalLabel->setScaledContents(true);
//     finalLabel->setGeometry(endPos.x(), endPos.y(), 30, 40);  // Position finale
//     finalLabel->setStyleSheet("border: none;");
//     finalLabel->raise();
//     finalLabel->show();
// });
