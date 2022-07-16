#include "NoteImage.h"
#include "NoteText.h"
#include <iostream>

NoteImage::NoteImage(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    title = new QTextEdit(this);
    title->setText(tr("insert title..."));
    title->setFixedHeight(27);
    title->setFrameStyle(QFrame::StyledPanel);
    title->setLineWidth(2);

    img = QPixmap("C:/Users/Isabel/Pictures/them.png");

    content = new QLabel(this);
    content->setPixmap(img);
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

NoteImage::NoteImage(QString t, QString c, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    title = new QTextEdit(this);
    title->setText(t);
    title->setFixedHeight(27);
    title->setFrameStyle(QFrame::StyledPanel);
    title->setLineWidth(2);

    content = new QLabel(this);
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

std::string NoteImage::toText() {
    return title->toPlainText().toStdString();
    //need the pixmap
}

noteType NoteImage::getType() {
    return noteImage;
}

NoteImage::~NoteImage() {
    delete title;
    delete content;
    delete lay;
}
