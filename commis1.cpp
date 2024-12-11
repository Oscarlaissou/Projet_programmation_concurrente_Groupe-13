#include "commis1.h"


#include "human.h"  // Inclure la classe human
#include <QTimer>
commis1::commis1(QWidget *parent) : QWidget(parent) {

}

void commis1::affichercommis1(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/commis2.png");

    QLabel *label37 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label37->setPixmap(pixmap4);
    label37->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label37->setGeometry(450, 200, 30, 40);
    label37->setStyleSheet("border: none;");
    label37->setFrameStyle(QFrame::NoFrame);
    label37->setFocusPolicy(Qt::NoFocus);


    // S'assurer que le label est visible et au premier plan
    label37->raise();
    label37->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(450, 200);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(440, 600);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    int delayBeforeMove = 5200;  // Par exemple, 2 secondes (2000 ms)

    // Créer un QTimer pour démarrer l'animation après le délai
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label37, startPos, endPos, duration);
    });

    // Démarrer le timer avec le délai spécifié
    timer->start(delayBeforeMove);}

