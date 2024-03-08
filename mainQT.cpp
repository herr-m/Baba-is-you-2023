#include "core/Core.h"
#include "view/QTView.h"
#include "controller/Controller.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc == 1) { std::cout << "A file path containing a level must be specified" << std::endl; return 1; }
    
    Core core{argv[1]};
    QTView view{core.getMap().size.first, core.getMap().size.second, argc, argv};
    Controller controller{&core, &view};
    controller.start();
    return 0;
}