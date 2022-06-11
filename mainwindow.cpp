#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    colorDia = new QColorDialog();
    nameDia = new QInputDialog();
    nameDia->setLabelText("Enter new name of wall:");

    fileDia = new QFileDialog();

    this->resize(900, 500);

    currWall = new Wall();
    currBoard = currWall->root->board;
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

    //add text note
    QAction *addTextNoteAction = new QAction(tr("&New Text Note"), this);
    connect(addTextNoteAction, &QAction::triggered, this, &MainWindow::addTextNote);
    toolMenu->addAction(addTextNoteAction);

    //add image note
    QAction *addImageNoteAction = new QAction(tr("&New Image Note"), this);
    connect(addImageNoteAction, &QAction::triggered, this, &MainWindow::addImageNote);
    toolMenu->addAction(addImageNoteAction);

    //make child board
    QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
    connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
    toolMenu->addAction(addChildBoardAction);

    mainbox = new QGridLayout;
    mainbox->addWidget(currBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    treeVis = currWall->buildTreeVis();
    mainbox->addLayout(treeVis, 1, 4, 9, 1);

    window = new QWidget();
    window->setLayout(mainbox);
    this->setCentralWidget(window);
}

void MainWindow::newWall() {
    currWall = new Wall();
    currBoard = currWall->root->board;
    updateBoard();
}

void MainWindow::loadWall() {
    std::string filePath = fileDia->getOpenFileName(this, tr("Open Wall"), "", tr("*.wal")).toStdString();

    if (filePath != "") {
        std::ifstream file(filePath, std::ios::in);

        delete currWall;
        currBoard = NULL;
        currWall = new Wall();

        std::cout << "benchmark 1: call read (mainwindow)" << std::endl;
        currWall->readData(&file);

        std::cout << "benchmark FINAL - 1: set up (mainwindow)" << std::endl;
        currBoard = currWall->root->board;
        updateBoard();
        file.close();
        std::cout << "benchmark FINAL: close file (mainwindow)" << std::endl;
        std::cout << currWall->root->board->boardName << std::endl;
    }
}

void MainWindow::saveWall() {
    std::ofstream file((std::string)currWall->wallName + ".wal", std::ios::out | std::ios::trunc);

    currWall->saveData(&file);

    file.close();
}

void MainWindow::tempedit() {
    if (colorDia->exec() == true) {
        this->currBoard->setColor("background-color:" + colorDia->currentColor().name(QColor::HexRgb));
        std::cout << this->currBoard->bgColor << std::endl;
    }

    nameDia->setLabelText("Enter new name of wall:");
    if (nameDia->exec() == true) {
        currWall->wallName = nameDia->textValue().toStdString();
    }

    nameDia->setLabelText("Enter new name of current board:");
    if (nameDia->exec() == true) {
        this->currBoard->setName(nameDia->textValue());
    }

    updateBoard();
}

void MainWindow::addTextNote() {
    currBoard->cork->addTextNote();
}

void MainWindow::addImageNote() {
    currBoard->cork->addImageNote();
}

void MainWindow::addBoard() {
    nameDia->setLabelText("Enter name of new board:");
    nameDia->setTextValue("New Board");
    if (nameDia->exec() == true) {

        currWall->wallName = nameDia->textValue().toStdString();
        //pass current board and name of new board to wall
    }
}



MainWindow::~MainWindow() {

}

void MainWindow::updateBoard() {
    this->setStyleSheet(QString::fromStdString(currBoard->bgColor));
    this->wallName->setText(QString::fromStdString(currWall->wallName));

    delete treeVis;
    delete mainbox;

    mainbox = new QGridLayout;
    treeVis = currWall->buildTreeVis();
    mainbox->addWidget(currBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    mainbox->addLayout(treeVis, 1, 4, 9, 1);

    window->setLayout(mainbox);
}

