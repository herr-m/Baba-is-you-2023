/**
    @file View.h
    @brief This file contains the declaration of the View virtual class.
*/

#ifndef VIEW_H
#define VIEW_H

#include "../controller/Controller.h"
#include "../utils/observer.h"

// Forward declarations
class Map;
enum class UserInput;

/**
    @class View
    @brief A virtual class for defining views in different frameworks.
    @note Inherits from nvs::Observer
*/
class View : public nvs::Observer {
protected:
    Controller* _controller;
public:
    /**
        @brief Start the input loop, this function must call Controller::manageInput
    */
    virtual void start() const = 0;
    /**
        @brief Setter for the controller
        @param controller The controller
    */
    virtual void setController(Controller* controller) {
        _controller = controller;
    }
};

#endif // VIEW_H
