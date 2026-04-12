/*
** EPITECH PROJECT, 2026
** Utils
** File description:
** shared utils class
*/

#include <queue>
#include "gfx.hpp"

class Utils {
    public:
        template <typename T>
        static std::queue<T> mergeQueues(std::queue<T> q1, std::queue<T> q2)
        {
            while (!q2.empty()) {
                q1.push(q2.front());
                q2.pop();
            }
            return q1;
        }
};
