#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
#include "Wall.h"
#include <QMainWindow>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "NoteBoard.h"


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

private slots:
    void newWall();
    void loadWall();
    void saveWall();
    void tempedit();

    void addNote();

private:
    void updateBoard();

    QMenuBar *menu;
    QMenu *fileMenu;
    QMenu *tools;
    QColorDialog *colorPicker;
    QInputDialog *namer;
    QFileDialog *fileDia;
    QLabel *name;
    QGridLayout *mainbox;


};
#endif // MAINWINDOW_H
