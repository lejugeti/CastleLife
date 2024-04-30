class_name Clock
extends Node2D


@export var minutes_every_tick: int = 5
@export var seconds_for_tick: float = 5.0

## Unix representation of time
var date_time: DateTime

## Fired every time time has changed on the clock
signal time_changed(date_time: String)


func start(initial_date_time: String) -> void:
    date_time = DateTime.from_date_time_string(initial_date_time)
    $Timer.timeout.connect(add_time)
    $Timer.start(seconds_for_tick)


func add_time():
    date_time.add_minutes(minutes_every_tick)
    time_changed.emit(date_time.get_time())

