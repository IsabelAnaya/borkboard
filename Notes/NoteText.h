#ifndef NOTETEXT_H
#define NOTETEXT_H

#include "Note.h"

class NoteText: public Note {

public:
    explicit NoteText(QWidget *parent = nullptr);
    NoteText(QString c, QWidget *parent);
    ~NoteText();

    std::string toText() override;
    noteType getType() override;

    //QTextEdit* title;
    QTextEdit* content;
};

#endif // NOTETEXT_H
