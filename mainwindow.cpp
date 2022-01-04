#include "mainwindow.h"
#include <fstream>
#include <iostream>

const char* delim = "%$";

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    colorPicker = new QColorDialog();
    namer = new QInputDialog();
    fileDia = new QFileDialog();

    this->resize(900, 500);

    currWall = new Wall();
    currBoard = currWall->root.board;
    currBoard->boardName = "New Board";
    currBoard->bgColor = "ffffff";
    name = new QLabel;
    name->setText(tr("New Board"));

    this->setWindowTitle("Bork Board");

    //file bar
    menu = new QMenuBar;
    fileMenu = menuBar()->addMenu(tr("&File"));
    tools = menuBar()->addMenu(tr("&Tools"));

    //new wall
    QAction *newWallAction = new QAction(tr("&New Wall"), this);
    connect(newWallAction, &QAction::triggered, this, &MainWindow::newWall);
    fileMenu->addAction(newWallAction);

    //new wall
    QAction *loadWallAction = new QAction(tr("&Load Wall"), this);
    connect(loadWallAction, &QAction::triggered, this, &MainWindow::loadWall);
    fileMenu->addAction(loadWallAction);

    //save wall
    QAction *saveWallAction = new QAction(tr("&Save"), this);
    connect(saveWallAction, &QAction::triggered, this, &MainWindow::saveWall);
    fileMenu->addAction(saveWallAction);

    //temp edit
    QAction *tempeditAction = new QAction(tr("&TEMP EDIT"), this);
    connect(tempeditAction, &QAction::triggered, this, &MainWindow::tempedit);
    fileMenu->addAction(tempeditAction);

    //add note
    QAction *addNoteAction = new QAction(tr("&New Note"), this);
    connect(addNoteAction, &QAction::triggered, this, &MainWindow::addNote);
    tools->addAction(addNoteAction);

    //make child board
    //QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
    //connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
    //tools->addAction(addChildBoardAction);

    mainbox = new QGridLayout;
    mainbox->addWidget(currBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(name, 0, 4, 1, 1);
    mainbox->addLayout(currWall->buildTreeVis(), 1, 4, 9, 1);

    QWidget *window = new QWidget();
    window->setLayout(mainbox);
    this->setCentralWidget(window);


}

void MainWindow::newWall() {
    currWall = new Wall();
    currBoard = currWall->root.board;
    updateBoard();
}

void MainWindow::loadWall() {
    std::string filePath = fileDia->getOpenFileName(this, tr("Open Wall"), "", tr("*.wal")).toStdString();

    if (filePath != "") {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        file.read(currBoard->boardName, 26);
        file.read(currBoard->bgColor, 26);

        char* notes = new char[5];
        file.read(notes, 5);
        //start reading boards and notes

        std::cout << notes << std::endl;

        updateBoard();
        file.close();
    }
}

void MainWindow::saveWall() {
    std::ofstream file((std::string)currBoard->boardName + ".wal", std::ios::out | std::ios::binary);
    file.write(currBoard->boardName, 26);
    file.write(delim, sizeof(delim));
    file.write(currBoard->bgColor, 26);
    file.write(delim, sizeof(delim));

    int notesize = currBoard->cork->notes.size();
    file.write(reinterpret_cast<const char*>(&notesize), sizeof(reinterpret_cast<const char*>(&notesize)) + 1);
    //https://stackoverflow.com/questions/9244563/writing-integer-to-binary-file-using-c

    for (int i = 0; i < notesize; i++) {
        //file.write(const_cast<char*>(currBoard->cork->notes[i]->title->toPlainText().toStdString()), 255);
    }

    file.close();
}

void MainWindow::tempedit() {

    if (colorPicker->exec() == true) {
        this->currBoard->setColor("background-color:" + colorPicker->currentColor().name(QColor::HexRgb));
        std::cout << this->currBoard->bgColor << std::endl;
    }
    if (namer->exec() == true) {
        this->currBoard->setName(namer->textValue());
    }

    updateBoard();

}

void MainWindow::addNote() {
    currBoard->cork->addNote();
}

MainWindow::~MainWindow() {

}

void MainWindow::updateBoard() {
    this->setStyleSheet(QString(currBoard->bgColor));
    this->name->setText(QString(currBoard->boardName));
}

