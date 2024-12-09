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


// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
//     , simulationTimer(new QTimer(this))
//     , tableController(new TableController())
//     , staffController(new StaffController())
// {
//     ui->setupUi(this);

//     // Initialiser la scène graphique
//     QGraphicsScene *scene = new QGraphicsScene(this);
//     ui->RestaurantGraphicsView->setScene(scene);

//     // Configurer les contrôleurs avec la scène
//     tableController->setScene(scene);
//     staffController->setScene(scene);

//     // Connexion à la base de données
//     connectToDatabase();

//     // Configuration des tables
//     setupTables();

//     // Connecter le bouton "Start" à la simulation
//     connect(ui->Start, &QPushButton::clicked, this, &MainWindow::start_simulation);
// }


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

// void MainWindow::setupKitchen() {
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/refrigerateur.png", 500, 50);
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chambre_froide.png", 50, 50);
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuiseur.png", 300, 100);
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/gardev.png", 300, 100);
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png", 300, 100);
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/lave_vaissele.png", 300, 100);

//     qDebug() << "Éléments de la cuisine configurés et affichés.";
// }


// void MainWindow::setupKitchen() {
//     int viewWidth = ui->CuisineGraphicsView->width();
//     int viewHeight = ui->CuisineGraphicsView->height();
//     int elementSize = 100; // Taille approximative après redimensionnement

//     // En haut à gauche
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/refrigerateur.png",
//                                          50, 50);

//     // En haut au centre
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chambre_froide.png",
//                                          viewWidth / 2 - elementSize / 2, 50);

//     // En haut à droite
//     //kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuiseur.png",
//                                         // viewWidth - elementSize - 50, 50);

//     // Au centre à gauche
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png",
//                                          10, viewHeight / 2 - elementSize / 2);
//     // En bas à gauche
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuiseur.png",
//                                          50, viewHeight - elementSize - 50);

//     // En bas au centre
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/gardev.png",
//                                          viewWidth / 2 - elementSize / 2, viewHeight - elementSize - 50);

//     // En bas à droite
//     kitchenController->addKitchenElement(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/lave_vaissele.png",
//                                          viewWidth - elementSize - 50, viewHeight - elementSize - 50);

//     qDebug() << "Éléments de la cuisine configurés avec une disposition spécifique.";
// }

void MainWindow::setupKitchen() {
    // Tableau contenant les chemins des images et leurs positions fixes (x, y)
    struct KitchenElement {
        QString imagePath;
        int x;
        int y;
    };


    QVector<KitchenElement> kitchenElements = {
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/refrigera.png", 50, 600},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Feux.png", 400, 50},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/chambre_froide.png", 50, 200},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/cuiseur.png", 550, 200},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/gardev.png", 350, 600},
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/lave_vaissele.png", 500, 500}
    };

    // Parcours et ajout des éléments
    for (const KitchenElement &element : kitchenElements) {
        kitchenController->addKitchenElement(element.imagePath, element.x, element.y);
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

void MainWindow::start_simulation()
{
    // Ajouter 5 personnages avec des positions initiales aléatoires
    for (int i = 0; i < 5; ++i) {
        int x = QRandomGenerator::global()->bounded(0, ui->RestaurantGraphicsView->width() - 50);
        int y = QRandomGenerator::global()->bounded(0, ui->RestaurantGraphicsView->height() - 50);
        staffController->addStaff(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Personnage.png", i, x, y, 0.5); // Échelle à 50%
    }

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
