#pragma once

#include <map>
#include <string>
#include <set>
#include <functional>
#include "Singleton.h"

using EventID = std::size_t;
/*
 Base class for subscribers
 i am here
 
 */

class BaseSubscriber{
	//don't like this...
	friend class BaseEvent;
public:
	BaseSubscriber();
	virtual ~BaseSubscriber() = default;
	EventID getEventID();
protected:
	EventID eventID;
};

/*
 Base class for events

 */

class BaseEvent {
	friend class EventSystem;
private:
	std::set<BaseSubscriber *> subscribers;
protected:
	EventID eventID;
	BaseEvent(EventID eventID);
	~BaseEvent();
public:
	virtual void subscribe(BaseSubscriber * subscriber);
	void unsusbcribe(BaseSubscriber * subscriber);
};

/*
 templated subscriber class

 */

template <typename ... Args>
class Subscriber: public BaseSubscriber {
protected:
	std::function<void(Args&&...)> func;
public:
	Subscriber(std::function<void(Args&&...)> nfunc);
	~Subscriber();
	void update(Args&&... mArgs);
};

/*
 templated event class

 */

template <typename ... Args>
class Event: public BaseEvent {
	friend class EventSystem;
public:
	//virtual void subscribe(Subscriber<Args...> * subscriber);
	virtual ~Event() = default;
protected:
	Event(EventID eventID);
}; 

/*
  main Event Manager

*/

class EventSystem {
	friend class BaseEvent;
	friend class BaseSubscriber;
private: //members
	std::map<EventID, BaseEvent *> events;
	std::map<std::string, BaseEvent *> eventNames;

public:
	template <typename ... Args>
	Event<Args...> * newEvent(const std::string eventName = "");
	template <typename ... Args>
	Event<Args...> * getEvent(const EventID eventID) const;
	template <typename ... Args>
	Event<Args...> * getEvent(const std::string eventName) const;
    EventSystem();
protected:
	void unregisterEvent(BaseEvent * event);
	BaseEvent * getEvent(const EventID eventID) const;
	BaseEvent * getEvent(const std::string & eventName) const;
private:
	
	inline EventID getNewID();
	EventID registerEvent(BaseEvent * event, const std::string eventName = nullptr);
	
};

/*
	definitions for Subscriber

*/

template <typename ... Args>
Subscriber<Args...>::Subscriber(std::function<void(Args&&...)> nfunc):func(nfunc){};

template <typename ... Args>
void Subscriber<Args...>::update(Args&&... mArgs){
	this->func(std::forward<Args>(mArgs)...);
}

template <typename ... Args>
Subscriber<Args...>::~Subscriber(){
	if (eventID==0) return;
	Event<Args...> * pEvent = Singleton<EventSystem>::getInstance()->getEvent<Args...>(eventID);
	if (pEvent != nullptr) pEvent->unsusbcribe(this);
}

/*
	definitions for Event

*/

template <typename ... Args>
Event<Args...>::Event(EventID eventID):BaseEvent(eventID){};

/*
	definitions for EventSystem

*/

template <typename ... Args>
Event<Args...> * EventSystem::newEvent(const std::string eventName){
	Event<Args...> * event = new Event<Args...>(getNewID());
	registerEvent(event, eventName);
}

template <typename ... Args>
Event <Args...> * EventSystem::getEvent(const EventID eventID) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventID));
}

template <typename ... Args>
Event<Args...> * EventSystem::getEvent(const std::string eventName) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventName));
}