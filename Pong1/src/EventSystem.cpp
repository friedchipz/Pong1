#include "EventSystem.h"

EventID EventSystem::getNewID() {
		static EventID lastID = 1;
		return lastID++;
}

EventID EventSystem::registerEvent(BaseEvent * event, const std::string name) {
	EventID newEID = getNewID();
	events[newEID] = event;
	return EventID();
}

EventSystem * EventSystem::instance = nullptr;

EventSystem * EventSystem::getInstance() {
	if (instance == nullptr) {
		instance = new EventSystem();
	}
	return instance;
}

EventSystem::EventSystem() {

}

void EventSystem::unregisterEvent(BaseEvent *  event){
	for (std::map<EventID, BaseEvent *>::iterator iter = events.begin(); iter != events.end();iter++) {
		if (iter->second == event) {
			events.erase(iter);
			break;
		}
	}
	for (std::map<std::string, BaseEvent *>::iterator iter = eventNames.begin(); iter != eventNames.end();iter++) {
		if (iter->second == event) {
			eventNames.erase(iter);
			break;
		}
	}
}

// obsolete now
/*
void EventSystem::unregisterEvent(const EventID eventID){
	std::map<EventID, BaseEvent*>::iterator iter = events.find(eventID);
	events.erase(iter);
}

void EventSystem::unregisterEvent(const std::string & eventName) {
	unregisterEvent(eventNames.find(eventName)->second);
}
*/
BaseEvent * EventSystem::getEvent(const EventID eventID) const {
	return events.find(eventID)->second;
}

BaseEvent * EventSystem::getEvent(const std::string & eventName) const {
	return eventNames.find(eventName)->second;
}

BaseSubscriber::~BaseSubscriber(){
	if (eventID==0) return;
	BaseEvent * pEvent = EventSystem::getInstance()->getEvent(eventID);
	if (pEvent != nullptr) pEvent->unsusbcribe(this);
}

BaseEvent::~BaseEvent(){
	for (BaseSubscriber * s : subscribers) {
		s->eventID=0;
	}
}
