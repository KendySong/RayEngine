#pragma once
#include <unordered_map>
#include <functional>

struct KeyEvent
{
public :
    std::unordered_map<int, std::function<void()>> down;
    std::unordered_map<int, std::function<void()>> hold;
    std::unordered_map<int, std::function<void()>> up;
};