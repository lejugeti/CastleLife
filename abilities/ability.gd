class_name Ability
extends Node


var ability_name: String
var tag: Tag

## Tags required before activating this ability
var activation_required_tags: Array[Tag] = []

## Tags blocking the ability activation
var activation_blocking_tags: Array[Tag] = []

## If the ability is currently active or not.
## One should plan to disable an ability after its job is done.
var is_active = false

## Signal to emit when ability just finished executing
signal finished(ability: Ability)

func assert_valid_ability() -> void:
    assert(!self.ability_name.is_empty())


func get_ability_name() -> String:
    return ability_name


func equals(other: Ability) -> bool:
    return ability_name == other.get_ability_name()


func execute():
    assert(false, "The execute method should be implemented.")
