#ifndef HUMAN_H
#define HUMAN_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class human : public QWidget {
    Q_OBJECT

public:
    explicit human(QWidget *parent = nullptr);
    void move(QLabel *personnageLabel, const QPoint &startPos, const QPoint &endPos, int duration);
    void moveLoop(QLabel *personnageLabel, const QPoint &startPos, const QPoint &endPos, int duration);

    void onAnimationFinished();

    void stopMovement();  // Nouvelle méthode pour arrêter le mouvement

private:
    bool moving = false;  // Variable pour savoir si un mouvement est en cours
    QSequentialAnimationGroup *currentGroup = nullptr;  // Garde une référence au groupe d'animation
};

#endif // HUMAN_H
