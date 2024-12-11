#ifndef CHEFDEPARTIE_H
#define CHEFDEPARTIE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class chefdepartie : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit chefdepartie(QWidget *parent = nullptr);

    // Méthode pour afficher l'image du serveur dans le panneau donné
    void afficherchefpartie(QWidget *parent);
    QLabel* getLabel() const { return label36; }  // Getter pour le QLabel du client
    int getX() const { return xPos; }             // Getter pour la position X
    int getY() const { return yPos; }             // Getter pour la position Y

private:
    QLabel *label36;  // Label pour afficher l'image du serveur
    int xPos;
    int yPos;
    QTimer *moveTimer;
};

#endif // CHEFDEPARTIE_H
