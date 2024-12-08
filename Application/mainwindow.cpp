#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

#include "StaffController.h"
#include "TableController.h"
#include "TableController.cpp"
#include "StaffController.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulationTimer(new QTimer(this))
    , timer(new QTimer(this)) // Initialisation du timer pour le chronomètre
    , elapsedSeconds(0)       // Initialisation du compteur de secondes
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

    // Configurer l'affichage du QTimeEdit
    ui->timeEditer->setDisplayFormat("mm:ss");

    // Connectez les boutons du chronomètre aux slots
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);

    // Connectez le timer à la mise à jour de l'affichage
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeDisplay);
}

MainWindow::~MainWindow()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
    delete tableController;
    delete staffController;
    delete timer; // Supprimez le timer pour éviter les fuites mémoire
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
    timer->start(1000); // Démarre le timer pour mises à jour toutes les 1000ms (1 seconde)
}

// Slot pour le bouton Pause
void MainWindow::onPauseButtonClicked()
{
    qDebug() << "Bouton Pause cliqué.";
    timer->stop(); // Arrête temporairement le timer
}

// Slot pour le bouton Stopper
void MainWindow::onStopButtonClicked()
{
    qDebug() << "Bouton Stopper cliqué.";
    timer->stop();             // Arrête le timer
    elapsedSeconds = 0;        // Réinitialise le temps écoulé

    QTime time(0, 0, 0);       // Réinitialise l'heure à 00:00:00
    ui->timeEditer->setTime(time); // Met à jour l'affichage dans QTimeEdit
}

// Connexion à la base de données
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
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/comptoir.png", 70, 60, 120, 120);

    qDebug() << "Tables configurées avec des ajouts spécifiques.";
}

// Simulation du mouvement des personnages
void MainWindow::start_simulation()
{
    connect(simulationTimer, &QTimer::timeout, this, [this]() {
        for (int i = 0; i < 5; ++i) {
            int dx = QRandomGenerator::global()->bounded(-10, 10); // Déplacement horizontal aléatoire
            int dy = QRandomGenerator::global()->bounded(-10, 10); // Déplacement vertical aléatoire
            staffController->moveStaff(i, dx, dy);
        }
    });

    simulationTimer->start(100); // Mise à jour toutes les 100ms
    qDebug() << "Simulation démarrée.";
}
