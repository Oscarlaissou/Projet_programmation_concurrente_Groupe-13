#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

#include "StaffController.h"
#include "TableController.h"
#include "KitchenController.h"
#include "StaffController.cpp"
#include "TableController.cpp"
#include "chefdepatisserie.h"
#include "chefdecuisine.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulationTimer(new QTimer(this))
    , tableController(new TableController())
    , staffController(new StaffController())
    , kitchenController(new KitchenController()) // Initialisation
{
    ui->setupUi(this);

    // Scène pour la salle principale
    QGraphicsScene *Scene = new QGraphicsScene(this);
    ui->RestaurantGraphicsView->setScene(Scene);

    // Scène pour la cuisine
    QGraphicsScene *kitchenScene = new QGraphicsScene(this);
    ui->CuisineGraphicsView->setScene(kitchenScene);

    // Configurer les contrôleurs avec les scènes
    tableController->setScene(Scene);       // Tables dans la salle principale
    staffController->setScene(Scene);       // Personnel dans la salle principale
    kitchenController->setScene(kitchenScene);  // Cuisine dans la vue de la cuisine

    // Connexion à la base de données
    connectToDatabase();

    // Configuration
    setupTables();
    setupKitchen();

    // Connecter le bouton "Start" à la simulation
    connect(ui->Start, &QPushButton::clicked, this, &MainWindow::start_simulation);
}

MainWindow::~MainWindow()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
}

void MainWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("app BD.db");

    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données :" << db.lastError().text();
    } else {
        qDebug() << "Connexion à la base de données réussie !";
    }
}



void MainWindow::setupKitchen() {
    // Tableau contenant les chemins des images et leurs positions fixes (x, y)
    QVector<QPair<QString, QPoint>> kitchenElements = {
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/refri.png", QPoint(500, 90)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png", QPoint(200, -60)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png", QPoint(110, -60)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png", QPoint(20, -60)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuisin.png", QPoint(300, -120)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/lave.png", QPoint(250, 150)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/gardev.png", QPoint(340, 130)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuiseur.png", QPoint(540, -40)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/reserve.png", QPoint(440, 400)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chambre_froide.png", QPoint(520, 380)},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/comptoir.png", QPoint(20, 180)}
    };

    // Ajout des éléments à la cuisine
    for (const auto &element : kitchenElements) {
        kitchenController->addKitchenElement(element.first, element.second.x(), element.second.y());
    }

    qDebug() << "Éléments de la cuisine configurés avec des positions fixes.";
}



void MainWindow::setupTables()
{
    // Ajouter des tables statiques via le TableController
   tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 50, 50);
   tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 200, 100);
   tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 350, 200);
   tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 500, 300);

   qDebug() << "Tables configurées et affichées sur l'interface.";
}

void MainWindow::startChefAnimation(QWidget *rightPanel) {
    chefdecuisine *chef = new chefdecuisine(this);  // Créer un cuisinier
    chef->affichercuisinier(rightPanel);    // Démarrer l'animation du cuisinier
}
void MainWindow::startChefpatisserie(QWidget *rightPanel) {
    chefdepatisserie *chef = new chefdepatisserie(this);  // Créer un cuisinier
    chef->afficherpatissier(rightPanel);    // Démarrer l'animation du cuisinier
}

void MainWindow::startplongeur(QWidget *rightPanel) {
    plongeur *chef = new plongeur(this);  // Créer un cuisinier
    chef->afficherplongeur(rightPanel);    // Démarrer l'animation du cuisinier
}
void MainWindow::startchefpartie(QWidget *rightPanel) {
    chefdepartie *chef = new chefdepartie(this);  // Créer un cuisinier
    chef->afficherchefpartie(rightPanel);    // Démarrer l'animation du cuisinier

}

    // Vous pouvez aussi ici gérer d'autres actions si nécessaire pour le cuisinier

