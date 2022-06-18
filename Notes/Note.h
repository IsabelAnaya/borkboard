#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QLabel>
#include <QMimeData>
#include <QTextEdit>
#include <QDrag>
#include <QVBoxLayout>
#include <fstream>

enum noteType { noteImage, noteText, noteBoard, noteFile };

//note semi-abstract class
class Note : public QFrame {
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    Note(QString t, QString c, QWidget *parent);
    ~Note();

    virtual void saveData(std::ofstream *file);
    virtual void readData(std::ifstream *file);
    virtual std::string toText();
    virtual noteType getType();

    QVBoxLayout* lay;
    int ID;
    //float len, wid;

protected:

};

#endif // NOTE_H
