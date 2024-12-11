// #ifndef CHEFDECUISINE_H
// #define CHEFDECUISINE_H

// #include <QString>
// #include <QMap>
// #include <QVector>
// #include <QDebug>

// class ChefDeCuisine {
// public:
//     ChefDeCuisine(const QString &name);

//     void receiveOrder(const QString &table, const QString &dish);
//     void processOrders();
//     void assignTasksToChefs();

//     QString getName() const { return name; }
//     // Autres membres

// private:
//     QString name;
//     QMap<QString, QVector<QString>> orders; // Commandes par table
// };

// #endif // CHEFDECUISINE_H

#ifndef CHEFDECUISINE_H
#define CHEFDECUISINE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class chefdecuisine : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit chefdecuisine(QWidget *parent = nullptr);

    // Méthode pour afficher l'image du serveur dans le panneau donné
    void affichercuisinier(QWidget *parent);
    QLabel* getLabel() const { return label33; }  // Getter pour le QLabel du client
    int getX() const { return xPos; }             // Getter pour la position X
    int getY() const { return yPos; }             // Getter pour la position Y

private:
    QLabel *label33;  // Label pour afficher l'image du serveur
    int xPos;
    int yPos;
    QTimer *moveTimer;
};






#endif // CHEFDECUISINE_H

