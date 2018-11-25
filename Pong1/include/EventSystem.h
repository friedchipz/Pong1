#pragma once

#include <map>
#include <string>
#include <set>
#include <functional>

using EventID = std::size_t;

class Message {

};

class Subscriber {
	std::function<void(Message)> update;
	virtual void update(Message msg) = 0;
};

class Event {
private:
	std::set<Subscriber *> subscribers;

public:
	Event();
	virtual ~Event();


};

class EventSystem {
	
private:
	std::map<EventID, Event *> events;
	std::map<std::string, EventID> eventNames;
	inline EventID getNewID() {
		static EventID lastID = 0;
		return lastID++;
	}
public:
	//ctors?
	//no dtors needed, the events destruction should be
	//managed by the event creator, surely.
	EventID registerEvent(Event * event, const std::string name = nullptr);
	void unregisterEvent(Event * event);
	void unregisterEvent(const EventID eventID);
	void unregisterEvent(const std::string eventName);
	Event * getEvent(const EventID eventID) const;
	Event * getEvent(const std::string eventName) const;
	void update();	//polls events from SDL event pool and
			//later from the events buffer? maybe?
			//(when multithreading comes in?)
};

