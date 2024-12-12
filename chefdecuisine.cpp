// #include "ChefDeCuisine.h"

// //ChefDeCuisine::ChefDeCuisine(const QString &name) : name(name) {}
// ChefDeCuisine::ChefDeCuisine(const QString& chefName) : name(chefName) {}

// void ChefDeCuisine::receiveOrder(const QString &table, const QString &dish) {
//     orders[table].append(dish);
//     qDebug() << name << "a reçu une commande pour la table:" << table << "->" << dish;
// }

// void ChefDeCuisine::processOrders() {
//     qDebug() << name << "traite les commandes en regroupant les plats similaires.";
//     QMap<QString, int> groupedOrders;

//     // Grouper les commandes similaires
//     for (auto it = orders.begin(); it != orders.end(); ++it) {
//         for (const QString &dish : it.value()) {
//             groupedOrders[dish]++;
//         }

//         // for (auto &order : orders) {
//         //     qDebug() << "Traitement de la commande pour" << order.first << ":" << order.second;
//         // }
//     }

//     // Afficher les commandes regroupées
//     for (auto it = groupedOrders.begin(); it != groupedOrders.end(); ++it) {
//         qDebug() << "Préparer:" << it.value() << "x" << it.key();
//     }
// }

// void ChefDeCuisine::assignTasksToChefs() {
//     qDebug() << name << "assigne les tâches aux chefs de partie.";
//     // Simulation d'assignation de tâches
//     for (auto it = orders.begin(); it != orders.end(); ++it) {
//         qDebug() << "Envoyer les plats pour la table" << it.key() << "aux chefs de partie.";
//     }
// }

#include "ChefDeCuisine.h"
#include "human.h"  // Inclure la classe human

chefdecuisine::chefdecuisine(QWidget *parent) : QWidget(parent) {

}

void chefdecuisine::affichercuisinier(QWidget *rightPanel) {
    // Créer un QLabel pour afficher l'image du cuisinier
    QPixmap pixmap4(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_cuisine.png");

    QLabel *label33 = new QLabel(rightPanel);  // Utiliser 'rightPanel' comme parent
    label33->setPixmap(pixmap4);
    label33->setScaledContents(true);

    // Positionner correctement l'image dans 'rightPanel'
    label33->setGeometry(20, 300, 30, 40);
    label33->setStyleSheet("border: none;");
    label33->setFrameStyle(QFrame::NoFrame);
    label33->setFocusPolicy(Qt::NoFocus);

    // S'assurer que le label est visible et au premier plan
    label33->raise();
    label33->show();

    // Créer un objet 'human' pour déplacer le personnage
    human *hum = new human(rightPanel);

    // Position de départ (position initiale du cuisinier)
    QPoint startPos(50, 300);

    // Position de destination (par exemple, vers une autre partie du panel)
    QPoint endPos(350, 200);  // Exemple de destination

    // Durée du mouvement (en millisecondes)
    int duration = 8000;

    // Déplacer le cuisinier avec l'animation et l'effet de marche
    hum->moveLoop(label33, startPos, endPos, duration);
}
