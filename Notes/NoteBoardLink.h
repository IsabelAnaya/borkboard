#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
//#include "UI-Components/Board.h"
#include <QPushButton>

class NoteBoardLink: public Note {
public:
    explicit NoteBoardLink(QWidget *parent = nullptr);
    //NoteBoardLink(Board* b, QWidget *parent);
    ~NoteBoardLink();

    void saveData(std::ofstream *file) override;
    void readData(std::ifstream *file) override;
    std::string toText() override;
    noteType getType() override;

    QPushButton* thing;
    //Board* board;
};

#endif // NOTEIMAGE_H
