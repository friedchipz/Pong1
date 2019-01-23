#include <iostream>

#include "game.h"
int main2() {
	try {
		Game * game = new Game();
		game->gameLoop();
		delete game;
	}
	catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

#include "EventSystem.h"
#include <string>
class A{
	public:
	float x;
	int i;
	A(float x, int i):x(x), i(i){}
};
int main(){
	auto myEvent = Singleton<EventSystem>::getInstance()->newEvent<A *>();
	auto mySubs = new Subscriber<A*>();
	auto mySubs2 = new Subscriber<A*>();
	myEvent->subscribe(mySubs2);
	myEvent->subscribe(mySubs);
	mySubs->rebind([]( A * a) {std::cout << a->x << a->i << std::endl;});
	mySubs2->rebind([]( A * a ){std::cout << a->x << a->i << std::endl;});
	A a(13.5,15);
	(*myEvent)(&a);
	delete mySubs;
	delete myEvent;
	delete mySubs2;
}