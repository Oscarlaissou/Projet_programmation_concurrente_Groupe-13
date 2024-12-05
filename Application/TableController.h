#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <QLabel>
#include <QList>

class TableController : public QObject
{
    Q_OBJECT

public:
    explicit TableController(QWidget *parent = nullptr);
    void addTable(const QString &imagePath, int x, int y); // Ajouter une table
    void removeTables(); // Optionnel : pour supprimer les tables existantes

private:
    QList<QLabel*> tables;  // Liste des QLabel (tables)
    QWidget *parentWidget;  // Widget parent (RestaurantFrame)
};

#endif // TABLECONTROLLER_H
