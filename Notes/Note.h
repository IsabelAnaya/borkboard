#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QLabel>
#include <QMimeData>
#include <QTextEdit>
#include <QDrag>
#include <QVBoxLayout>
#include <fstream>

enum noteType { noteImage, noteText, noteBoard, noteFile, noteSticker };

//note semi-abstract class
class Note : public QFrame {

public:
    explicit Note(QWidget *parent = nullptr);
    //Note(QString t, QString c, QWidget *parent);
    ~Note();

    int getID();
    void setColor(int c);

    virtual QString toText();
    virtual noteType getType();

    QVBoxLayout* lay;
    int ID;
    int color;

    bool locked = false;
    //float len, wid;

protected:

};

#endif // NOTE_H
