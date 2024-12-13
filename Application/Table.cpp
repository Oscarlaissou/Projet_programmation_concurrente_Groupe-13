#include "Table.h"
#include <QPixmap>

Table::Table(const QString &imagePath, int x, int y, int capacity, QObject *parent)
    : QObject(parent), capacity(capacity), occupied(false) {
    QPixmap pixmap(imagePath);
    graphicsItem = new QGraphicsPixmapItem(pixmap);
    graphicsItem->setPos(x, y);
}

QGraphicsPixmapItem* Table::getGraphicsItem() const {
    return graphicsItem;
}

int Table::getCapacity() const {
    return capacity;
}

bool Table::isOccupied() const {
    return occupied;
}

void Table::setOccupied(bool occupied) {
    this->occupied = occupied;
}
