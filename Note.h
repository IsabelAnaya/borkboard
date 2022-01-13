#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QTextEdit>
#include <QDrag>
#include <QVBoxLayout>

#include <fstream>

//note
class Note : public QFrame {
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    Note(QString t, QString c, QWidget *parent);
    ~Note();

    void saveData(std::ofstream *file);

    QTextEdit* title;
    QTextEdit* content;
    QVBoxLayout* lay;
    int ID;
    //float xLoc, yLoc;
    //float len, wid;
};

#endif // NOTE_H
