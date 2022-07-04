#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    colorDia = new QColorDialog();
    nameDia = new QInputDialog();
    nameDia->setLabelText("Enter new name of wall:");

    fileDia = new QFileDialog();

    this->resize(900, 500);

    currWall = new Wall();
    currBoard = currWall->root;

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

    /******* NOTES ********/
    //add text note
    QAction *addTextNoteAction = new QAction(tr("&New Text Note"), this);
    connect(addTextNoteAction, &QAction::triggered, this, &MainWindow::addTextNote);
    toolMenu->addAction(addTextNoteAction);

    //add image note
    QAction *addImageNoteAction = new QAction(tr("&New Image Note"), this);
    connect(addImageNoteAction, &QAction::triggered, this, &MainWindow::addImageNote);
    toolMenu->addAction(addImageNoteAction);

    //add board link note
    QAction *addBoardLinkNoteAction = new QAction(tr("New Board Note"), this);
    connect(addBoardLinkNoteAction, &QAction::triggered, this, &MainWindow::addBoardLinkNote);
    toolMenu->addAction(addBoardLinkNoteAction);

    //make child board
    QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
    connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
    toolMenu->addAction(addChildBoardAction);




    window = new QWidget();
    window->setLayout(currWall->mainbox);
    this->setCentralWidget(window);

    db = new DBManager();
    db->addWall("hi");

    dh = new DataHandler(db);
}

void MainWindow::newWall() {
    currWall = new Wall();
    currBoard = currWall->root;
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
        currBoard = currWall->root;
        updateBoard();
        file.close();
        std::cout << "benchmark FINAL: close file (mainwindow)" << std::endl;
        std::cout << currWall->root->boardName << std::endl;
    }
}

void MainWindow::saveWall() {
    dh->saveBoard(currBoard, 0, NULL);
}

void MainWindow::tempedit() {
    if (colorDia->exec() == true) {
        this->currBoard->setColor("background-color:" + colorDia->currentColor().name(QColor::HexRgb).toStdString());
        std::cout << this->currBoard->bgColor << std::endl;
    }

    nameDia->setLabelText("Enter new name of wall:");
    if (nameDia->exec() == true) {
        currWall->wallName = nameDia->textValue().toStdString();
    }

    nameDia->setLabelText("Enter new name of current board:");
    if (nameDia->exec() == true) {
        this->currBoard->setName(nameDia->textValue().toStdString());
    }

    updateBoard();
}

void MainWindow::addTextNote() {
    currBoard->cork->addTextNote();
}

void MainWindow::addImageNote() {
    currBoard->cork->addImageNote();
}

void MainWindow::addBoardLinkNote() {
    //ask for new/existing
    currBoard->cork->addBoardLinkNote();
}

void MainWindow::addBoard() {
    nameDia->setLabelText("Enter name of new board:");
    nameDia->setTextValue("New Board");
    if (nameDia->exec() == true) {

        currWall->wallName = nameDia->textValue().toStdString();
        Board* child = currBoard->makeChild(nameDia->textValue().toStdString());

        //currBoard->cork->addBoardLinkNote(child);
        updateBoard();
        //pass current board and name of new board to wall
    }
}



MainWindow::~MainWindow() {

}

void MainWindow::updateBoard() {
    currWall->update();
    this->setStyleSheet(QString::fromStdString(currWall->currentBoard->bgColor));
    window->setLayout(currWall->mainbox);
}

