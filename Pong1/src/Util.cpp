#include <memory>
#include "Util.h"

std::size_t IdGenerator::getNewID() {
	static std::size_t lastID = 1;
	return lastID++;
}