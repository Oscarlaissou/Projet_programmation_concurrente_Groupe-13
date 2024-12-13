#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

class Table; // Déclaration anticipée de la classe Table

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(int id, int groupSize, int x, int y, QObject *parent = nullptr);

    int getId() const;
    int getGroupSize() const;
     Table* getAssignedTable() const;
    QGraphicsEllipseItem* getGraphicsItem() const;
    QGraphicsTextItem* getTextItem() const;
    void moveTo(int x, int y);

    // Nouvelle méthode pour assigner une table au client
    void assignTable(Table* table);
    void moveToAssignedTable();

private:
    int id;
    int groupSize;
    QGraphicsEllipseItem *graphicsItem;
    QGraphicsTextItem *textItem;
    Table* assignedTable; // Pointeur vers la table assignée


};

#endif // CLIENT_H
