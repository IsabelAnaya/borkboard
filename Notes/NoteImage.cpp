#include "NoteImage.h"

NoteImage::NoteImage(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    imgPath = ":/images/dummy";
    img = QPixmap(imgPath);

    content = new QLabel(this);
    content->setPixmap(img.scaledToHeight(200));
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
    content->setPixmap(img.scaledToHeight(content->height() - 20));
    resize(content->pixmap().width() + 20, this->height());
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
    content->setPixmap(img.scaledToHeight(content->height() - 20));
    resize(content->pixmap().width() + 20, this->height());
}

std::string NoteImage::toText() {
    return imgPath.toStdString();
}

noteType NoteImage::getType() {
    return noteImage;
}

void NoteImage::resizeEvent(QResizeEvent *event) {
    content->setPixmap(img.scaledToHeight(event->size().height() - 20));
    resize(content->pixmap().width() + 20, event->size().height());
}

NoteImage::~NoteImage() {
    delete content;
    delete lay;
}
