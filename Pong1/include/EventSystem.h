#pragma once

#include <map>
#include <string>
#include <set>
#include <functional>

using EventID = std::size_t;

class BaseSubscriber{
	//don't like this...
	friend class BaseEvent;
public:
	virtual ~BaseSubscriber();
	EventID getEventID();
protected:
	EventID eventID;
};

class BaseEvent {
	friend class EventSystem;
private:
	std::set<BaseSubscriber *> subscribers;
protected:
	EventID eventID;
public:
	BaseEvent() = default;
	virtual ~BaseEvent();
	virtual void subscribe(BaseSubscriber * subscriber);
	void unsusbcribe(BaseSubscriber * subscriber);
};

template <typename ... Args>
class Event: public BaseEvent {
public:
	void subscribe(BaseSubscriber * subscriber);

}; 

template <typename ... Args>
class Subscriber: public BaseSubscriber {
	// i definitely don't like this
	friend class Event<Args>;
protected:
	std::function<void(Args&&...)>;
public:
	Subscriber();
	void update(Args&&... mArgs);
	~Subscriber();
};

// for now, this will be a singleton
// later will be included in the engine core systems
// and will be accessed through the engine instance, like Engine::getSystem<EventSystem>()
 
// dont erase it yet, please -  i jsu copied ;)
// i want to check some of the thins we said
/* i was thinking: i don't want any event to be out of EventSystem knowledge
	i want  all of them to have an ID and things like that
	because that way, when the game ends, it will be able to destroy everything
	it's not that it __really really__ matters
	but it will help reducing or debuggin memory leaks (if they happen(and they probably will(at the begining at least)))
	so how can we do this?
	there are two simple ways:
		1) make the Event<> ctor register _this_ (but this has other problems)
		2) make the BaseEvent abstract (this is another part) and the Event<> ctor protected
		   so only EventSystem could create a new event
	the 1st one is _very_ easy to implement and it doesn't imply anything important for design and development
	the 2nd one is 'less' easy and implies that the developers will never use a statement like new Event<...>()
	but EventSystem::newEvent<...>()

	so the Event system will have kind of builder for events?
	yes -  i like builders xD
	this way, the register and unregister function will be private too - i vote for it
	(don't forget about this line)
	the problem here is:
		when is an event destroyed? maybe when the owner (like the object that caused it to instantiate) is destroyed

	but event has subscribers. so what happens if every subscriber unsubscribe?
	nothing bad happens there. it's just that the list will be empty and there will be no one to notify
	but 
but we don't wasnt to destroy event in that case? not necessarily. it may be an event that has ocassional subscribers
	or that was created recently and there's no subscriber subscribed yet
	events and subscribers lifes are independent from each other
	i mean imagine you created some events with some subscribers but on the text stages of game or next level nobody is listening for them
	and you end up with thousands of empty objects in memory not used ones
	this means that you should have destroyed this events before and you didn't
	that's why the EventComponent will manage this, and once the entity with events is destroyed, it will automatically destroy the event too
	in that case you should be really aware when to create event and desctory
	 what about on demand creating and destruction
	 when you subsribe to event if it doesn't exist it is created and when the last listener unsubscribes deleted		
	this won't do. because events are tied to functionality
	for example, when a collider collides with something important for it
	it will trigger an event (send a message, or whatever) like
	OnCollision->update(...) or something like that
	this event must be created before, or this won't be possible
	no you didn't understand
	you have a entity which you want to happen some event on collision
	let's say several entities that will react colEntity->register(OnCollision)
	ok from the beginning
	for entity you defeninely know what kind of events it want to listen to
	(it's not just about kind of events, but which entity triggers them)
	you have both sides so this pub-sub mechanism
	some subscriber(s) register to listen to sole event
	and when event happens it has information who triggered the event so that the subscriber (if interested in that information) can get it
	maybe some are interested some not
		
	this design has three problems:
		1) the signature for the event gets even bulkier
		2) each and every subscriber must implement the way to filter which events want to listen to and which not
		3) (last and most problematic) this is a broadcast. so you have to inform many more subscribers and
			all of them must process the info. worst case, you have a very long list of subscribers with
			a selection method that involves dynamic casts (a bit slow)
			and only one of them is going to use the info
			so you're spending so many cycles in notifying subscribers that spend a lot of cycles processing the info
			just to realize they don't need the message
			don't need what? if they don't need they do not subscribe to event
			if they are subscribed to OnCollision() for example, but they only care about collisions with some kind of entity
			(classical case) you can have an event like Event<Entity*> or you could have multiple events like Event<Wall*>, Event<Bullet*>
			well there maybe can be sunscribtion to 2 types of events
			1. broadcast from any triggerer
			2. you soecify who should trigger to be subscribed			
			this is why EventSystem is useful. it can create the BroadCast or non-entity-dependant events (let's think of a timer, for example)
			(which could be implemented as an entity, but it really doesn't need a representation in the world)
			aha
			events are not _necessarily_ related to entities so you can have 1. and 2.
			but the 2. part can't be instantiated on demand
			and the 1. part would be hard to

	ok let's do this way
	you continue on this and I will spend some time designing a draft of the thing i want (only on paper) an can showyou and we discuss one more time
	maybe visual it will look better
	what do you say? fine, but remember to do lifecycle diagrams ok
	i want to see how much the classical pub-sub or observer pattern will match this case
	^^ perfect, 
	this was a long dscussion xD
	i just realized XD
	80 lines long. and it felt good :D
	
	summary:
		make BaseEvent abstract
		protect Event<> ctors to make them accessible only from EventSystem
		EventSystem::register and unregister will be private
		think about how/when to destroy entity related Events
			maybe make it happen in BaseEvent virtual dtor so EventSystem will be friend of BaseEvent only
		
*/


class EventSystem {
	friend class BaseEvent;
	friend class BaseSubscriber;
private: //members
	std::map<EventID, BaseEvent *> events;
	std::map<std::string, BaseEvent *> eventNames;

public:
	static EventSystem * getInstance();
	template <typename ... Args>
	Event<Args...> * getEvent(const EventID eventID) const;
	template <typename ... Args>
	Event<Args...> * getEvent(const std::string eventName) const;
    
protected:
	void unregisterEvent(BaseEvent * event);
	// no need for those now
	//void unregisterEvent(const EventID eventID);
	//void unregisterEvent(const std::string & eventName);
	BaseEvent * getEvent(const EventID eventID) const;
	BaseEvent * getEvent(const std::string & eventName) const;
private:
	static EventSystem * instance;
	EventSystem();
	inline EventID getNewID();
	EventID registerEvent(BaseEvent * event, const std::string eventName = nullptr); 
	
};

template <typename ... Args>
Event <Args...> * EventSystem::getEvent(const EventID eventID) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventID));
}

template <typename ... Args>
Event<Args...> * EventSystem::getEvent(const std::string eventName) const{
	return dynamic_cast<Event<Args...>*>(getEvent(eventName));
}