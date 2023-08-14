#include "SidebarItem.h"

SidebarItem::SidebarItem(QWidget* parent, BoardSwitchButton* board) : QWidget(parent) {
    line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setProperty("class", QString::fromStdString("column"));

    boardButton = board;

    mainLay = new QVBoxLayout;

    mainLay->addWidget(boardButton);


    subLay = new QHBoxLayout;
    childrenLay = new QVBoxLayout;
    subLay->addWidget(line);
    subLay->addLayout(childrenLay);
    mainLay->addLayout(subLay);

    setLayout(mainLay);
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    directChildCount = 0;

}

void SidebarItem::addItem(SidebarItem* newChild) {
    directChildCount++;
    children.push_back(newChild);
    childrenLay->addWidget(newChild);
    //line->setFixedHeight(directChildCount * 20);
}

SidebarItem::~SidebarItem() {
    for (SidebarItem* child : children) {
        delete child;
    }

    delete line;
}
