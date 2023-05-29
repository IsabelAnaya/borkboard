#include "NoteImage.h"
#include "NoteText.h"
#include <iostream>

NoteImage::NoteImage(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    imgPath = ":/images/dummy";
    img = QPixmap(imgPath);

    content = new QLabel(this);
    content->setFixedHeight(200);
    content->setPixmap(img.scaled(200, content->height(), Qt::KeepAspectRatio));
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);
    content->setAttribute(Qt::WA_TransparentForMouseEvents);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteImage::NoteImage(QString c, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    imgPath = c;
    img = QPixmap(imgPath);

    content = new QLabel(this);
    content->setFixedHeight(80);
    content->setPixmap(img.scaled(content->width(), content->height(), Qt::KeepAspectRatio));
    content->setFrameStyle(QFrame::StyledPanel);
    content->setLineWidth(2);

    lay = new QVBoxLayout;
    lay->addWidget(content);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);
    content->setAttribute(Qt::WA_TransparentForMouseEvents);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

void NoteImage::changeImage(QString newPath) {
    imgPath = newPath;
    img = QPixmap(imgPath);
    content->setPixmap(img.scaled(content->width(), content->height(), Qt::KeepAspectRatio));
}

std::string NoteImage::toText() {
    return imgPath.toStdString();
    //need the pixmap
}

noteType NoteImage::getType() {
    return noteImage;
}

void NoteImage::resizeEvent(QResizeEvent *event) {
    content->setFixedHeight(this->height() - 20);
    content->setPixmap(img.scaled(content->width(), content->height(), Qt::KeepAspectRatio));
}

NoteImage::~NoteImage() {
    delete content;
    delete lay;
}
