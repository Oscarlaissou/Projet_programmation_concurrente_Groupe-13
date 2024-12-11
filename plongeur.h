#ifndef PLONGEUR_H
#define PLONGEUR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class plongeur : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit plongeur(QWidget *parent = nullptr);

    // Méthode pour afficher l'image du serveur dans le panneau donné
    void afficherplongeur(QWidget *parent);
    QLabel* getLabel() const { return label35; }  // Getter pour le QLabel du client
    int getX() const { return xPos; }             // Getter pour la position X
    int getY() const { return yPos; }             // Getter pour la position Y

private:
    QLabel *label35;  // Label pour afficher l'image du serveur
    int xPos;
    int yPos;
    QTimer *moveTimer;
};
#endif // PLONGEUR_H
