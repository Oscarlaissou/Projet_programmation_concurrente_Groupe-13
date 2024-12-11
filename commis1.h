#ifndef COMMIS1_H
#define COMMIS1_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class commis1 : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit commis1(QWidget *parent = nullptr);

    // Méthode pour afficher l'image du serveur dans le panneau donné
    void affichercommis1(QWidget *parent);
    QLabel* getLabel() const { return label37; }  // Getter pour le QLabel du client
    int getX() const { return xPos; }             // Getter pour la position X
    int getY() const { return yPos; }             // Getter pour la position Y

private:
    QLabel *label37;  // Label pour afficher l'image du serveur
    int xPos;
    int yPos;
    QTimer *moveTimer;
};
#endif // COMMIS1_H
