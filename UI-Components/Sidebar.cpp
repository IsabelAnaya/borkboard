#include "Sidebar.h"

Sidebar::Sidebar(std::vector<BoardSwitchButton*> bits) {
    buttons = bits;

    for (unsigned int i = 0; i < bits.size(); i++) {
        this->addWidget(bits[i]);
    }
}

Sidebar::~Sidebar() {

    int toDelete = this->count();
    for (int i = 0; i < toDelete; i++) {
        QLayoutItem *temp = this->takeAt(0);
        delete temp->widget();
        delete temp;
    }
}
