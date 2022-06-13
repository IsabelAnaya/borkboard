#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
//#include "UI-Components/Board.h"
#include <QPushButton>

class NoteBoardLink: public Note {
public:
    explicit NoteBoardLink(QWidget *parent = nullptr);
    NoteBoardLink(QString t, QWidget *parent);
    ~NoteBoardLink();

    void saveData(std::ofstream *file);
    void readData(std::ifstream *file);

    QPushButton* thing;
    //Board* board;
};

#endif // NOTEIMAGE_H
