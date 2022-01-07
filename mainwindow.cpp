#include "mainwindow.h"
#include <fstream>
#include <iostream>
#include <string>

const char* delim = "%$";

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    colorDia = new QColorDialog();
    nameDia = new QInputDialog();
    nameDia->setLabelText("Enter new name of wall:");

    fileDia = new QFileDialog();

    this->resize(900, 500);

    currWall = new Wall();
    currBoard = currWall->root.board;
    wallName = new QLabel;
    wallName->setText(tr("New Wall"));

    this->setWindowTitle("Bork Board");

    //file bar
    menu = new QMenuBar;
    fileMenu = menuBar()->addMenu(tr("&File"));
    toolMenu = menuBar()->addMenu(tr("&Tools"));

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
    toolMenu->addAction(addNoteAction);

    //make child board
    //QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
    //connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
    //tools->addAction(addChildBoardAction);

    mainbox = new QGridLayout;
    mainbox->addWidget(currBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    mainbox->addLayout(currWall->buildTreeVis(), 1, 4, 9, 1);

    window = new QWidget();
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
        std::ifstream file(filePath, std::ios::in);

        delete currWall;
        currBoard = NULL;
        currWall = new Wall();

        std::string temp;
        std::getline(file, temp);
        currWall->wallName = temp;

        int boardsize;
        std::getline(file, temp); //num of boards
        boardsize = stoi(temp);

        //get boards
        for (int i = 0; i < boardsize; i++) {
            //set parent
            Board *newBoard = new Board();

            std::getline(file, temp);
            newBoard->setName(QString::fromStdString(temp));
            std::getline(file, temp);
            newBoard->setColor(QString::fromStdString(temp));

            int notesize;
            std::getline(file, temp); //num of notes for curr board
            notesize = stoi(temp);

            std::string title;
            std::string content;
            int xPos;
            int yPos;
            //get notes
            for (int j = 0; j < notesize; j++) {
                std::getline(file, title);
                std::getline(file, content);

                std::getline(file, temp);
                xPos = stoi(temp);
                std::getline(file, temp);
                yPos = stoi(temp);
                newBoard->cork->addNote(title, content, xPos, yPos);
            }
        }

        currBoard = currWall->root.board;
        updateBoard();
        file.close();
    }
}

void MainWindow::saveWall() {
    std::ofstream file((std::string)currWall->wallName + ".wal", std::ios::out | std::ios::trunc);
    file << currWall->wallName << std::endl;
    file << 1 << std::endl; //number of boards
    file << currBoard->boardName << std::endl;
    file << currBoard->bgColor << std::endl;

    int notesize = currBoard->cork->notes.size();
    file << notesize << std::endl;;

    Cork *currCork = currBoard->cork;
    for (int i = 0; i < notesize; i++) {
        std::cout << "benchmark 1" << std::endl;
        Note *currNote = currCork->notes[i];
        std::cout << "benchmark 2" << std::endl;
        file << currNote->title->toPlainText().toStdString() << std::endl; //BREAKS HERE?????
        std::cout << "benchmark 3" << std::endl;
        file << currNote->content->toPlainText().toStdString() << std::endl;
        std::cout << "benchmark 4" << std::endl;
        file << currNote->pos().x() << std::endl;
        std::cout << "benchmark 5" << std::endl;
        file << currNote->pos().y() << std::endl;
        std::cout << "benchmark 6" << std::endl;
    }

    file.close();
}

void MainWindow::tempedit() {
    if (colorDia->exec() == true) {
        this->currBoard->setColor("background-color:" + colorDia->currentColor().name(QColor::HexRgb));
        std::cout << this->currBoard->bgColor << std::endl;
    }

    if (nameDia->exec() == true) {
        currWall->wallName = nameDia->textValue().toStdString();
    }
    nameDia->setLabelText("Enter new name of current board:");

    if (nameDia->exec() == true) {
        this->currBoard->setName(nameDia->textValue());
    }
    nameDia->setLabelText("Enter new name of wall:"); //reset to the normal text

    updateBoard();
}

void MainWindow::addNote() {
    currBoard->cork->addNote();
}

MainWindow::~MainWindow() {

}

void MainWindow::updateBoard() {
    this->setStyleSheet(QString(currBoard->bgColor));
    this->wallName->setText(QString::fromStdString(currWall->wallName));

    delete mainbox;
    mainbox = new QGridLayout;
    mainbox->addWidget(currBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    mainbox->addLayout(currWall->buildTreeVis(), 1, 4, 9, 1);

    window->setLayout(mainbox);
}

