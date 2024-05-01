class_name TimetableEvent
extends Node


var time_to_start: DateTime:
    get:
        return time_to_start
    set(value):
        time_to_start = value

var tasks: Array[Ability] = []


func add_task(task: Ability) -> void:
    tasks.append(task)
