#include "EventSystem.h"
#include "Singleton.h"
#include "Util.h"

BaseEvent::BaseEvent():eventID(IdGenerator::getNewID()){}


void BaseEvent::unsusbcribe(BaseSubscriber * subscriber){
	subscriber->eventIDs.erase(eventID);
	subscribers.erase(subscriber);
}

BaseEvent::~BaseEvent(){
	// could use unsubscribe but this way is 'much' faster
	for (BaseSubscriber * s : subscribers) s->eventIDs.erase(eventID);
	Singleton<EventSystem>::getInstance()->unregisterEvent(this);
}

BaseEvent * EventSystem::getEvent(const EventID eventID) const {
	return events.find(eventID)->second;
}

BaseEvent * EventSystem::getEvent(const std::string & eventName) const {
	return eventNames.find(eventName)->second;
}



EventID EventSystem::registerEvent(BaseEvent * event, const std::string eventName) {
	//TODO: improve this please
	events[event->eventID] = event;
	if (eventNames.find(eventName)==eventNames.end()){
		eventNames[eventName]=event;
	} else {
		//throw :D
	}
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
