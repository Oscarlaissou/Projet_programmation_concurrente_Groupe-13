#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

#include "StaffController.h"
#include "TableController.h"
#include "KitchenController.h"

#include "TableController.cpp"
#include "chefdepatisserie.h"
#include "chefdecuisine.h"
#include "ClientController.h"
#include "RoomMasterController.h"
#include "Client.h"
#include "OrderController.h"
#include "RoomMasterController.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulationTimer(new QTimer(this))
    , timer(new QTimer(this)) // Initialisation du timer pour le chronomètre
    , elapsedSeconds(0)       // Initialisation du compteur de secondes
    , viewWindow(new ViewWindow(this))
    , tableController(new TableController())
    , kitchenController(new KitchenController()) // Initialisation
    , clientController(new ClientController())
    , roomMasterController(new RoomMasterController()) // Initialisation de RoomMasterController
{
    ui->setupUi(this);

    // Scène pour la salle principale
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->RestaurantGraphicsView->setScene(scene);

    // Scène pour la cuisine
    QGraphicsScene *kitchenScene = new QGraphicsScene(this);
    ui->CuisineGraphicsView->setScene(kitchenScene);

    // Configurer les contrôleurs avec les scènes
    tableController->setScene(scene);       // Tables dans la salle principale
    kitchenController->setScene(kitchenScene);  // Cuisine dans la vue de la cuisine
    clientController->setScene(scene);

    // Lier tableController à clientController
    clientController->setTableController(tableController);

    // Ajouter le RoomMaster à la scène
    roomMasterController->setScene(scene);
    roomMasterController->addRoomMaster(70, 60); // Positionner le RoomMaster à (70, 60)

    // Connexion à la base de données
    connectToDatabase();
    orderController = new OrderController(db, this);
    // Configuration
    setupTables();
    setupKitchen();

    // // Connecter le bouton "Start" à la simulation
    // connect(ui->Start, &QPushButton::clicked, this, &MainWindow::start_simulation);


    // Configurer l'affichage du QTimeEdit
    ui->timeEditer->setDisplayFormat("mm:ss");

    // Connectez les boutons du chronomètre aux slots
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);

    // Connectez le bouton Dashboard au slot
    connect(ui->dashboardButton, &QPushButton::clicked, this, &MainWindow::onDashboardButtonClicked);

    // Connectez le timer à la mise à jour de l'affichage
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeDisplay);

}


MainWindow::~MainWindow()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
    delete simulationTimer;
    delete tableController;
    delete clientController;
    delete roomMasterController;
    delete orderController;
    delete timer;
    delete viewWindow;
}

// Mise à jour de l'affichage du temps
void MainWindow::updateTimeDisplay()
{
    elapsedSeconds++;
    QTime time(0, 0, 0); // Temps de départ (00:00:00)
    time = time.addSecs(elapsedSeconds); // Ajoute le temps écoulé
    ui->timeEditer->setTime(time); // Met à jour le QTimeEdit
}

// Slot pour le bouton Démarrer
void MainWindow::onStartButtonClicked()
{
    qDebug() << "Bouton Démarrer cliqué.";

    // Démarrer la simulation si ce n'est pas déjà en cours
    if (!simulationStarted) {
        start_simulation();  // Lancer la simulation pour la première fois
    }

    // Démarrer le chronomètre si ce n'est pas déjà fait
    if (!timer->isActive()) {
        timer->start(1000);  // Démarre le chronomètre
    }

    // Lancer la simulation si ce n'est pas déjà en cours
    if (!simulationTimer->isActive()) {
        simulationTimer->start(1000);  // Mettre à jour chaque seconde
    }
}

// Slot pour le bouton Pause
void MainWindow::onPauseButtonClicked()
{
    qDebug() << "Bouton Pause cliqué.";
    timer->stop(); // Arrête temporairement le timer
    simulationTimer->stop();
    qDebug() << "Simulation et chronomètre en pause.";

}

