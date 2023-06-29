#ifndef NOTESTICKER_H
#define NOTESTICKER_H

#include "Note.h"

class NoteSticker : public Note {

public:
    NoteSticker(QWidget *parent = nullptr);
    NoteSticker(int type, QWidget *parent = nullptr);
    ~NoteSticker();

    std::string toText() override;
    noteType getType() override;

private:
    QString stickerPath;
    QPixmap img;
    QLabel* content;

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // NOTESTICKER_H
