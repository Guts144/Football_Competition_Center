/*
 * mainwindow.cpp
 */

#include "mainwindow.h"

#include <QMessageBox>

// --- Add Match Dialog ---
class AddMatchDialog : public QDialog
{
public:
    AddMatchDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        setWindowTitle("Ajouter un nouveau match");
        setModal(true);

        team1Edit = new QLineEdit;
        team1Edit->setPlaceholderText("Nom de l'équipe 1");
        team2Edit = new QLineEdit;
        team2Edit->setPlaceholderText("Nom de l'équipe 2");
        timeEdit = new QTimeEdit;
        terrainEdit = new QLineEdit;
        terrainEdit->setPlaceholderText("Nom du terrain");

        QPushButton *addButton = new QPushButton("Ajouter");
        QPushButton *cancelButton = new QPushButton("Annuler");

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Équipe 1:"));
        layout->addWidget(team1Edit);
        layout->addWidget(new QLabel("Équipe 2:"));
        layout->addWidget(team2Edit);
        layout->addWidget(new QLabel("Heure du match:"));
        layout->addWidget(timeEdit);
        layout->addWidget(new QLabel("Terrain:"));
        layout->addWidget(terrainEdit);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);
        layout->addLayout(buttonLayout);

        connect(addButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getTeam1() const { return team1Edit->text(); }
    QString getTeam2() const { return team2Edit->text(); }
    QString getTime() const { return timeEdit->time().toString("hh:mm"); }
    QString getTerrain() const { return terrainEdit->text(); }

private:
    QLineEdit *team1Edit;
    QLineEdit *team2Edit;
    QTimeEdit *timeEdit;
    QLineEdit *terrainEdit;
};
// --- End Add Match Dialog ---

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), matchListLayoutPtr(nullptr)
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QWidget *sidebar = createSidebar();
    stackedWidget = new QStackedWidget;

    stackedWidget->addWidget(createPlaceholderPage("Dashboard"));     // index 0
    stackedWidget->addWidget(createPlaceholderPage("Players"));       // index 1
    stackedWidget->addWidget(createPlaceholderPage("Teams"));         // index 2
    stackedWidget->addWidget(createMatchArea());                     // index 3
    stackedWidget->addWidget(createPlaceholderPage("Fields"));        // index 4

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget, 1);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Smart Football Competition Center");
    resize(1200, 700);
}

QWidget* MainWindow::createSidebar()
{
    QWidget *sidebar = new QWidget;
    sidebar->setFixedWidth(250);
    sidebar->setStyleSheet("background-color: #00695c; color: white;");

    QVBoxLayout *layout = new QVBoxLayout(sidebar);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 40, 20, 20);

    QLabel *logo = new QLabel("⚽\nSmart Football\nCompititon Center");
    logo->setAlignment(Qt::AlignCenter);
    logo->setStyleSheet("font-weight: bold; font-size: 18px;");

    QPushButton *btnDashboard = new QPushButton("Tableau de bord");
    QPushButton *btnPlayers = new QPushButton("Joueurs");
    QPushButton *btnTeams = new QPushButton("Equipes");
    QPushButton *btnMatches = new QPushButton("Matches");
    QPushButton *btnFields = new QPushButton("Terrains");
    QPushButton *btnAdmin = new QPushButton("Admin");

    QList<QPushButton*> buttons = {btnDashboard, btnPlayers, btnTeams, btnMatches, btnFields, btnAdmin};
    for (QPushButton *btn : buttons) {
        btn->setStyleSheet("text-align: left; padding: 10px; font-size: 16px; background-color: transparent; color: white;");
        btn->setFlat(true);
        layout->addWidget(btn);
    }

    connect(btnDashboard, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(btnPlayers, &QPushButton::clicked, this, &MainWindow::showPlayers);
    connect(btnTeams, &QPushButton::clicked, this, &MainWindow::showTeams);
    connect(btnMatches, &QPushButton::clicked, this, &MainWindow::showMatches);
    connect(btnFields, &QPushButton::clicked, this, &MainWindow::showFields);

    layout->addStretch();
    layout->insertWidget(0, logo);

    return sidebar;
}

