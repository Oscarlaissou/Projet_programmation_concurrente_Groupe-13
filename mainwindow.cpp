#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

#include "StaffController.h"
#include "TableController.h"
#include "StaffController.cpp"
#include "TableController.cpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulationTimer(new QTimer(this))
    , tableController(new TableController())
    , staffController(new StaffController())
{
    ui->setupUi(this);

    // Initialiser la scène graphique
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->RestaurantGraphicsView->setScene(scene);

    // Configurer les contrôleurs avec la scène
    tableController->setScene(scene);
    staffController->setScene(scene);

    // Connexion à la base de données
    connectToDatabase();

    // Configuration des tables
    setupTables();

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

void MainWindow::setupTables()
{
    // Ajouter des tables statiques via le TableController
    //tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 50, 50);
   // tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 200, 100);
   // tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 350, 200);
   // tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 500, 300);

   // qDebug() << "Tables configurées et affichées sur l'interface.";
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