// Slot pour le bouton Stopper
void MainWindow::onStopButtonClicked()
{
    qDebug() << "Bouton Stopper cliqué.";
    timer->stop();             // Arrête le timer
    elapsedSeconds = 0;        // Réinitialise le temps écoulé
    simulationStarted = false; // Réinitialiser l'état de la simulation

    QTime time(0, 0, 0);       // Réinitialise l'heure à 00:00:00
    ui->timeEditer->setTime(time); // Met à jour l'affichage dans QTimeEdit

    // Supprimer les clients de la scène
    if (clientController) {
        clientController->removeAllClients();
        qDebug() << "Tous les clients ont été supprimés.";
    }

}

void MainWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE","uniqueConnectionName");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database.db");

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
        {":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/comptoir1.png", QPoint(20, 180)}
    };

    // Ajout des éléments à la cuisine
    for (const auto &element : kitchenElements) {
        kitchenController->addKitchenElement(element.first, element.second.x(), element.second.y());
    }

    qDebug() << "Éléments de la cuisine configurés avec des positions fixes.";
}


// Configuration des tables
void MainWindow::setupTables()
{
    if (!tableController) {
        qWarning() << "Erreur : TableController n'est pas initialisé.";
        return;
    }

    // Organiser les tables avec la logique principale
    tableController->setupTables();

    // Ajouter des tables spécifiques manuellement
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/comptoir.png", 70, 60, 120, 120,0);

    qDebug() << "Tables configurées avec des ajouts spécifiques.";
}

void MainWindow::onDashboardButtonClicked()
{
    if (viewWindow) {
        viewWindow->show(); // Afficher la fenêtre du tableau de bord
    } else {
        qDebug() << "Erreur : ViewWindow n'a pas été initialisée.";
    }
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
void MainWindow::startcommis1(QWidget *rightPanel) {
    commis1 *chef = new commis1(this);  // Créer un cuisinier
    chef->affichercommis1(rightPanel);    // Démarrer l'animation du cuisinier

}
void MainWindow::startcommis2(QWidget *rightPanel) {
    commis2 *chef = new commis2(this);  // Créer un cuisinier
    chef->affichercommis2(rightPanel);    // Démarrer l'animation du cuisinier

}



void MainWindow::start_simulation()
{
    // Vérifier si la simulation est déjà en cours
    if (isSimulationRunning) {
        qDebug() << "Simulation déjà en cours. Veuillez mettre en pause avant de relancer.";
        return;
    }

    isSimulationRunning = true; // Marquer la simulation comme active

    // Ajouter des clients uniquement si la simulation n'a pas déjà démarré
    if (!simulationStarted) {
        // Démarrer l'animation des cuisiniers
        startChefAnimation(ui->CuisineGraphicsView);
        startChefpatisserie(ui->CuisineGraphicsView);
        startplongeur(ui->CuisineGraphicsView);
        startchefpartie(ui->CuisineGraphicsView);
        startcommis1(ui->CuisineGraphicsView);
        startcommis2(ui->CuisineGraphicsView);

        // Ajouter un client
        Client *newClient = clientController->addClient(1, 500, 100);

        // Utiliser un QTimer pour introduire un délai avant l'affichage du QMessageBox
        QTimer::singleShot(1000, this, [this, newClient]() {
            QMessageBox::information(this, "Maitre d'hôtel", roomMasterController->getRoomMaster().askGroupSize());

            // Utiliser un autre QTimer pour introduire un délai entre les actions suivantes
            QTimer::singleShot(1500, this, [this, newClient]() {
                clientController->assignTableToClient(newClient);
                clientController->moveClientToAssignedTable(1);

                // Création et utilisation de OrderController
                OrderController orderController(db);
                QList<QString> menuItems = orderController.getMenuItems();
                for (const QString &item : menuItems) {
                    qDebug() << "Menu Item: " << item;
                }

                // Passer une commande pour le client
                orderController.placeOrderForClient(newClient->getId());

                qDebug() << "Clients ajoutés, table assignée, et commande passée.";
            });
        });

        simulationStarted = true; // Marquer la simulation comme commencée
    }

    // Démarrer les timers si ce n'est pas déjà fait
    if (!timer->isActive()) {
        timer->start(1000); // Mise à jour chaque seconde
    }

    if (!simulationTimer->isActive()) {
        simulationTimer->start(100); // Mise à jour toutes les 100 ms
    }

    qDebug() << "Simulation démarrée.";
}
