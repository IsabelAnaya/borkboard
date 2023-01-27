#include "Note.h"
#include "NoteText.h"
#include <iostream>

NoteText::NoteText(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

//    title = new QTextEdit(this);
//    title->setText(tr("insert title..."));
//    //title->setFixedHeight(27);
//    title->setFrameStyle(QFrame::StyledPanel);
//    title->setLineWidth(2);

    content = new QTextEdit(this);
    content->setText(tr("type text here..."));
    //content->setFixedHeight(80);
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    //lay->addWidget(title);
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);
    this->resize(200, 150);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteText::NoteText(QString c, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

//    title = new QTextEdit(this);
//    title->setText(t);
//    //title->setFixedHeight(27);
//    title->setFrameStyle(QFrame::StyledPanel);
//    title->setLineWidth(2);

    content = new QTextEdit(this);
    content->setText(c);
    //content->setFixedHeight(80);
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    //lay->addWidget(title);
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);
    this->resize(100, 200);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

std::string NoteText::toText() {
    return content->toPlainText().toStdString();
}

noteType NoteText::getType() {
    return noteText;
}

NoteText::~NoteText() {
    //delete title;
    delete content;
    delete lay;
}
