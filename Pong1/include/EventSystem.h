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
	BaseSubscriber() = default;
	virtual ~BaseSubscriber() = default;
protected:
	std::set<EventID> eventIDs;
};

/*
 Base class for events

 */

class BaseEvent {
	friend class EventSystem;
protected:
	std::set<BaseSubscriber *> subscribers;
	EventID eventID;
	BaseEvent();
	virtual ~BaseEvent();
public:
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
	Subscriber();
	Subscriber(std::function<void(Args&&...)> nfunc);
	void rebind(std::function<void(Args&&...)> nfunc);
	~Subscriber();
	virtual void operator()(Args&&... mArgs);
};

/*
 templated event class

 */

template <typename ... Args>
class Event: public BaseEvent {
	friend class EventSystem;
public:
	void subscribe(Subscriber<Args...> * subscriber);
	virtual ~Event() = default;
	virtual void operator()(Args...);
protected:
	Event()=default;
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
	void unregisterEvent(BaseEvent * event); //TODO: i think it should be by ID or name
	BaseEvent * getEvent(const EventID eventID) const;
	BaseEvent * getEvent(const std::string & eventName) const;
private:
	EventID registerEvent(BaseEvent * event, const std::string eventName = nullptr);
	
};

/*
	definitions for Subscriber

*/
template <typename ... Args>
Subscriber<Args...>::Subscriber():Subscriber([](Args&&...){}){}

template <typename ... Args>
Subscriber<Args...>::Subscriber(std::function<void(Args&&...)> nfunc):func(nfunc){};

template <typename ... Args>
void Subscriber<Args...>::rebind(std::function<void(Args&&...)> nfunc){
	func=nfunc;
}

template <typename ... Args>
void Subscriber<Args...>::operator()(Args&&... mArgs){
	this->func(std::forward<Args>(mArgs)...);
}

template <typename ... Args>
Subscriber<Args...>::~Subscriber(){
	for (auto eID : eventIDs){
		Event<Args...> * pEvent = Singleton<EventSystem>::getInstance()->getEvent<Args...>(eID);
		if (pEvent != nullptr) pEvent->unsusbcribe(this);
	}
}

/*
	definitions for Event

*/

template <typename ... Args>
void Event<Args...>::operator()(Args... mArgs){
	for (auto subscriber : subscribers){
		auto s = dynamic_cast<Subscriber<Args...>*>(subscriber);
		if(s!=nullptr) (*s)(std::forward<Args>(mArgs)...);
	}
}

template <typename ... Args>
void Event<Args...>::subscribe(Subscriber<Args...> * subscriber ){
	subscribers.insert(subscriber);
}

/*
	definitions for EventSystem

*/

template <typename ... Args>
Event<Args...> * EventSystem::newEvent(const std::string eventName){
	//TODO: check for eventName in events map. if it is there, throw
	Event<Args...> * event = new Event<Args...>();
	registerEvent(event, eventName);
	return event;
}

template <typename ... Args>
Event <Args...> * EventSystem::getEvent(const EventID eventID) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventID));
}

template <typename ... Args>
Event<Args...> * EventSystem::getEvent(const std::string eventName) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventName));
}