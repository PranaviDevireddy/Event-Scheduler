#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>

using namespace std;

class Event {
public:
    int event_id;
    string event_name;
    time_t event_time;  // Timestamp of when the event is scheduled
    string event_details;

    // Default constructor (required by unordered_map)
    Event() : event_id(0), event_name(""), event_time(0), event_details("") {}

    // Constructor to initialize the event with values
    Event(int id, string name, time_t time, string details)
        : event_id(id), event_name(name), event_time(time), event_details(details) {}

    // Comparator function to define priority (earliest event has the highest priority)
    bool operator>(const Event& other) const {
        return event_time > other.event_time;  // Min-heap: earlier events should be at the top
    }

    // To display event details
    void display() const {
        cout << "Event ID: " << event_id
             << ", Event Name: " << event_name
             << ", Event Time: " << ctime(&event_time)  // Converts time_t to human-readable format
             << ", Event Details: " << event_details << endl;
    }
};

int main() {
    // Create an unordered_map to store events, where the key is the event_id
    unordered_map<int, Event> event_map;

    // Sample data for events
    event_map[1] = Event(1, "Event 1", time(0), "Details of event 1");
    event_map[2] = Event(2, "Event 2", time(0) + 3600, "Details of event 2");  // 1 hour later
    event_map[3] = Event(3, "Event 3", time(0) + 7200, "Details of event 3");  // 2 hours later

    // Output events using the display method
    cout << "List of Events: " << endl;
    for (const auto& pair : event_map) {
        pair.second.display();  // Calls the display method of each event object
    }
 
    // You can also use the priority defined by the `>` operator
    // For example, you could sort the events by time, but the unordered_map
    // doesn't maintain any order, so let's use a priority queue if needed.

    return 0;
}
