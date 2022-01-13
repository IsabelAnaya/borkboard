#include "Note.h"

Note::Note(QWidget *parent) : QFrame(parent) {
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

Note::Note(QString t, QString c, QWidget *parent) : QFrame(parent) {
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

void Note::saveData(std::ofstream *file) {
    *file << title->toPlainText().toStdString() << std::endl;
    *file << content->toPlainText().toStdString() << std::endl;

    *file << this->pos().x() << std::endl;
    *file << this->pos().y() << std::endl;
}

Note::~Note() {
    delete title;
    delete content;
    delete lay;
}
