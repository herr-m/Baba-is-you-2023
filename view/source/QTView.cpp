#include "../QTView.h"
#include "../QTSprites.h"
#include "../../core/Map.h"
#include "../../core/Utils.h"
#include "../../core/Core.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

void Window::setController(Controller* controller) {
    _controller = controller;
}
void Window::keyPressEvent(QKeyEvent* evt) {
    switch(evt->key()) {
        case Qt::Key_Up: _controller->manageInput(UserInput::UP); break;
        case Qt::Key_Down: _controller->manageInput(UserInput::DOWN); break;
        case Qt::Key_Right: _controller->manageInput(UserInput::RIGHT); break;
        case Qt::Key_Left: _controller->manageInput(UserInput::LEFT); break;
        case Qt::Key_R: _controller->manageInput(UserInput::RESET); break;
        case Qt::Key_Q: _controller->manageInput(UserInput::QUIT); break;
        case Qt::Key_S: _controller->manageInput(UserInput::SAVE); break;
    }
}

void QTView::clearMap() {
    for(unsigned i{}; i<_map.count(); ++i) {
        static_cast<QLabel*>(_map.itemAt(i)->widget())->clear();
    }
}
QTView::QTView(unsigned vSize, unsigned hSize, int argc, char** argv) 
: QApplication(argc, argv), _map(&_window) {
    _window.setWindowTitle("BABA");
    _window.setPalette(QPalette(QPalette::Window, Qt::black));
    for(unsigned row=0; row<hSize; ++row)
        for(unsigned col=0; col<vSize; ++col) {
            QLabel* label = new QLabel(); label->setScaledContents(true);
            _map.addWidget(label, row, col);
        }
    _window.show();

    loadSprites();
}
void QTView::start() const {
    exec();
}
void QTView::setController(Controller* controller) {
    _window.setController(controller);
}
void QTView::update(const nvs::Subject* subject) {
    const Core* coreptr{static_cast<const Core*>(subject)};
    if(coreptr->isGameOver()) { return exit(); }
    
    clearMap();
    for(auto entity : coreptr->getMap().entities) {
        auto pos{entity.getPosition()};
        static_cast<QLabel*>(_map.itemAtPosition(pos.first, pos.second)->widget())->setMovie(sprites.at(entity.getType()));
        sprites.at(entity.getType())->start();
    }
}