#include "include\EventSystem.h"

EventID EventSystem::registerEvent(Event * event, const std::string name) {
	EventID newEID = getNewID();
	events[newEID] = event;
	return EventID();
}

void EventSystem::unregisterEvent(Event *  event){
	for (std::map<EventID, Event *>::iterator iter = events.begin(); iter != events.end();iter++) {
		if (iter->second == event) {
			events.erase(iter);
			break;
		}
	}
}

void EventSystem::unregisterEvent(const EventID eventID){
	std::map<EventID, Event*>::iterator iter = events.find(eventID);
	events.erase(iter);
}

void EventSystem::unregisterEvent(const std::string eventName) {
	unregisterEvent(eventNames.find(eventName)->second);
}

Event * EventSystem::getEvent(const EventID eventID) const {
	return events.find(eventID)->second;
}

Event * EventSystem::getEvent(const std::string eventName) const {
	return events.find(eventNames.find(eventName)->second)->second;
}
