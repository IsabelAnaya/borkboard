#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UI-Components/Board.h"
#include "UI-Components/Wall.h"
#include <QMainWindow>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QLabel>
#include <QSettings>
#include <QScrollArea>
#include <QMenuBar>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <string>
#include "UI-Components/Cork.h"
#include "UI-Components/Sidebar.h"
#include "Tools/DBManager.h"
#include "Tools/DataHandler.h"
#include "Tools/ThemeManager.h"

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
    void addBoardLinkNote(bool positioned);

private slots:
    void newWall();
    void loadRecentWall();
    void loadWallByPath(const QString &filepath);
    void loadWall();
    void saveWall();
    void renameBoard();
    void deleteBoard();
    void updateCurrentFile(const QString &file);
    void updateRecent();
    void changeTheme();
    void renameWall();
    void addTextNote();
    void addImageNote();
    Board* addBoard();

private:
    void updateCork();
    void connectButtons();
    void connectButtonsRecurse(SidebarItem* elem);

    QMenuBar *menu;
    QMenu *fileMenu;
    QMenu *boardMenu;
    QMenu *toolMenu;
    QColorDialog *colorDia;
    QInputDialog *nameDia;
    QInputDialog *selectDia;
    QFileDialog *fileDia;
    QMessageBox *questionDia;
    QMessageBox *confirmBoardDelete;
    QMessageBox *confirmDelete;
    QLabel *wallName;
    QLabel *boardName;
    Sidebar *sidebar;
    QGridLayout *mainbox;
    QWidget *window;
    DBManager *db;
    DataHandler *dh;
    ThemeManager *tm;
    QAction *recentFileAction[5];

};
#endif // MAINWINDOW_H
