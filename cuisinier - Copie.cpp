#include "cuisinier.h"
#include "human.h"

cuisinier::cuisinier(QWidget *parent) : QWidget(parent) {

}

void cuisinier::affichercuisinier(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4("F:/X3/programmation concurrente/restaurant_projet/resto_projet/images/MasterChefDown.png");

    QLabel *label33 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label33->setPixmap(pixmap4);
    label33->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label33->setGeometry(350, 71, 15, 30);

    // S'assurer que le label est visible et au premier plan
    label33->raise();
    label33->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(350, 71);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(400, 100);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 4000;

    // Déplacer le cuisinier avec l'animation et l'effet de marche
    hum->moveLoop(label33, startPos, endPos, duration);
}
