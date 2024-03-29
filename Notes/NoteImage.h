#ifndef NOTEIMAGE_H
#define NOTEIMAGE_H

#include "Note.h"
#include <QResizeEvent>

class NoteImage: public Note {

public:
    explicit NoteImage(QWidget *parent = nullptr);
    NoteImage(QString c, QWidget *parent);
    ~NoteImage();

    void changeImage(QString newPath);
    QString toText() override;
    noteType getType() override;

    QPixmap img;
    QLabel* content;
    QString imgPath;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // NOTEIMAGE_H
