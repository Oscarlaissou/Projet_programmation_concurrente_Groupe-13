#include "commis2.h"

#include "human.h"  // Inclure la classe human
#include <QTimer>
commis2::commis2(QWidget *parent) : QWidget(parent) {

}

// void commis2::affichercommis2(QWidget *rightPanel) {
//     // Créer un QLabel pour afficher l'image du cuisinier
//     QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_partie.png");

//     QLabel *label38 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
//     label38->setPixmap(pixmap4);
//     label38->setScaledContents(true);

//     // Positionner correctement l'image dans 'rightPanel'
//     label38->setGeometry(260, 200, 30, 40);
//     label38->setStyleSheet("border: none;");
//     label38->setFrameStyle(QFrame::NoFrame);
//     label38->setFocusPolicy(Qt::NoFocus);


//     // S'assurer que le label est visible et au premier plan
//     label38->raise();
//     label38->show();

//     // Créer un objet 'human' pour déplacer le personnage
//     human *hum = new human(rightPanel);

//     // Position de départ (position initiale du cuisinier)
//     QPoint startPos(260, 200);

//     // Position de destination (par exemple, vers une autre partie du panel)
//     QPoint endPos(50, 450);  // Exemple de destination

//     // Durée du mouvement (en millisecondes)
//     int duration = 8000;

//     int delayBeforeMove = 5200;  // Par exemple, 2 secondes (2000 ms)

//     // Créer un QTimer pour démarrer l'animation après le délai
//     QTimer *timer = new QTimer(this);
//     connect(timer, &QTimer::timeout, [=]() {
//         // Lorsque le timer atteint son délai, lancer le mouvement
//         hum->moveLoop(label38, startPos, endPos, duration);
//     });
//     // Afficher une nouvelle image ou effectuer une autre action
//     QLabel *finalLabel = new QLabel(rightPanel);
//     QPixmap finalPixmap(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/lave_vaissele.png");
//     finalLabel->setPixmap(finalPixmap);
//     finalLabel->setScaledContents(true);

//     // Positionner l'image finale
//     finalLabel->setGeometry(50, 450, 30, 40);
//     finalLabel->setStyleSheet("border: none;");
//     finalLabel->raise();
//     finalLabel->show();
//     // Démarrer le timer avec le délai spécifié
//     timer->start(delayBeforeMove);
// }


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

    int delayBeforeMove = 8000;  // Temps d'attente avant de démarrer le mouvement

    // Créer un QTimer pour démarrer l'animation après un délai
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label38, startPos, endPos, duration);

        // Vérifier si le label a atteint la position finale à la fin du déplacement
        QTimer::singleShot(duration, [=]() {
            if (label38->geometry().topLeft() == endPos) {
                // Afficher l'image finale
                QLabel *finalLabel = new QLabel(rightPanel);
                QPixmap finalPixmap(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/plat.png");
                finalLabel->setPixmap(finalPixmap);
                finalLabel->setScaledContents(true);

                // Positionner l'image finale
                finalLabel->setGeometry(50, 450, 30, 40);
                finalLabel->setStyleSheet("border: none;background: transparent;" );
                finalLabel->raise();
                finalLabel->show();
                // Masquer l'image après 2 secondes
                QTimer::singleShot(3500, [=]() {
                    finalLabel->hide(); // Masquer l'image
                    delete finalLabel;  // Libérer la mémoire si nécessaire
                });
            }
        });
    });
    timer->start(delayBeforeMove); // Attendre 5200 ms avant de lancer le mouvement
}


