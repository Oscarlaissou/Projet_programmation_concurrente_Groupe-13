#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>

namespace Ui {
class ViewWindow;
}

class ViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewWindow(QWidget *parent = nullptr);
    ~ViewWindow();

private:
    Ui::ViewWindow *ui;
    QSqlDatabase db;  // Objet pour la connexion à la base de données

    bool connectToDatabase();  // Méthode pour se connecter à la base de données
    void loadProduits();  // Méthode pour charger les produits dans TableProduit
    void loadCommandes();  // Méthode pour charger les commandes dans commande
    void loadMateriels(); //Méthode pour charger le matériel
    void checkStockAndUpdateProgressBar();


};

#endif // VIEWWINDOW_H
