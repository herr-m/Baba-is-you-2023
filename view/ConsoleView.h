/**
    @file ConsoleView.h
    @brief This file contains the declaration of the ConsoleView class.
*/
#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"

// Forward declarations
enum class UserInput;
typedef struct _win_st WINDOW;

/**
    @class ConsoleView
    @brief Class representing the console view of the game.
    @details The ConsoleView class is responsible for displaying the game on the console and getting user input.
    @note It inherits from the nvs::Observer class and is notified of any changes in the game state. (must override void update())
*/
class ConsoleView : public View {
    bool _running;
    unsigned _hdim, _vdim;
    WINDOW* _window;

    void displayMap(const Map& map) const;
    UserInput getUserInput() const;
public:
    /**
        @brief Constructs a new ConsoleView object.
        @param vSize The vertical size of the console window.
        @param hSize The horizontal size of the console window.
    */
    ConsoleView(unsigned vSize, unsigned hSize);
    /**
        @brief Destroys the ConsoleView object and frees the ncurses window.
    */
    ~ConsoleView();
    /**
        @brief Starts the input loop
    */
    void start() const override;
    /**
        @brief Implementation of the update method of the nvs::Observer class.
        @details This method is called whenever the game state changes and updates the view accordingly.
        @param subject Pointer to the nvs::Subject object that triggered the update.
    */
    void update(const nvs::Subject* subject) override;
};

#endif //CONSOLEVIEW_H