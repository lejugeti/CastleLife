class_name DateTime
extends Node


var unix_timestamp: int = 0:
    get:
        return unix_timestamp
    set(value):
        assert(value >= 0)
        unix_timestamp = value


const minute: int = 60
const hour: int = minute * 60
const day: int = hour * 24


## Constructs a new DateTime from an ISO date-time/time String
static func from_date_time_string(date_time: String):
    var dt: DateTime = DateTime.new()
    dt.unix_timestamp = Time.get_unix_time_from_datetime_string(date_time)

    return dt


func add_seconds(seconds: int) -> void:
    unix_timestamp += seconds


func remove_seconds(seconds: int) -> void:
    unix_timestamp -= seconds


func add_minutes(minutes_count: int) -> void:
    unix_timestamp += minutes_count * minute


func remove_minutes(minutes_count: int) -> void:
    unix_timestamp -= minutes_count * minute


func add_hours(hours_count: int) -> void:
    unix_timestamp += hours_count * hour


func remove_hours(hours_count: int) -> void:
    unix_timestamp -= hours_count * hour


func get_time() -> String:
    return Time.get_time_string_from_unix_time(unix_timestamp)


func get_date_time() -> String:
    return Time.get_datetime_string_from_unix_time(unix_timestamp)


func equals(other: DateTime) -> bool:
    return unix_timestamp == other.unix_timestamp


func is_before(other: DateTime) -> bool:
    return unix_timestamp < other.unix_timestamp


func is_after(other: DateTime) -> bool:
    return unix_timestamp > other.unix_timestamp
