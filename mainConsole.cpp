#include "core/Core.h"
#include "view/ConsoleView.h"
#include "controller/Controller.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc == 1) { std::cout << "A file path containing a level must be specified" << std::endl; return 1; }
    
    Core core{argv[1]};
    ConsoleView view{core.getMap().size.first, core.getMap().size.second};
    Controller controller{&core, &view};
    controller.start();
    return 0;
}