void MainWindow::start_simulation()
{
    // Ajouter 5 personnages avec des positions initiales aléatoires
    for (int i = 0; i < 5; ++i) {
        int x = QRandomGenerator::global()->bounded(0, ui->RestaurantGraphicsView->width() - 50);
        int y = QRandomGenerator::global()->bounded(0, ui->RestaurantGraphicsView->height() - 50);
        staffController->addStaff(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Personnage.png", i, x, y, 0.5); // Échelle à 50%
    }


    // Démarrer l'animation du cuisinier
    startChefAnimation(ui->CuisineGraphicsView);  // Appeler la méthode spécifique
    startChefpatisserie(ui->CuisineGraphicsView);
    startplongeur(ui->CuisineGraphicsView);
    startchefpartie(ui->CuisineGraphicsView);
    // Connecter le timer pour animer les personnages
    connect(simulationTimer, &QTimer::timeout, this, [=]() {
        for (int i = 0; i < 5; ++i) {
            int dx = QRandomGenerator::global()->bounded(-10, 10); // Déplacement horizontal aléatoire
            int dy = QRandomGenerator::global()->bounded(-10, 10); // Déplacement vertical aléatoire
            staffController->moveStaff(i, dx, dy);
        }
    });

    simulationTimer->start(100); // Mise à jour toutes les 100 ms
    qDebug() << "Simulation démarrée.";
}

// void MainWindow::start_simulation() {
//     // Création des chefs
//     ChefDePatisserie *chefPatisserie = new ChefDePatisserie("Chef Pâtisserie");
//     ChefDeCuisine *chefCuisine = new ChefDeCuisine("Chef Cuisine");

//     // Préparer les desserts avant l'ouverture
//     chefPatisserie->addDessertToPrepare("Tarte aux pommes");
//     chefPatisserie->addDessertToPrepare("Mousse au chocolat");
//     chefPatisserie->prepareDessertsBeforeOpening();

//     // Simuler la réception des commandes
//     chefCuisine->receiveOrder("Table 1", "Filet de boeuf");
//     chefCuisine->receiveOrder("Table 1", "Soupe du jour");
//     chefCuisine->receiveOrder("Table 2", "Filet de boeuf");

//     // Processus des commandes
//     chefCuisine->processOrders();
//     chefCuisine->assignTasksToChefs();
// }

// void MainWindow::start_simulation() {
//     // Création des chefs
//     ChefDePatisserie *chefPatisserie = new ChefDePatisserie("Chef Pâtisserie");
//     ChefDeCuisine *chefCuisine = new ChefDeCuisine("Chef Cuisine");

//     // Ajouter graphiquement les chefs à la scène
//     QGraphicsPixmapItem *chefPatisserieItem = kitchenController->addCharacter(
//         ":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_patisserie.png", 50, 50);
//     QGraphicsPixmapItem *chefCuisineItem = kitchenController->addCharacter(
//         ":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_cuisine.png", 50, 50);

//     // Définir les positions pour représenter leurs déplacements
//     QVector<QPoint> patisseriePositions = {
//                                            QPoint(100, 100), QPoint(300, 100), QPoint(300, 200), QPoint(100, 200)};
//     QVector<QPoint> cuisinePositions = {
//                                         QPoint(200, 100), QPoint(400, 100), QPoint(400, 200), QPoint(200, 200)};

//     int patisserieIndex = 0; // Position actuelle du chef pâtissier
//     int cuisineIndex = 0;    // Position actuelle du chef de cuisine

//     // Ajouter des desserts au chef pâtissier
//     chefPatisserie->addDessertToPrepare("Tarte aux pommes");
//     chefPatisserie->addDessertToPrepare("Mousse au chocolat");

//     // Préparer les desserts
//     chefPatisserie->prepareDessertsBeforeOpening();

//     // Simuler la réception des commandes pour le chef de cuisine
//     chefCuisine->receiveOrder("Table 1", "Filet de boeuf");
//     chefCuisine->receiveOrder("Table 1", "Soupe du jour");
//     chefCuisine->receiveOrder("Table 2", "Filet de boeuf");

//     // Animer les chefs avec un timer
//     QTimer *animationTimer = new QTimer(this);

//     connect(animationTimer, &QTimer::timeout, this, [=, &patisserieIndex, &cuisineIndex]() mutable {
//         // Déplacer le chef pâtissier
//         chefPatisserieItem->setPos(patisseriePositions[patisserieIndex]);
//         qDebug() << chefPatisserie->getName() << "travaille sur" << chefPatisserie->getNextDessert();
//         patisserieIndex = (patisserieIndex + 1) % patisseriePositions.size();

//         // Déplacer le chef de cuisine
//         chefCuisineItem->setPos(cuisinePositions[cuisineIndex]);
//         chefCuisine->processOrders(); // Traite les commandes en mouvement
//         cuisineIndex = (cuisineIndex + 1) % cuisinePositions.size();

//         qDebug() << chefCuisine->getName() << "travaille sur une commande.";
//     });

//     animationTimer->start(1000); // Met à jour toutes les secondes

//     qDebug() << "Simulation démarrée avec des chefs instanciés et animés.";
// }

// void MainWindow::start_simulation() {
//     // Création des chefs
//     ChefDePatisserie *chefPatisserie = new ChefDePatisserie("Chef Pâtisserie");
//     ChefDeCuisine *chefCuisine = new ChefDeCuisine("Chef Cuisine");

//     // Ajouter graphiquement les chefs à la scène
//     QGraphicsPixmapItem *chefPatisserieItem = kitchenController->addCharacter(
//         ":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_patisserie.png", 50, 50);
//     QGraphicsPixmapItem *chefCuisineItem = kitchenController->addCharacter(
//         ":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chef_cuisine.png", 50, 50);


//     // Définir les positions pour représenter leurs déplacements
//     QVector<QPoint> patisseriePositions = {
//                                            QPoint(100, 100), QPoint(300, 100), QPoint(300, 200), QPoint(100, 200)};
//     QVector<QPoint> cuisinePositions = {
//                                         QPoint(20, 180), QPoint(400, 100), QPoint(400, 200), QPoint(200, 200)};

//     int patisserieIndex = 0; // Position actuelle du chef pâtissier
//     int cuisineIndex = 0;    // Position actuelle du chef de cuisine

//     // Ajouter des desserts au chef pâtissier
//     chefPatisserie->addDessertToPrepare("Tarte aux pommes");
//     chefPatisserie->addDessertToPrepare("Mousse au chocolat");

//     // Préparer les desserts
//     chefPatisserie->prepareDessertsBeforeOpening();

//     // Simuler la réception des commandes pour le chef de cuisine
//     chefCuisine->receiveOrder("Table 1", "Filet de boeuf");
//     chefCuisine->receiveOrder("Table 1", "Soupe du jour");
//     chefCuisine->receiveOrder("Table 2", "Filet de boeuf");

//     // Animer les chefs avec un timer
//     QTimer *animationTimer = new QTimer(this);

//     connect(animationTimer, &QTimer::timeout, this, [=, &patisserieIndex, &cuisineIndex]() mutable {
//         // Déplacer le chef pâtissier
//         qDebug() << "Patisserie Index:" << patisserieIndex;
//         qDebug() << "Chef Pâtisserie Position:" << patisseriePositions[patisserieIndex];
//         chefPatisserieItem->setVisible(false); // Rendre le chef invisible avant de le déplacer
//         QTimer::singleShot(500, [=]() {
//             chefPatisserieItem->setPos(patisseriePositions[patisserieIndex]);
//             chefPatisserieItem->setVisible(true); // Rendre le chef visible après déplacement
//         });
//         patisserieIndex = (patisserieIndex + 1) % patisseriePositions.size();

//         // Déplacer le chef de cuisine
//         qDebug() << "Cuisine Index:" << cuisineIndex;
//         qDebug() << "Chef Cuisine Position:" << cuisinePositions[cuisineIndex];
//         chefCuisineItem->setVisible(false); // Rendre le chef invisible avant de le déplacer
//         QTimer::singleShot(500, [=]() {
//             chefCuisineItem->setPos(cuisinePositions[cuisineIndex]);
//             chefCuisineItem->setVisible(true); // Rendre le chef visible après déplacement
//         });
//         cuisineIndex = (cuisineIndex + 1) % cuisinePositions.size();

//         // Traiter les commandes
//         chefCuisine->processOrders();
//         qDebug() << chefCuisine->getName() << "travaille sur une commande.";
//         qDebug() << chefPatisserie->getName() << "travaille sur" << chefPatisserie->getNextDessert();
//     });

//     animationTimer->start(1000); // Met à jour toutes les secondes

//     qDebug() << "Simulation démarrée avec des chefs instanciés et animés.";
// }
