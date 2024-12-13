#ifndef COMMIS2_H
#define COMMIS2_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class commis2 : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicite, reçoit le panneau parent
    explicit commis2(QWidget *parent = nullptr);

    // Méthode pour afficher l'image du serveur dans le panneau donné
    void affichercommis2(QWidget *parent);
    QLabel* getLabel() const { return label38; }  // Getter pour le QLabel du client
    int getX() const { return xPos; }             // Getter pour la position X
    int getY() const { return yPos; }             // Getter pour la position Y

private:
    QLabel *label38;  // Label pour afficher l'image du serveur
    int xPos;
    int yPos;
    QTimer *moveTimer;
};
#endif // COMMIS2_H
