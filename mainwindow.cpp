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

    //load wall
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
//    QAction *addImageNoteAction = new QAction(tr("&New Image Note"), this);
//    connect(addImageNoteAction, &QAction::triggered, this, &MainWindow::addImageNote);
//    toolMenu->addAction(addImageNoteAction);

    //add board link note
    QAction *addBoardLinkNoteAction = new QAction(tr("New Board Note"), this);
    connect(addBoardLinkNoteAction, &QAction::triggered, this, &MainWindow::addBoardLinkNote);
    toolMenu->addAction(addBoardLinkNoteAction);

    //make child board
//    QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
//    connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
//    toolMenu->addAction(addChildBoardAction);

    wallName = new QLabel(currWall->wallName);
    sidebar = new Sidebar(currWall->updateTree(currWall->root));
    mainbox = new QGridLayout;

    mainbox->addWidget(currWall->root->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    mainbox->addWidget(sidebar, 1, 4, 9, 1);

    window = new QWidget();
    window->setLayout(mainbox);
    this->setCentralWidget(window);

    db = new DBManager();
    dh = new DataHandler(db);
}

void MainWindow::newWall() {
    delete currWall;
    currBoard = NULL;
    currWall = new Wall();
    currBoard = currWall->root;
    updateBoard();
}

void MainWindow::loadWall() {
    QString filePath = fileDia->getOpenFileName(this, tr("Open Wall"), "", tr("*.bork"));

    if (filePath != "") {
        delete currWall;
        currBoard = NULL;

        db->openWall(filePath); //opening the file
        currWall = dh->rebuildWall(); //getting the wall ready
        currBoard = currWall->root;

        wallName->setText(currWall->wallName); //update the wall name
        sidebar->replace(currWall->updateTree(currWall->root)); //update the sidebar
        mainbox->addWidget(currWall->root->cork,0, 0, 10, 3); //re add the cork

        updateBoard();
    }
}

void MainWindow::saveWall() {
    if (db->openWall(currWall->wallName + ".bork")) {
        qDebug() << "overwriting " << currWall->wallName;
    } else {
        db->addWall(currWall->wallName);
    }
    dh->saveBoard(currBoard, 0, NULL);
}

void MainWindow::changeBoard(int board) {
    qDebug() << "changeBoard signal";
    if (board != currWall->currentBoard->ID) {
        currWall->changeBoard(board);
        currBoard = currWall->currentBoard;
        updateBoard();
    } else {
        qDebug() << "same board, not switching";
    }
}

void MainWindow::tempedit() {
//    if (colorDia->exec() == true) {
//        this->currBoard->setColor("background-color:" + colorDia->currentColor().name(QColor::HexRgb));
//    }

    nameDia->setLabelText("Enter new name of wall:");
    if (nameDia->exec() == true) {
        currWall->wallName = nameDia->textValue();

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

void MainWindow::addBoardLinkNote() {
    //ask for new/existing
    Board* board = addBoard();

    if (board) {
        connect(currBoard->cork->addBoardLinkNote(board->ID, board->boardName)->button, &BoardSwitchButton::boardSwitch, this, &MainWindow::changeBoard);
    }
}

Board* MainWindow::addBoard() {
    nameDia->setLabelText("Enter name of new board:");
    nameDia->setTextValue("New Board");
    if (nameDia->exec() == true) {
        Board* child = currWall->addBoard(currBoard, nameDia->textValue());

        updateBoard();
        std::vector<BoardSwitchButton*>* newButtons = currWall->updateTree(currWall->root);
        //pass current board and name of new board to wall
        return child;
    }
    return NULL;
}


void MainWindow::updateBoard() {
    //this->setStyleSheet(currWall->currentBoard->bgColor);
    //window->setLayout(currWall->mainbox);

    qDebug() << "updating";
}

MainWindow::~MainWindow() {

}
