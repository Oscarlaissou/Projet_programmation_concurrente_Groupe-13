// #ifndef CHEFDEPATISSERIE_H
// #define CHEFDEPATISSERIE_H

// #include <QString>
// #include <QQueue>
// #include <QDebug>

// class ChefDePatisserie {
// public:
//     ChefDePatisserie(const QString &name);

//     void addDessertToPrepare(const QString &dessert);
//     void prepareDessertsBeforeOpening();
//     QString getName() const { return name; }
//     QString getNextDessert() const; // Pour gérer les desserts

// private:
//     QString name;
//     QQueue<QString> dessertsToPrepare; // File des desserts à préparer
// };
#ifndef CHEFDEPATISSERIE_H
#define CHEFDEPATISSERIE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include "human.h"

class chefdepatisserie : public QWidget {
    Q_OBJECT

public:
    explicit chefdepatisserie(QWidget *parent = nullptr);
    void afficherpatissier(QWidget *parent);

    QLabel* getLabel() const { return label34; }
    int getX() const { return xPos; }
    int getY() const { return yPos; }

private:
    QLabel *label34;
    int xPos;
    int yPos;
    QTimer *moveTimer;
};

#endif // CHEFDEPATISSERIE_H
