#include "Staff.h"
#include <QGraphicsTextItem>
#include <QFont>

Staff::Staff(const QString &imagePath, int id, QObject *parent)
    : QObject(parent), graphicsItem(new QGraphicsPixmapItem(QPixmap(imagePath))), id(id), orderPopup(nullptr)
{
    graphicsItem->setZValue(1);
}

Staff::~Staff()
{
    delete graphicsItem;
    if (orderPopup) {
        delete orderPopup;
    }
}

void Staff::setPosition(int x, int y, double scale)
{
    if (graphicsItem) {
        graphicsItem->setPos(x, y);
        graphicsItem->setScale(scale / 100.0);
    }
}

void Staff::orderDish(const QString &dish)
{
    Q_UNUSED(dish);
}

QGraphicsPixmapItem* Staff::getGraphicsItem() const
{
    return graphicsItem;
}

int Staff::getId() const
{
    return id;
}

void Staff::showOrderPopup(const QString &message, QGraphicsScene *scene)
{
    if (orderPopup) {
        scene->removeItem(orderPopup);
        delete orderPopup;
    }

    orderPopup = new QGraphicsTextItem(message);
    orderPopup->setFont(QFont("Arial", 12));
    orderPopup->setPos(graphicsItem->pos().x(), graphicsItem->pos().y() - 30);
    orderPopup->setZValue(2);
    scene->addItem(orderPopup);
}
