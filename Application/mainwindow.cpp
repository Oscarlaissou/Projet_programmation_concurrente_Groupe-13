#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulationTimer(new QTimer(this))
    , tableController(new TableController(ui->RestaurantFrame))
{
    ui->setupUi(this);
    connectToDatabase();
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

void MainWindow::start_simulation()
{
    // Nettoyer les anciens personnages
    for (QLabel *label : staffLabels) {
        delete label;
    }
    staffLabels.clear();

    // Créer 5 personnages avec des positions initiales aléatoires
    for (int i = 0; i < 5; ++i) {
        QLabel *staffLabel = new QLabel(ui->RestaurantFrame);
        staffLabel->setGeometry(QRandomGenerator::global()->bounded(0, ui->RestaurantFrame->width() - 50),
                                QRandomGenerator::global()->bounded(0, ui->RestaurantFrame->height() - 50),
                                50, 50); // Taille et position initiale
        QString imagePath = ":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/Personnage.png";
        QPixmap pixmap(imagePath);

        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image depuis" << imagePath;
            delete staffLabel;
            continue;
        }

        staffLabel->setPixmap(pixmap);
        staffLabel->setScaledContents(true);
        staffLabel->show();
        staffLabels.append(staffLabel); // Ajouter le QLabel à la liste
    }

    // Connecter le timer pour animer les personnages
    connect(simulationTimer, &QTimer::timeout, this, [=]() {
        for (QLabel *staffLabel : staffLabels) {
            int dx = QRandomGenerator::global()->bounded(-10, 10); // Déplacement horizontal aléatoire
            int dy = QRandomGenerator::global()->bounded(-10, 10); // Déplacement vertical aléatoire

            // Calculer la nouvelle position
            int newX = staffLabel->x() + dx;
            int newY = staffLabel->y() + dy;

            // Vérifier les limites
            if (newX < 0) newX = 0;
            if (newY < 0) newY = 0;
            if (newX > ui->RestaurantFrame->width() - staffLabel->width()) {
                newX = ui->RestaurantFrame->width() - staffLabel->width();
            }
            if (newY > ui->RestaurantFrame->height() - staffLabel->height()) {
                newY = ui->RestaurantFrame->height() - staffLabel->height();
            }

            // Déplacer le personnage
            staffLabel->move(newX, newY);
        }
    });

    // Démarrer la simulation
    simulationTimer->start(100); // Met à jour toutes les 100 ms
}

void MainWindow::setupTables()
{
    // Ajouter des tables statiques
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 50, 50);
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 200, 100);
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 350, 200);
    tableController->addTable(":build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/images/table-ronde.png", 500, 300);

    qDebug() << "Tables configurées et affichées sur l'interface.";
}
