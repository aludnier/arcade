# Arcade
The goal of the project is to create a program that allow the user to choose a game and a display setting and make them work no matter which game or display are choosen.  
The user can also add any game or graphic settting he create if they suit the program structur. 

## build
the project is build using CMake.
so you can build the project by runing those command specifying where you want the program to build: 
```cpp
cmake -B path/build/dir
cmake --build path/build/dir/
```
## features
### lauch
Once the project is build you can execute the program by choosing the base graphic setting should be use.
```cpp
./path/build/dir/arcade  basegraphiclib.so
```

Then you can press the following button to interact with the program:
  - click on **Play** : launch the first game
  - M : switch game
  - P : switch graphic settings
  - O : reset current game
  - L : return to Menu
  - I : close the program

Each game also handle interaction with it own logic.

### Game
The project implement 2 Game by default:
  - Snake
  - MineSweeper

And the user can [implement a new Game](https://github.com/aludnier/arcade/blob/main/README-DEV-IGAME.md) he created

### Display
The project implement 3 display setting by default :
  - SDL2
  - SMFL
  - NCurse

And the user can [implement a new Display Setting](https://github.com/aludnier/arcade/blob/main/README-DEV-IDISPLAY.md) he created


## Documentation

Doxygen diagram on this [github page](https://valtyyy.github.io/arcade-mirror/html)
