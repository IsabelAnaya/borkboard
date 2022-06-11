#include "Note.h"
#include "NoteText.h"
#include <iostream>

NoteText::NoteText(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    title = new QTextEdit(this);
    title->setText(tr("insert title..."));
    title->setFixedHeight(27);
    title->setFrameStyle(QFrame::StyledPanel);
    title->setLineWidth(2);

    content = new QTextEdit(this);
    content->setText(tr("type text here..."));
    content->setFixedHeight(80);
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    lay->addWidget(title);
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteText::NoteText(QString t, QString c, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    title = new QTextEdit(this);
    title->setText(t);
    title->setFixedHeight(27);
    title->setFrameStyle(QFrame::StyledPanel);
    title->setLineWidth(2);

    content = new QTextEdit(this);
    content->setText(c);
    content->setFixedHeight(80);
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    lay->addWidget(title);
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

void NoteText::saveData(std::ofstream *file) {
    *file << title->toPlainText().toStdString() << std::endl;
    *file << content->toPlainText().toStdString() << std::endl;

    *file << this->pos().x() << std::endl;
    *file << this->pos().y() << std::endl;
}

void NoteText::readData(std::ifstream *file) {
    std::string temp;
    std::getline(*file, temp);
    title->setText(QString::fromStdString(temp));
    std::cout << "benchmark 9x: getting title (Note); " << temp << std::endl;

    std::getline(*file, temp);
    content->setText(QString::fromStdString(temp));
    std::cout << "benchmark 10x: getting content (Note); " << temp << std::endl;
}

NoteText::~NoteText() {
    delete title;
    delete content;
    delete lay;
}
