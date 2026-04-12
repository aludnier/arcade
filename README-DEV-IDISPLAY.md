# Implementation of New Graphic Library

The arcade project can handle every Graphic library who contain a class who Inherit from the IDisplay class and implement all of the virtual function in her definition.

```cpp
class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void clear() = 0;
        virtual void render(std::queue<AnyInstruction>) = 0;
        virtual std::queue<Event> pollEvents() = 0;
};
```
and define the two following function :

```cpp
extern "C" IDisplay *create()
{
    return new SDL2();
}

extern "C" LIB_TYPE getLibType()
{
    return LIB_TYPE::DISPLAY;
}
```

## Library entry point 
this functions will be used in the core to indentify/instanciate your graphic library  
_**IDisplay *create()**_ function should return a raw pointer to your new graphic class.  
_**LIB_TYPE getLibType()**_ function should return the enum LIB_TYPE::DISPLAY defined in [IDisplay.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/IDisplay.hpp) used to differentiate Graphic and Game Libraires.   


## New Graphic Class
### Class Constructor
the constructor of the new graphic library should not take any parameter since the core will not give anything throught it.

```cpp
SDL2::SDL2() : _window(nullptr), _renderer(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(SDL_GetError());
    if (TTF_Init() != 0)
        throw std::runtime_error(SDL_GetError());
    _events = {};
}
```

### init / close
_**void init()**_ :
- init() is used to initialize the window where the game will be displayed and will be called when at the load of the game or when switching between graphic library.  

_**void close()**_ :
- close() is used to close the close the window of the graphic lib and will be called when switching game or stop the program.


### Display function
_**void render(std::queue<AnyInstruction>)**_ :
  - allow to display on the screen a queue of AnyInstruction define in [gfx.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/gfx.hpp).
  - AnyInstruction can handle every structure define in [gfx.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/gfx.hpp)
so your graphic class should be able to display all the structurs define in this file.

_**void clear()**_ :
  - clear() should clear everything on the display support to allow _render()_ to draw a new iteration of the instructions.

_**std::queue<Event> pollEvents()**_ :
  - this functon allow your graphic library to send which event happen to the game throught the core.
  - the Event type is define in [gfx.hpp](https://github.com/Valtyyy/arcade-mirror/blob/main/shared/include/gfx.hpp) and handle either the coordinate of a click or a key pressed.

## Add to the prject build
To add your game librairy to the project, you can go in the [CMakeList.txt](https://github.com/Valtyyy/arcade-mirror/blob/main/CMakeLists.txt) file and fill the following code to the file

```cpp
SET(LIBNAME
    ${SHARED}
    # The source file of the game
)

add_library(arcade_LIBNAME SHARED
    ${LIBNAME}
)

target_include_directories(arcade_LIBNAME PRIVATE
    # the header file of the game
)
```