QWidget* MainWindow::createMatchCard(const QString &team1, const QString &team2, const QString &time, const QString &stadium)
{
    QFrame *card = new QFrame;
    card->setStyleSheet(R"(
        QFrame {
            border: 1px solid #ccc;
            border-radius: 16px;
            background-color: #ffffff;
        }
    )");
    QHBoxLayout *layout = new QHBoxLayout(card);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(30);

    // Team 1
    QLabel *team1Icon = new QLabel("⚽");
    team1Icon->setStyleSheet("font-size: 32px; color: #004d40;");
    QLabel *team1Label = new QLabel(team1);
    team1Label->setStyleSheet("font-size: 18px; font-weight: bold; color: #004d40;");
    QVBoxLayout *team1Layout = new QVBoxLayout;
    team1Layout->addWidget(team1Icon, 0, Qt::AlignCenter);
    team1Layout->addWidget(team1Label, 0, Qt::AlignCenter);

    // Match Info
    QLabel *matchTimeLabel = new QLabel("<b style='font-size: 22px;'>" + time + "</b>");
    QLabel *stadiumLabel = new QLabel(stadium);
    stadiumLabel->setStyleSheet("color: #777;");
    QVBoxLayout *infoLayout = new QVBoxLayout;
    infoLayout->addWidget(matchTimeLabel, 0, Qt::AlignCenter);
    infoLayout->addWidget(stadiumLabel, 0, Qt::AlignCenter);

    // Team 2
    QLabel *team2Icon = new QLabel("⚽");
    team2Icon->setStyleSheet("font-size: 32px; color: #00695c;");
    QLabel *team2Label = new QLabel(team2);
    team2Label->setStyleSheet("font-size: 18px; font-weight: bold; color: #00695c;");
    QVBoxLayout *team2Layout = new QVBoxLayout;
    team2Layout->addWidget(team2Icon, 0, Qt::AlignCenter);
    team2Layout->addWidget(team2Label, 0, Qt::AlignCenter);

    // Buttons
    QPushButton *detailsBtn = new QPushButton("Détails");
    QPushButton *deleteBtn = new QPushButton("Supprimer");

    detailsBtn->setStyleSheet("padding: 8px 16px; background-color: #004d40; color: white; font-weight: bold; border-radius: 8px;");
    deleteBtn->setStyleSheet("padding: 8px 16px; background-color: #c62828; color: white; font-weight: bold; border-radius: 8px;");

    connect(detailsBtn, &QPushButton::clicked, [=]() {
        showMatchDetails(team1, team2);
    });

    connect(deleteBtn, &QPushButton::clicked, [=]() {
        if (matchListLayoutPtr) {
            matchListLayoutPtr->removeWidget(card);
            card->deleteLater();  // Schedule deletion
        }
    });

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(detailsBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addStretch();

    // Add all to main layout
    layout->addLayout(buttonLayout);
    layout->addLayout(team1Layout);
    layout->addLayout(infoLayout);
    layout->addLayout(team2Layout);

    return card;
}


QWidget* MainWindow::createMatchArea()
{
    QWidget *mainArea = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(mainArea);

    QLabel *title = new QLabel("Matches");
    title->setStyleSheet("font-size: 28px; font-weight: bold;");
    QPushButton *addMatchBtn = new QPushButton("Ajouter un match");
    addMatchBtn->setStyleSheet("background-color: #00695c; color: white; padding: 10px 20px; border-radius: 10px; font-size: 16px;");
    addMatchBtn->setFixedWidth(200);
    connect(addMatchBtn, &QPushButton::clicked, this, &MainWindow::openAddMatchDialog);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(title);
    topLayout->addStretch();
    topLayout->addWidget(addMatchBtn);

    layout->addLayout(topLayout);
    layout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: #f0f0f0; border: none;");

    QWidget *scrollWidget = new QWidget;
    matchListLayoutPtr = new QVBoxLayout(scrollWidget); // Initialize the pointer

    matchListLayoutPtr->setSpacing(15);
    matchListLayoutPtr->addStretch(); // Leave space for future cards

    scrollWidget->setLayout(matchListLayoutPtr);
    scrollArea->setWidget(scrollWidget);

    layout->addWidget(scrollArea);
    return mainArea;
}


QWidget* MainWindow::createPlaceholderPage(const QString &text)
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(label);
    return page;
}

void MainWindow::showDashboard() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showPlayers() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showTeams() {
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showMatches() {
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::showFields() {
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::showMatchDetails(const QString &team1, const QString &team2)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Détails du Match");
    dialog->setModal(true);
    dialog->resize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *label1 = new QLabel("Equipe 1: " + team1);
    QLabel *label2 = new QLabel("Equipe 2: " + team2);
    layout->addWidget(label1);
    layout->addWidget(label2);

    QPushButton *closeButton = new QPushButton("Fermer");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->exec();
}

void MainWindow::openAddMatchDialog()
{
    AddMatchDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString team1 = dialog.getTeam1();
        QString team2 = dialog.getTeam2();
        QString time = dialog.getTime();
        QString terrain = dialog.getTerrain();

        addNewMatch(team1, team2, time, terrain); // Correct call to addNewMatch
    }
}

void MainWindow::addNewMatch(const QString &team1, const QString &team2, const QString &time, const QString &terrain)
{
    if (!team1.isEmpty() && !team2.isEmpty() && !time.isEmpty() && !terrain.isEmpty() && matchListLayoutPtr) {
        matchListLayoutPtr->insertWidget(matchListLayoutPtr->count() - 1, createMatchCard(team1, team2, time, terrain));
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs pour ajouter un match.");
    }
}
