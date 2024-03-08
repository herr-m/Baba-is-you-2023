#include "../ConsoleView.h"
#include "../ConsoleSprites.h"
#include "../../core/Map.h"
#include "../../core/Utils.h"
#include "../../core/Core.h"
#include <ncurses.h>
#include <algorithm>

ConsoleView::ConsoleView(unsigned vSize, unsigned hSize) : _running{true} {
    initscr();
    start_color();
    noecho();
    refresh();
    for(const auto& [_, sprite] : sprites)
        init_pair(sprite.color, sprite.fg, sprite.bg);

    _window = newwin((vSize+1)*2, (hSize+1)*3, 0, 0);
    keypad(_window, TRUE);
    wrefresh(_window);
}
ConsoleView::~ConsoleView() {
    endwin();
}
void ConsoleView::displayMap(const Map& map) const {
    wclear(_window);
    box(_window, 0, 0);
    std::for_each(std::begin(map.entities), std::end(map.entities), [&](const MapEntity& entity) {
        wattron(_window, COLOR_PAIR(sprites.at(entity.getType()).color));
        mvwprintw(_window, entity.getPosition().first*2+1, entity.getPosition().second*3+1, sprites.at(entity.getType()).image[0].c_str());
        mvwprintw(_window, entity.getPosition().first*2+2, entity.getPosition().second*3+1, sprites.at(entity.getType()).image[1].c_str());
        wattroff(_window, COLOR_PAIR(sprites.at(entity.getType()).color));
    });
    wrefresh(_window);
}
UserInput ConsoleView::getUserInput() const {
    switch (wgetch(_window)) {
        case KEY_UP: return UserInput::UP;
        case KEY_DOWN: return UserInput::DOWN;
        case KEY_LEFT: return UserInput::LEFT;
        case KEY_RIGHT: return UserInput::RIGHT;
        case 'r': return UserInput::RESET;
        case 's': return UserInput::SAVE;
        case 'q': return UserInput::QUIT;
        default: return UserInput::NONE;
    }
}

void ConsoleView::start() const {
    while(_running)
        _controller->manageInput(getUserInput());
}

void ConsoleView::update(const nvs::Subject* subject) {
    const Core* coreptr{static_cast<const Core*>(subject)};
    displayMap(coreptr->getMap());
    _running = !coreptr->isGameOver();
}
