#include "EventSystem.h"
#include "Singleton.h"

BaseSubscriber::BaseSubscriber():eventID(0) {}

EventID BaseSubscriber::getEvent() {
	return eventID;
}


BaseEvent::BaseEvent(EventID eventID):eventID(eventID){}

void BaseEvent::subscribe(BaseSubscriber * subscriber){
	subscribers.insert(subscriber);
}

void BaseEvent::unsusbcribe(BaseSubscriber * subscriber){
	subscriber->eventID=0;
	for (auto iter = subscribers.begin(); iter!= subscribers.end(); iter++){
		if (iter->second == subscriber) {
			subscribers.erase(iter);
			break;
		}
	}
}

BaseEvent::BaseEvent(){

}

BaseEvent::~BaseEvent(){
	// could use unsubscribe but this way is 'much' faster
	for (BaseSubscriber * s : subscribers) s->eventID=0;
	Singleton<EventSystem>::getInstance()->unregisterEvent(this);
}

BaseEvent * EventSystem::getEvent(const EventID eventID) const {
	return events.find(eventID)->second;
}

BaseEvent * EventSystem::getEvent(const std::string & eventName) const {
	return eventNames.find(eventName)->second;
}

EventID EventSystem::getNewID() {
		static EventID lastID = 1;
		return lastID++;
}

EventID EventSystem::registerEvent(BaseEvent * event, const std::string name) {
	EventID newEID = getNewID();
	events[newEID] = event;
	return EventID();
}

EventSystem::EventSystem() {

}

void EventSystem::unregisterEvent(BaseEvent *  event){
	//for (std::map<EventID, BaseEvent *>::iterator iter = events.begin(); iter != events.end();iter++) {
	for (auto iter = events.begin(); iter != events.end(); iter++) {
		if (iter->second == event) {
			events.erase(iter);
			break;
		}
	}
	//for (std::map<std::string, BaseEvent *>::iterator iter = eventNames.begin(); iter != eventNames.end();iter++) {
	for (auto iter = eventNames.begin(); iter != eventNames.end(); iter++) {
		if (iter->second == event) {
			eventNames.erase(iter);
			break;
		}
	}
}
