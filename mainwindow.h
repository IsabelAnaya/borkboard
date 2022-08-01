#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UI-Components/Board.h"
#include "UI-Components/Wall.h"
#include <QMainWindow>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <fstream>
#include <iostream>
#include <string>
#include "UI-Components/Cork.h"
#include "UI-Components/Sidebar.h"
#include "Tools/DBManager.h"
#include "Tools/DataHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//run the app, display current board
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Wall *currWall;
    Board *currBoard;

public slots:
    void changeBoard(int board);

private slots:
    void newWall();
    void loadWall();
    void saveWall();
    void tempedit();
    void addTextNote();
    void addImageNote();
    void addBoardLinkNote();
    Board* addBoard();

private:
    void updateCork();
    void connectButtons();

    QMenuBar *menu;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QColorDialog *colorDia;
    QInputDialog *nameDia;
    QFileDialog *fileDia;
    QLabel *wallName;
    QLabel *boardName;
    Sidebar *sidebar;
    QGridLayout *mainbox;
    QWidget *window;
    DBManager *db;
    DataHandler *dh;

};
#endif // MAINWINDOW_H
