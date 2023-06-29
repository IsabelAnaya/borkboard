#include "NoteSticker.h"

NoteSticker::NoteSticker(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    stickerPath = ":/images/star";
    img = QPixmap(stickerPath);

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

NoteSticker::NoteSticker(int type, QWidget *parent) {
    setMinimumSize(20, 20);

    stickerPath = ":/images/star";
    img = QPixmap(stickerPath);

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

std::string NoteSticker::toText() {
    return "sticker";
}

noteType NoteSticker::getType() {
    return noteSticker;
}

void NoteSticker::resizeEvent(QResizeEvent *event) {
    content->setFixedHeight(this->height() - 20);
    content->setPixmap(img.scaled(content->width(), content->height(), Qt::KeepAspectRatio));
}

NoteSticker::~NoteSticker() {
    delete content;
    delete lay;
}
