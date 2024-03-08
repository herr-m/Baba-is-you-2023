#include "../Controller.h"
#include "../../view/View.h"
#include "../../core/Core.h"

Controller::Controller(Core* core, View* view) : _core(core), _view(view) {
    _core->registerObserver(_view);
    _view->setController(this);
};

void Controller::start() {
    _core->update();
    _view->start();
}

void Controller::manageInput(UserInput input) {
    _core->manageInput(input);
    _core->update();
}
