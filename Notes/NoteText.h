#ifndef NOTETEXT_H
#define NOTETEXT_H

#include "Note.h"

class NoteText: public Note {
public:
    explicit NoteText(QWidget *parent = nullptr);
    NoteText(QString t, QString c, QWidget *parent);
    ~NoteText();

    void saveData(std::ofstream *file) override;
    void readData(std::ifstream *file) override;
    std::string toText() override;
    noteType getType() override;

    QTextEdit* title;
    QTextEdit* content;
};

#endif // NOTETEXT_H
