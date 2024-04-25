class_name Ability
extends Node


var ability_name: String
var tag: Tag

## Tags required in before activating this ability
var activation_required_tags: Array[Tag] = []

## If the ability is currently active or not.
## One should plan to disable an ability after its job is done.
var is_active = false


func assert_valid_ability() -> void:
    assert(!ability_name.is_empty())


func get_ability_name() -> String:
    return ability_name


func equals(other: Ability) -> bool:
    return ability_name == other.get_ability_name()


func execute():
    assert(false, "The execute method should be implemented.")
