#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    colorDia = new QColorDialog();
    nameDia = new QInputDialog();
    questionDia = new QMessageBox();
    nameDia->setLabelText("Enter new name of wall:");
    questionDia->setText("Use Pre-Existing Board?");
    questionDia->addButton("Yes", QMessageBox::YesRole);
    questionDia->addButton("No", QMessageBox::NoRole);

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

    //recent walls
    QMenu *recentWallSubMenu = fileMenu->addMenu(tr("&Recent Walls"));
    for (int i = 0; i < 5; i++) {
        recentFileAction[i] = new QAction(this);
        recentFileAction[i]->setVisible(true);
        recentFileAction[i]->setData("");
        connect(recentFileAction[i], &QAction::triggered, this, &MainWindow::loadRecentWall);
        recentWallSubMenu->addAction(recentFileAction[i]);
    }
    updateRecent();

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

    toolMenu->addSeparator();

    //make child board
    QAction *addChildBoardAction = new QAction(tr("&New Child Board"), this);
    connect(addChildBoardAction, &QAction::triggered, this, &MainWindow::addBoard);
    toolMenu->addAction(addChildBoardAction);

    wallName = new QLabel("Wall: " + currWall->wallName);
    boardName = new QLabel("Board: " + currBoard->boardName);
    sidebar = new Sidebar(currWall->updateTree(currWall->root));
    mainbox = new QGridLayout;

    mainbox->addWidget(currWall->root->cork,0, 0, 10, 3);
    mainbox->addWidget(wallName, 0, 4, 1, 1);
    mainbox->addWidget(boardName, 1, 4, 1, 1);
    mainbox->addWidget(sidebar, 2, 4, 8, 1);

    window = new QWidget();
    window->setLayout(mainbox);
    this->setCentralWidget(window);

    connectButtons();

    db = new DBManager();
    dh = new DataHandler(db);
}

void MainWindow::newWall() {
    delete currWall;
    currBoard = NULL;
    currWall = new Wall();
    currBoard = currWall->root;

    wallName->setText("Wall: " + currWall->wallName); //update the wall name
    boardName->setText("Board: " + currBoard->boardName);

    sidebar->replace(currWall->updateTree(currWall->root)); //update the sidebar
    connectButtons(); //reconnect the sidebar
    mainbox->addWidget(currWall->root->cork,0, 0, 10, 3); //re add the cork
}

void MainWindow::loadWall() {
    QString filePath = fileDia->getOpenFileName(this, tr("Open Wall"), "", tr("*.bork"));
    loadWallByPath(filePath);
}

void MainWindow::loadRecentWall() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        loadWallByPath(action->data().toString());
    }
}

void MainWindow::loadWallByPath(const QString &filePath) {
    if (filePath != "") {
        delete currWall;
        currBoard = NULL;

        db->openWall(filePath); //opening the file
        currWall = dh->rebuildWall(); //getting the wall ready
        currBoard = currWall->root;

        wallName->setText("Wall: " + currWall->wallName); //update the wall name
        boardName->setText("Board: " + currBoard->boardName);
        sidebar->replace(currWall->updateTree(currWall->root)); //update the sidebar
        connectButtons(); //reconnect the sidebar
        mainbox->addWidget(currWall->root->cork,0, 0, 10, 3); //re add the cork

        //find any board links
        std::vector<Note*> boardlinks = currWall->findAllNotesOfType(noteBoard);
        for (unsigned int i = 0; i < boardlinks.size(); i++) {
            connect(static_cast<NoteBoardLink*>(boardlinks[i])->button, &BoardSwitchButton::boardSwitch, this, &MainWindow::changeBoard);
        }

        updateCurrentFile(filePath);
    }
}

void MainWindow::saveWall() {
    if (db->openWall(currWall->wallName + ".bork")) {
        qDebug() << "overwriting " << currWall->wallName;
    } else {
        db->addWall(currWall->wallName);
    }
    dh->saveWall(currWall);
    updateCurrentFile(currWall->wallName + ".bork");
}

void MainWindow::changeBoard(int board) {
    qDebug() << "changeBoard signal";
    if (board != currWall->currentBoard->ID) {
        currWall->changeBoard(board);
        currBoard = currWall->currentBoard;
        boardName->setText("Board: " + currBoard->boardName);
        updateCork();
    } else {
        qDebug() << "same board, not switching";
    }
}

void MainWindow::updateCurrentFile(const QString &file) {
    qDebug() << "updateCurrentFile, " << file;
    QSettings settings("beldog", "Bork Board");
    QStringList files = settings.value("recentfiles").toStringList();
    files.removeAll(file);
    files.prepend(file);
    while (files.size() > 5) {
        files.removeLast();
    }

    qDebug() << files;
    settings.setValue("recentfiles", files);
    settings.sync();
    qDebug() << settings.value("recentfiles").toStringList();
    updateRecent();
}

