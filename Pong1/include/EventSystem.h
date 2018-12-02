#pragma once

#include <map>
#include <string>
#include <set>
#include <functional>

using EventID = std::size_t;

class Message {

};

class Subscriber {
	virtual void update(Message msg) = 0;
};

class Event {
private:
	std::set<Subscriber *> subscribers;

public:
	Event();
	virtual ~Event();
	void subscribe(Subscriber * subscriber);
	void unsusbcribe(Subscriber * subscriber);
	void notify(Message msg);
	
};

// for now, this will be a singleton
// later will be included in the engine core systems
// and will be accessed through the engine instance, like Engine::getSystem<EventSystem>()

class EventSystem {
	
private:
	//ctor:
	//must initialize core events, like input keys, mouse, etc
	static EventSystem * instance;
	EventSystem();
	std::map<EventID, Event *> events;
	std::map<std::string, EventID> eventNames;
	inline EventID getNewID() {
		static EventID lastID = 0;
		return lastID++;
	}
public:
	static EventSystem * getInstance();
	//dtor to remove the core events
	EventID registerEvent(Event * event, const std::string name = nullptr);
	void unregisterEvent(Event * event);
	void unregisterEvent(const EventID eventID);
	void unregisterEvent(const std::string eventName);
	Event * getEvent(const EventID eventID) const;
	Event * getEvent(const std::string eventName) const;
	void update();	//polls events from SDL event pool and maybe other things (?)
};

