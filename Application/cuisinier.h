
#ifndef CUISINIER_H
#define CUISINIER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class cuisinier : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit cuisinier(QWidget *parent = nullptr);

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






#endif //CUISINIER_H