void MainWindow::updateRecent() {
    qDebug() << "updateRecent";
    QSettings settings("beldog", "Bork Board");
    QStringList files = settings.value("recentfiles").toStringList();
    int recentFileCount = qMin(files.size(), 5);
    qDebug() << files;
    for (int i = 0; i < recentFileCount; i++) {
        QString fileName = files[i];

        recentFileAction[i]->setText(QFileInfo(fileName).fileName());
        recentFileAction[i]->setData(files[i]);
        recentFileAction[i]->setVisible(true);
    }

    for (int j = recentFileCount; j < 5; j++) {
        recentFileAction[j]->setVisible(false);
    }
    //https://surfer.nmr.mgh.harvard.edu/ftp/dist/freesurfer/tutorial_versions/freesurfer/lib/qt/qt_doc/html/mainwindows-recentfiles-mainwindow-cpp.html
}

void MainWindow::tempedit() {
//    if (colorDia->exec() == true) {
//        this->currBoard->setColor("background-color:" + colorDia->currentColor().name(QColor::HexRgb));
//    }

    nameDia->setLabelText("Enter new name of wall:");
    if (nameDia->exec() == true) {
        currWall->wallName = nameDia->textValue();
        wallName->setText(nameDia->textValue());

    }

    nameDia->setLabelText("Enter new name of current board:");
    if (nameDia->exec() == true) {
        this->currBoard->setName(nameDia->textValue());
        boardName->setText("Board: " + currBoard->boardName);
        sidebar->replace(currWall->updateTree(currWall->root));
        connectButtons();
    }
}

void MainWindow::addTextNote() {
    currBoard->cork->addTextNote();
}

void MainWindow::addImageNote() {
    currBoard->cork->addImageNote();
}

void MainWindow::addBoardLinkNote() {
    int result = questionDia->exec(); // 0 for yes, 1 for no

    if (result == 1) {
        Board* board = addBoard();
        if (board) {
            connect(currBoard->cork->addBoardLinkNote(board->ID, board->boardName)->button, &BoardSwitchButton::boardSwitch, this, &MainWindow::changeBoard); //doesn't catch preexisting
        }
    } else { // old board
        std::pair<Board**, bool*> boardInfo = currWall->getAllBoards();
        QStringList items;

        for (int i = 0; i < MAX_BOARDS; i++) {
            if (boardInfo.second[i]) {
                items += boardInfo.first[i]->boardName;
            }
        }

        nameDia->setLabelText("Select board:");
        nameDia->setComboBoxItems(items);
        if (nameDia->exec()) {
            qDebug() << nameDia->textValue();
            Board* board = currWall->getBoard(items.indexOf(nameDia->textValue()));
            if (board) {
                connect(currBoard->cork->addBoardLinkNote(board->ID, board->boardName)->button, &BoardSwitchButton::boardSwitch, this, &MainWindow::changeBoard); //doesn't catch preexisting
            }
        }
    }
}

Board* MainWindow::addBoard() {
    nameDia->setLabelText("Enter name of new board:");
    nameDia->setTextValue("New Board");
    if (nameDia->exec() == true) {
        Board* child = currWall->addBoard(currBoard, nameDia->textValue());

        std::vector<BoardSwitchButton*>* newButtons = currWall->updateTree(currWall->root);
        sidebar->replace(newButtons); //inefficient, fix this

        connectButtons();
        return child;
    }
    return NULL;
}

void MainWindow::connectButtons() {
    int size = sidebar->buttons->size();
    for (int i = 0; i < size; i++) {
        connect(sidebar->buttons->at(i), &BoardSwitchButton::boardSwitch, this, &MainWindow::changeBoard, Qt::UniqueConnection);
    }
}

void MainWindow::updateCork() {
    //this->setStyleSheet(currWall->currentBoard->bgColor);
    //window->setLayout(currWall->mainbox);
    Cork* oldCork = static_cast<Cork*> (mainbox->itemAtPosition(0, 0)->widget());
    for (unsigned int i = 0; i < oldCork->notes.size(); i++) {
        oldCork->notes[i]->hide();
    }
    oldCork->hide();
    mainbox->removeItem(mainbox->itemAtPosition(0, 0)); //remove old cork

    mainbox->addWidget(currWall->currentBoard->cork,0, 0, 10, 3); //replace with new
    Cork* currCork = currWall->currentBoard->cork;
    currCork->show();
    for (unsigned int i = 0; i < currCork->notes.size(); i++) {
        currCork->notes[i]->show();
//        if (currCork->notes[i]->getType() == noteBoard) {

//        }
    }

    qDebug() << "updating";
}



MainWindow::~MainWindow() {

}
