#ifndef NOTEIMAGE_H
#define NOTEIMAGE_H

#include "Note.h"

class NoteImage: public Note {
public:
    explicit NoteImage(QWidget *parent = nullptr);
    NoteImage(QString t, QString c, QWidget *parent);
    ~NoteImage();

    void saveData(std::ofstream *file) override;
    void readData(std::ifstream *file) override;
    std::string toText() override;
    noteType getType() override;

    QTextEdit* title;
    QPixmap img;
    QLabel* content;
};

#endif // NOTEIMAGE_H
