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

void NoteImage::saveData(std::ofstream *file) {
    *file << title->toPlainText().toStdString() << std::endl;
    //save image location

    *file << this->pos().x() << std::endl;
    *file << this->pos().y() << std::endl;
}

void NoteImage::readData(std::ifstream *file) {
    std::string temp;
    std::getline(*file, temp);
    title->setText(QString::fromStdString(temp));
    std::cout << "benchmark 9x: getting title (Note); " << temp << std::endl;

    //std::getline(*file, temp);
    //content->setText(QString::fromStdString(temp));
    std::cout << "benchmark 10x: getting content (Note); " << temp << std::endl;
}

NoteImage::~NoteImage() {
    delete title;
    delete content;
    delete lay;
}
