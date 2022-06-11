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

//note semi-abstract class
class Note : public QFrame {
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    Note(QString t, QString c, QWidget *parent);
    ~Note();

    void saveData(std::ofstream *file);
    void readData(std::ifstream *file);

    QVBoxLayout* lay;
    int ID;
    //float len, wid;
};

#endif // NOTE_H