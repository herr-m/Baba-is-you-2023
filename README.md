# Baba is You
C++ implementation of [Baba is you](https://store.steampowered.com/app/736260/Baba_Is_You/), originally created by Arvi Teikari for the Nordic Game Jam.

This version uses the MVC design pattern, and features a terminal frontend (Ncurses) and a graphical frontend (QT).

The game levels are stored as text files, which makes them editable!

Unit tests are written using the catch library.

## Demo
Terminal version\
![Terminal demo](https://github.com/herr-m/Baba-is-you-2023/blob/master/demo_console.gif)

Graphical version\
![GUI demo](https://github.com/herr-m/Baba-is-you-2023/blob/master/demo_gui.gif)

## Controls
- Movement: `Directional arrows`
- Restart level: `R`
- Save level (creates a new file): `S`
- Quit: `Q`

## Compiling
Use the makefile to compile the game

`make console` for the Ncurses HUD or\
`make gui` for the QT HUD

## Dependencies
- [Ncurses](https://www.gnu.org/software/ncurses)
- [QT5](https://www.qt.io/qt-5-12)
