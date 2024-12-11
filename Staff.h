#ifndef STAFF_H
#define STAFF_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Staff : public QObject {
    Q_OBJECT

public:
    Staff(const QString &imagePath, int id, QObject *parent = nullptr);
    ~Staff();

    void setPosition(int x, int y, double scale);
    void orderDish(const QString &dish);
    QGraphicsPixmapItem* getGraphicsItem() const;
    int getId() const;
    void showOrderPopup(const QString &message, QGraphicsScene *scene);

private:
    QGraphicsPixmapItem *graphicsItem;
    int id;
    QGraphicsTextItem *orderPopup;
};

#endif // STAFF_H
