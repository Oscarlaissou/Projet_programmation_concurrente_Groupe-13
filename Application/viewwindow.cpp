#include "viewwindow.h"
#include "ui_viewwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewWindow)
{
    ui->setupUi(this);

    // Connecter la base de données
    if (!connectToDatabase()) {
        qDebug() << "Erreur de connexion à la base de données!";
    }

    // Charger les données dans les QTableWidget
    loadProduits();
    loadCommandes();
    loadMateriels();
}

ViewWindow::~ViewWindow()
{
    delete ui;
    db.close();  // Fermer la base de données lorsque la fenêtre est fermée
}

// Connexion à la base de données SQLite
bool ViewWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la BD :" << db.lastError().text();
        return false;
    }

    return true;
}

// Charger les produits dans TableProduit

// Charger les commandes dans commande
void ViewWindow::loadCommandes()
{
    QSqlQuery query("SELECT Commande_ID, Date_Commande, Status, Heure, Client_ID FROM Commande");

    if (!query.exec()) {
        qDebug() << "Échec de la récupération des commandes:" << query.lastError().text();
        return;
    }

    // Configurer le QTableWidget
    ui->commande->setColumnCount(5);  // 5 colonnes : Commande_ID, Date_Commande, Status, Heure, Client_ID
    ui->commande->setHorizontalHeaderLabels({"Commande_ID", "Date_Commande", "Status", "Heure", "Client_ID"});

    // Remplir les données dans le QTableWidget
    int row = 0;
    while (query.next()) {
        ui->commande->insertRow(row);

        ui->commande->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));  // Commande_ID
        ui->commande->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));  // Date_Commande
        ui->commande->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));  // Status
        ui->commande->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));  // Heure
        ui->commande->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));  // Client_ID

        ++row;
    }
}
void ViewWindow::loadProduits()
{
    QSqlQuery query("SELECT Produit_ID, Nom, Type, Quantite_Stockée, Quantite_Disponible, Zone_Stockage, Date_Peremption FROM Produit");

    if (!query.exec()) {
        qDebug() << "Échec de la récupération des produits:" << query.lastError().text();
        return;
    }

    ui->Tableproduit->setColumnCount(7);
    ui->Tableproduit->setHorizontalHeaderLabels({"Produit_ID", "Nom", "Type", "Quantite_Stockée", "Quantite_Disponible", "Zone_Stockage", "Date_Peremption"});

    ui->Tableproduit->setRowCount(0);  // Réinitialiser le tableau avant de le remplir
    QString alertMessage;

    while (query.next()) {
        int row = ui->Tableproduit->rowCount();
        ui->Tableproduit->insertRow(row);

        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->Tableproduit->setItem(row, col, item);
        }

        // Récupérer les quantités
        int quantiteStockee = query.value(3).toInt();  // Quantité disponible est à l'index 3
        int quantiteDisponible = query.value(4).toInt();  // Quantité stockée est à l'index 4

        // Vérifier si la quantité disponible est inférieure à 80 % de la quantité stockée
        if (quantiteStockee > 0 && quantiteDisponible < (0.6 * quantiteStockee)) {
            QString nomProduit = query.value(1).toString();  // Nom du produit à l'index 1
            QString typeProduit = query.value(2).toString();  // Type du produit à l'index 2
            alertMessage.append(nomProduit + " du type " + typeProduit + " a un stock faible. Veuillez vérifier.\n");

        }
    }

    // Afficher les alertes dans un label
    if (!alertMessage.isEmpty()) {
        ui->label->setText(alertMessage);  // Assure-toi d'avoir un label nommé labelAlerte dans l'UI
    }
}


void ViewWindow::loadMateriels()
{
    // Récupérer toutes les colonnes de la table Materiels
    QSqlQuery query("SELECT Materiel_ID, Type, Nom FROM Materiels");

    if (!query.exec()) {
        qDebug() << "Échec de la récupération des matériaux:" << query.lastError().text();
        return;
    }

    qDebug() << "Requête exécutée avec succès!";


    // Configurer le QTableWidget avec les bonnes colonnes
    ui->TableMateriels->setColumnCount(3);  // 3 colonnes correspondant aux champs de la table Materiels
    ui->TableMateriels->setHorizontalHeaderLabels({"Materiel_ID", "Type", "Nom"});

    // Remplir les données dans le QTableWidget
    int row = 0;
    while (query.next()) {
        ui->TableMateriels->insertRow(row);

        ui->TableMateriels->setItem(row, 0, new QTableWidgetItem(query.value("Materiel_ID").toString()));  // Materiel_ID
        ui->TableMateriels->setItem(row, 1, new QTableWidgetItem(query.value("Type").toString()));         // Type
        ui->TableMateriels->setItem(row, 2, new QTableWidgetItem(query.value("Nom").toString()));          // Nom

        ++row;
    }

    qDebug() << row << " lignes de matériaux chargées dans le tableau.";
}
