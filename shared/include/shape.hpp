/*
** EPITECH PROJECT, 2026
** shape hdader
** File description:
** shape
*/

#include <functional>
#include <string>

class IShape {
    public:
        virtual void render() = 0;
        virtual void apply_texture(const std::string &asset) = 0;
};

// declare each shape in each graphic lib in a map
