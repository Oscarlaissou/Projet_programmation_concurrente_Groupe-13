#include "Client.h"
#include "Table.h"

#include <QGraphicsScene>
#include <QBrush>

Client::Client(int id, int groupSize, int x, int y, QObject *parent)
    : QObject(parent), id(id), groupSize(groupSize) {
    // Création du cercle graphique
    graphicsItem = new QGraphicsEllipseItem(0, 0, 30, 30);
    graphicsItem->setBrush(QBrush(Qt::blue)); // Couleur bleue pour les clients
    graphicsItem->setPos(x, y);

    // Création du texte pour afficher la taille du groupe
    textItem = new QGraphicsTextItem(QString::number(groupSize), graphicsItem);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(5, 2); // Position ajustée à l'intérieur du cercle
}

int Client::getId() const {
    return id;
}

int Client::getGroupSize() const {
    return groupSize;
}

QGraphicsEllipseItem* Client::getGraphicsItem() const {
    return graphicsItem;
}

QGraphicsTextItem* Client::getTextItem() const {
    return textItem;
}

void Client::moveTo(int x, int y) {
    graphicsItem->setPos(x, y);
}

void Client::assignTable(Table* table) {
    assignedTable = table;
}

Table* Client::getAssignedTable() const {
    return assignedTable;
}



