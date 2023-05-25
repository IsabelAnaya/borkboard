#ifndef NOTEIMAGE_H
#define NOTEIMAGE_H

#include "Note.h"

class NoteImage: public Note {

public:
    explicit NoteImage(QWidget *parent = nullptr);
    NoteImage(QString c, QWidget *parent);
    ~NoteImage();

    void changeImage(QString newPath);
    std::string toText() override;
    noteType getType() override;

    QPixmap img;
    QLabel* content;
    QString imgPath;

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // NOTEIMAGE_H
