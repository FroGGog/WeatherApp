# Weather App
![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square) 

This project is one on my way on learning Qt.

## Controls

Use input field - enter city name and than press "Find" button.

## Screenshots
![Screenshot](Screenshots/startScreen.png?raw=true "Programm starts")

![Screenshot](Screenshots/inProgress.png?raw=true "Programm in progress")

### Must Have (dependencies)
- A valid C++ compiler - clang, gcc, msvc that supports c++17
- cmake >= v3.15

## Building

The CMAKE is set up to automatically download the dependencies and link against it. It will be done when configuring cmake.
Builded in Qt Creator, don't really tried to build without it.

Add your API key from https://weatherstack.com/ to "datagetter.cpp".

```
git clone https://github.com/FroGGog/WeatherApp.git
cd WeatherApp
cmake build .
```

Feel free to fork, fix the issues and contribute. Help is always welcome.
