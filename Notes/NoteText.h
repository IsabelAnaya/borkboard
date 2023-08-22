#ifndef NOTETEXT_H
#define NOTETEXT_H

#include "Note.h"

class NoteText: public Note {

public:
    explicit NoteText(QWidget *parent = nullptr);
    NoteText(QString c, QWidget *parent);
    ~NoteText();

    QString toText() override;
    noteType getType() override;
    void toMarkdown();
    void toPlaintext();

    //QTextEdit* title;
    QTextEdit* content;
    QString text;

    bool editable = false;
};

#endif // NOTETEXT_H
