#include "human.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <QSequentialAnimationGroup>
#include <QTimer>

human::human(QWidget *parent) : QWidget(parent), moving(false) {
    // Constructeur vide, peut être utilisé pour initialiser des variables si nécessaire
}

void human::moveLoop(QLabel *personnageLabel, const QPoint &startPos, const QPoint &endPos, int duration) {
    // Vérifiez si un mouvement est déjà en cours
    if (moving) {
        return;  // Si déjà en mouvement, ne rien faire
    }

    moving = true;  // L'animation commence

    // Définir la position initiale
    personnageLabel->setGeometry(startPos.x(), startPos.y(), 30, 60);

    // Animation pour aller au point final
    QPropertyAnimation *goToEnd = new QPropertyAnimation(personnageLabel, "pos");
    goToEnd->setDuration(duration);
    goToEnd->setStartValue(startPos);
    goToEnd->setEndValue(endPos);
    goToEnd->setEasingCurve(QEasingCurve::OutQuad);

    // Animation pour revenir au point initial
    QPropertyAnimation *returnToStart = new QPropertyAnimation(personnageLabel, "pos");
    returnToStart->setDuration(duration);
    returnToStart->setStartValue(endPos);
    returnToStart->setEndValue(startPos);
    returnToStart->setEasingCurve(QEasingCurve::OutQuad);

    // Créer un groupe d'animations séquentielles
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
    group->addAnimation(goToEnd);
    group->addAnimation(returnToStart);

    // Lancer l'animation
    group->start();

    // Sauvegarder une référence à l'animation et au groupe
    currentGroup = group;

    // Connecter l'animation à une fonction de fin pour réinitialiser 'moving'
    connect(group, &QSequentialAnimationGroup::finished, this, &human::onAnimationFinished);
}

void human::onAnimationFinished() {
    moving = false;  // L'animation est terminée, réinitialiser l'état 'moving'
}

void human::stopMovement() {
    if (currentGroup) {
        currentGroup->stop();  // Arrêter l'animation
        moving = false;  // Indiquer que le mouvement est arrêté
    }
}

