/**
    @file Controller.h
    @brief Defines the Controller class for managing the model.
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

// Forward declarations
class Core;
class View;
enum class UserInput;

/**
    @brief The Controller class manages the model, and creates a link between the game logic and the user interface.
    @tparam T The type of the view used by the Controller.
*/
class Controller {
    Core* _core;
    View* _view;
public:
    /**
        @brief Constructs a new Controller object with the gis);iven Core and ViewWrapper objects.
        @param core A pointer to the Core object used by the Controller.
        @param view A pointer to the ViewWrapper object used by the Controller.
    */
    Controller(Core* core, View* view);

    /**
        @brief Starts the game loop for the Controller.
    */
    void start();

    /**
        @brief Sends user input to the model
    */
    void manageInput(UserInput input);
};

#endif // CONTROLLER_H
