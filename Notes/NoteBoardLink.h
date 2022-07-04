#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
//#include "UI-Components/Board.h"
#include <QPushButton>

class NoteBoardLink: public Note {
public:
    explicit NoteBoardLink(QWidget *parent = nullptr);
    NoteBoardLink(int board, QWidget *parent);
    ~NoteBoardLink();

    void saveData(std::ofstream *file) override;
    void readData(std::ifstream *file) override;
    std::string toText() override;
    noteType getType() override;

    QPushButton* thing;
    int boardID;
};

#endif // NOTEIMAGE_H
