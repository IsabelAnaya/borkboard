#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <vector>
#include <QVBoxLayout>
#include <QPushButton>

class Sidebar : public QVBoxLayout {
    Q_OBJECT

public:
    Sidebar(std::vector<QPushButton*> bits);
    ~Sidebar();


};

#endif // SIDEBAR_H
