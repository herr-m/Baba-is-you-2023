/**
    @file QTView.h
    @brief This file contains the declaration of the QTView class.
*/

#ifndef QTVIEW_H
#define QTVIEW_H

#include "View.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>

/**
    @class Window
    @brief A wrapper class for QWidget.
    @details Contains an event handler and a Controller for input transmision.
*/
class Window : public QWidget{
    Controller* _controller;
public:
    /**
        @brief Setter for the controller
        @param controller The controller
    */
    void setController(Controller* controller);
protected:
    void keyPressEvent(QKeyEvent* evt);
};

/**
    @class QTView
    @brief Class representing the view of the game in the QT framefork.
    @details The QTView class is responsible for displaying the game in the QT framework and getting user input.
    @note It inherits from the nvs::Observer class and is notified of any changes in the game state. (must override void update())
*/
class QTView : public View, public QApplication {
    Window _window;
    QGridLayout _map;
    void clearMap();
public:
    /**
        @brief Constructs a new QTView object.
        @param vSize The vertical size of the represented map.
        @param hSize The horizontal size of the represented map.
    */
    QTView(unsigned vSize, unsigned hSize, int argc, char** argv);
    /**
        @brief Starts the QT application loop (event listeners).
    */
    void start() const override;
    /**
        @brief Sets the controller
    */
    void setController(Controller* controller) override;
    /**
        @brief Implementation of the update method of the nvs::Observer class.
        @details This method is called whenever the game state changes and updates the view accordingly.
        @param subject Pointer to the nvs::Subject object that triggered the update.
    */
    void update(const nvs::Subject* subject) override;
};

#endif //CONSOLEVIEW_H