#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdlib.h>

//TODO: maybe turn this into a namespace? let's think about it some day in the future :D
class IdGenerator {
public:
    static std::size_t getNewID();
};

#endif