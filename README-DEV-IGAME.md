# Implementation of New Game

The arcade project can handle every game library who contain a class who Inherit from the IGame class and implement all of the virtual function in her definition.

```cpp
class IGame {
    public:
        virtual ~IGame() = default;
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void update(std::queue<Event>) = 0;
        virtual std::queue<AnyInstruction> getGfxInstructions() = 0;
        virtual std::queue<GameEvent> getEvent() = 0;
};
```
and define the two following function :

```cpp
extern "C" IGame *create()
{
    return new Snake::GameSnake();
}

extern "C" LIB_TYPE getLibType()
{
    return LIB_TYPE::GAME;
}
```

## Library entry point 
this functions will be used in the core to indentify/instanciate your game and should be define in a separate file from your game 
_**IGame *create()**_ function should return a raw pointer to your new game class.  
_**LIB_TYPE getLibType()**_ function should return the enum LIB_TYPE::GAME defined in [IGame.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/IGame.hpp) used to differentiate Graphic and Game Libraires.   


## New Game Class
### Class constructor
the constructor of the new game should not take any parameter since the core will not give anything threw it.

```cpp
Snake::GameSnake::GameSnake() :
    _matrix(COLUMNS, LINES, Snake::EMPTY, TILESIZE),
    _speed(1)
{
};
```

### init / close
_**void init()**_ :
- init is used to set the game logic to the basic state of the game and will be called when at the load of the game or when switching between games.  

_**void close()**_ :
- is used to close the game and will be called when switching game or stop the program.


### Game Logic
_**void update(std::queue<Event>)**_ :
 - update will handle all the game logic by taking a queue of Event define in [gfx.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/gfx.hpp).
 - you can iterate threw the event queue using :
```cpp
while (!events.empty()) {
  // it's up to you to handle wich event do what
  events.pop();
}
```
_**std::queue<AnyInstruction> getGfxInstructions()**_ :
 - getGfsInstruction return each element of the game that will be send to the display library to draw them.
 - you should return a queue of _AnyInstruction_ who can take any structure define in [gfx.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/gfx.hpp)

_**std::queue<GameEvent> getEvent()**_ :
  - getEvent allow the Game to send instruction to the core like switching or quit the game with a click on a button

## Add to the prject build
To add your game librairie to the project, you can go in the [CMakeList.txt](https://github.com/Valtyyy/arcade-mirror/blob/main/CMakeLists.txt) file and fill the following code to the file

```cpp
SET(GAMENAME
    ${SHARED}
    # The source file of the game
)

add_library(arcade_GAMENAME SHARED
    ${GAMENAME}
    # the source file for the entry point
)

target_include_directories(arcade_GAMENAME PRIVATE
    # the header file of the game
)
```

