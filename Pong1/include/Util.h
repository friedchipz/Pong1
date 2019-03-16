#pragma once
#include <memory>

//T O D O: maybe turn this into a namespace? let's think about it some day in the future :D

class IdGenerator {
public:
    static std::size_t getNewID();
};
