// #include "ChefDePatisserie.h"
// #include <QThread>


// //ChefDePatisserie::ChefDePatisserie(const QString &name) : name(name) {}
// ChefDePatisserie::ChefDePatisserie(const QString& chefName) : name(chefName) {}

// void ChefDePatisserie::addDessertToPrepare(const QString &dessert) {
//     dessertsToPrepare.enqueue(dessert);
//     qDebug() << name << "a ajouté le dessert à la file:" << dessert;
// }

// void ChefDePatisserie::prepareDessertsBeforeOpening() {
//     while (!dessertsToPrepare.isEmpty()) {
//         QString dessert = dessertsToPrepare.dequeue();
//         qDebug() << name << "prépare le dessert:" << dessert;
//         // Simuler un temps de préparation (exemple : attendre une seconde par dessert)
//         QThread::sleep(1); // À adapter si vous avez un système de simulation d'événements
//     }
//     qDebug() << name << "a terminé la préparation des desserts avant l'ouverture.";
// }
// class ChefDePatisserie {
// public:
// QString ChefDePatisserie::getNextDessert() const {
//     if (!dessertsToPrepare.isEmpty()) {
//         return dessertsToPrepare.front();
//     }
//     return "Aucun dessert en attente.";
// }
// };


// #include "ChefDePatisserie.h"
// #include <QThread>
// #include <QDebug>

// ChefDePatisserie::ChefDePatisserie(const QString& chefName) : name(chefName) {}

// void ChefDePatisserie::addDessertToPrepare(const QString &dessert) {
//     dessertsToPrepare.enqueue(dessert);
//     qDebug() << name << "a ajouté le dessert à la file:" << dessert;
// }

// void ChefDePatisserie::prepareDessertsBeforeOpening() {
//     while (!dessertsToPrepare.isEmpty()) {
//         QString dessert = dessertsToPrepare.dequeue();
//         qDebug() << name << "prépare le dessert:" << dessert;
//         QThread::sleep(1); // Simuler un temps d'attente
//     }
//     qDebug() << name << "a terminé la préparation des desserts avant l'ouverture.";
// }

// QString ChefDePatisserie::getNextDessert() const {
//     if (!dessertsToPrepare.isEmpty()) {
//         return dessertsToPrepare.front();
//     }
//     return "Aucun dessert en attente.";
// }


#include "ChefDePatisserie.h"
#include "human.h"  // Inclure la classe human
#include <QTimer>
chefdepatisserie::chefdepatisserie(QWidget *parent) : QWidget(parent) {

}

void chefdepatisserie::afficherpatissier(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_patisserie.png");

    QLabel *label34 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label34->setPixmap(pixmap4);
    label34->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label34->setGeometry(350, 200, 30, 40);
    label34->setStyleSheet("border: none;");
    label34->setFrameStyle(QFrame::NoFrame);
    label34->setFocusPolicy(Qt::NoFocus);


    // S'assurer que le label est visible et au premier plan
    label34->raise();
    label34->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(350, 200);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(540, 200);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    int delayBeforeMove = 3500;  // Par exemple, 2 secondes (2000 ms)

    // Créer un QTimer pour démarrer l'animation après le délai
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        // Lorsque le timer atteint son délai, lancer le mouvement
        hum->moveLoop(label34, startPos, endPos, duration);
    });

    // Démarrer le timer avec le délai spécifié
    timer->start(delayBeforeMove);}
