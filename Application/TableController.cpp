#include "TableController.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

TableController::TableController(QWidget *parent)
    : QObject(parent), parentWidget(parent)
{
}

void TableController::addTable(const QString &imagePath, int x, int y)
{
    // Crée un QGraphicsPixmapItem pour représenter une table
    QGraphicsPixmapItem *tableItem = new QGraphicsPixmapItem(QPixmap(imagePath));

    if (tableItem->pixmap().isNull()) {
        qWarning() << "Erreur : Impossible de charger l'image" << imagePath;
        delete tableItem;
        return;
    }

    // Positionner la table dans la scène
    tableItem->setPos(x, y);
    parentWidget->scene()->addItem(tableItem);  // Ajouter l'item à la scène

    // Ajouter la table à la liste pour un suivi ultérieur (si nécessaire)
    tables.append(tableItem);
}

void TableController::removeTables()
{
    // Supprime toutes les tables (QGraphicsPixmapItem)
    for (QGraphicsPixmapItem *table : tables) {
        parentWidget->scene()->removeItem(table);  // Retirer de la scène
        delete table;  // Suppression de l'item
    }
    tables.clear();  // Réinitialiser la liste
}
