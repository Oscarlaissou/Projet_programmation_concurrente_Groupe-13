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
    QList<QPair<QString, int>> tableData = {
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table2.png", 10},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table4(3).png", 10},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table6.png", 5},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table8.png", 5},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table10.png", 2}
    };

    // Fonction utilitaire pour récupérer le prochain type de table
    auto getNextTableType = [&]() -> QString {
        while (currentTableIndex < tableData.size()) {
            int &remainingTables = tableData[currentTableIndex].second;
            if (remainingTables > 0) {
                remainingTables--;
                return tableData[currentTableIndex].first;
            }
            currentTableIndex++;
        }
        return QString();
    };

    // Placement des tables
    for (int square = 0; square < 2; ++square) {
        int currentX = startX + square * squareOffsetX;
        int currentY = startY;

        // Deux rangées de six tables
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                QString tableType = getNextTableType();
                if (!tableType.isEmpty()) {
                    addTable(tableType, currentX + col * spaceX, currentY, tableSize.width(), tableSize.height());
                }
            }
            currentY += spaceY;
        }
    }

    // Ajuste la scène pour inclure toutes les tables
    scene->setSceneRect(scene->itemsBoundingRect());
    qDebug() << "Tables placées et scène ajustée.";
}

void TableController::addTable(const QString &imagePath, int x, int y, int width, int height) {
    if (!scene) return;

    QPixmap originalPixmap(imagePath);
    if (originalPixmap.isNull()) {
        qWarning() << "Erreur : Impossible de charger l'image" << imagePath;
        return;
    }

    QPixmap scaledPixmap = originalPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *tableItem = new QGraphicsPixmapItem(scaledPixmap);
    tableItem->setPos(x, y);
    scene->addItem(tableItem);
    tables.append(tableItem);

    qDebug() << "Table ajoutée (" << imagePath << ") à la position (" << x << "," << y << ")";
}
