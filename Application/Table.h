#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Table : public QObject {
    Q_OBJECT

public:
    explicit Table(const QString &imagePath, int x, int y, int capacity, QObject *parent = nullptr);

    QGraphicsPixmapItem* getGraphicsItem() const;
    int getCapacity() const;
    bool isOccupied() const;
    void setOccupied(bool occupied);

private:
    QGraphicsPixmapItem *graphicsItem; // Élément graphique
    int capacity;                      // Capacité de la table
    bool occupied;                     // État de la table
};

#endif // TABLE_H
