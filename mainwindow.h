/*
 * mainwindow.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QScrollArea>
#include <QStackedWidget>
#include <QSpacerItem>
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QTimeEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showDashboard();
    void showPlayers();
    void showTeams();
    void showMatches();
    void showFields();
    void showMatchDetails(const QString &team1, const QString &team2);
    void openAddMatchDialog();
    void addNewMatch(const QString &team1, const QString &team2, const QString &time, const QString &terrain); // Correct declaration

private:
    QWidget *createSidebar();
    QWidget *createMatchCard(const QString &team1, const QString &team2, const QString &time, const QString &stadium);
    QWidget *createMatchArea();
    QWidget *createPlaceholderPage(const QString &text);

    QStackedWidget *stackedWidget;
    QVBoxLayout *matchListLayoutPtr; // Pointer to the layout containing match cards
};

#endif // MAINWINDOW_H
