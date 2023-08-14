#ifndef SIDEBARITEM_H
#define SIDEBARITEM_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QDebug>
#include <QVariant>
#include "BoardSwitchButton.h"

class SidebarItem : public QWidget {
    Q_OBJECT

public:
    explicit SidebarItem(QWidget *parent = nullptr, BoardSwitchButton *board = nullptr);
    ~SidebarItem();
    void addItem(SidebarItem* newChild);

    BoardSwitchButton* boardButton;
    int directChildCount;
    std::vector<SidebarItem*> children;

private:
    QVBoxLayout* mainLay;
    QHBoxLayout* subLay;
    QVBoxLayout* childrenLay;
    QFrame* line;

signals:

};

#endif // SIDEBARITEM_H
