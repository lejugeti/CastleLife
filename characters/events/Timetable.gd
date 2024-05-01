class_name Timetable
extends Node2D


var clock: Clock:
    get:
        return clock
    set(value):
        clock = value


## Should always be sorted by ascendant DateTime
var events: Array[TimetableEvent] = []

signal time_to_start_event(event: TimetableEvent)


static func from_clock(clock: Clock) -> Timetable:
    var timetable_pack = load("res://characters/events/Timetable.tscn")
    var timetable = timetable_pack.instantiate()
    timetable.clock = clock
    clock.time_changed.connect(timetable.check_if_should_start_event)
    return timetable


func check_if_should_start_event(current_time: DateTime):
    assert(current_time != null)

    if(events.size() != 0):
        var next_event: TimetableEvent = events[0]
        if(current_time.is_after(next_event.time_to_start)):
            events.erase(next_event)
            time_to_start_event.emit(next_event)


## Add an event to the event list
## and returns the index at which has been inserted
func add_event(new_event: TimetableEvent) -> int:
    assert(new_event != null && new_event.time_to_start != null)

    for i in range(events.size()):
        var current: TimetableEvent = events[i]
        if(event_is_anterior_or_simultaneous(new_event, current)):
            return events.insert(i, new_event)

    return events.insert(events.size(), new_event)


func event_is_anterior_or_simultaneous(event1, event2):
    return event1.time_to_start.is_before(event2.time_to_start) \
        || event1.time_to_start.equals(event2.time_to_start)
