#include "Table.h"
#include <QLabel>
#include <QPixmap>

Table::Table(const QString &imagePath, int x, int y, QWidget *parent)
    : QObject(parent)  // On s'assure que le parent est bien RestaurantFrame
{
    tableLabel = new QLabel(parent);  // parent doit être ui->RestaurantFrame ici
    tableLabel->setPixmap(QPixmap(imagePath));
    tableLabel->setGeometry(x, y, 100, 100); // Positionner la table dans RestaurantFrame
    tableLabel->setScaledContents(true);    // Ajuster l'image à la taille du QLabel
    tableLabel->show();  // Afficher la table dans RestaurantFrame
}

QLabel* Table::getLabel() const
{
    return tableLabel;
}
