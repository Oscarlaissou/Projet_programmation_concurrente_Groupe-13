#include "TableController.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

TableController::TableController(QObject *parent)
    : QObject(parent), scene(nullptr) {}

void TableController::setScene(QGraphicsScene *scene) {
    this->scene = scene;
}

void TableController::addTable(const QString &imagePath, int x, int y) {
    if (!scene) return;

    QGraphicsPixmapItem *tableItem = new QGraphicsPixmapItem(QPixmap(imagePath));
    if (tableItem->pixmap().isNull()) {
        qWarning() << "Erreur : Impossible de charger l'image" << imagePath;
        delete tableItem;
        return;
    }

    tableItem->setPos(x, y);
    scene->addItem(tableItem);
    tables.append(tableItem);
}

