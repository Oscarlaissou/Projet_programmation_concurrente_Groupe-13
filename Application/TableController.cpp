#include "TableController.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>



TableController::TableController(QObject *parent)
    : QObject(parent), scene(nullptr) {}

void TableController::setScene(QGraphicsScene *scene) {
    this->scene = scene;
}

void TableController::setupTables() {
    if (!scene) {
        qWarning() << "Erreur : la scène n'a pas été définie.";
        return;
    }

    // Dimensions et espacements
    int startX = 60;
    int startY = 200;
    int spaceX = 100;
    int spaceY = 140;
    int squareOffsetX = 500;
    QSize tableSize(90, 90);
    int currentTableIndex = 0;

    // Types de tables et quantités
    QList<QPair<QString, QPair<int, int>>> tableData = {
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table2.png", {10, 2}},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table4(3).png", {10, 4}},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table6.png", {5, 6}},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table8.png", {5, 8}},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table10.png", {2, 10}}
    };

    // Fonction utilitaire pour récupérer le prochain type de table
    auto getNextTableType = [&]() -> QPair<QString, int> {
        while (currentTableIndex < tableData.size()) {
            int &remainingTables = tableData[currentTableIndex].second.first;
            if (remainingTables > 0) {
                remainingTables--;
                return {tableData[currentTableIndex].first, tableData[currentTableIndex].second.second};
            }
            currentTableIndex++;
        }
        return {"", 0};
    };

    // Placement des tables
    for (int square = 0; square < 2; ++square) {
        int currentX = startX + square * squareOffsetX;
        int currentY = startY;

        // Deux rangées de six tables
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                auto tableType = getNextTableType();
                if (!tableType.first.isEmpty()) {
                    addTable(tableType.first, currentX + col * spaceX, currentY, tableSize.width(), tableSize.height(), tableType.second);
                }
            }
            currentY += spaceY;
        }
    }

    // Ajuste la scène pour inclure toutes les tables
    scene->setSceneRect(scene->itemsBoundingRect());
    qDebug() << "Tables placées et scène ajustée.";
}

void TableController::addTable(const QString &imagePath, int x, int y, int width, int height, int capacity) {
    if (!scene) return;

    // Créer une instance de la classe Table
    Table *table = new Table(imagePath, x, y, capacity);

    // Redimensionner l'image pour s'adapter à la taille spécifiée
    table->getGraphicsItem()->setScale(static_cast<qreal>(width) / table->getGraphicsItem()->pixmap().width());

    // Ajouter l'élément graphique à la scène
    scene->addItem(table->getGraphicsItem());
    tables.append(table); // Ajouter à la liste des tables

    qDebug() << "Table ajoutée (" << imagePath << ") à la position (" << x << "," << y << ") avec une capacité de" << capacity;

}

QList<Table*> TableController::getTables() const {
    return tables;
}

Table* TableController::getTableAt(int index) const {
    if (index >= 0 && index < tables.size()) {
        return tables.at(index);
    }
    return nullptr;
}


