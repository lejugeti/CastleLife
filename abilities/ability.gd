class_name Ability
extends Node


var ability_name: String
var tag: Tag


func assert_valid_ability() -> void:
    assert(!ability_name.is_empty())


func get_ability_name() -> String:
    return ability_name


func equals(other: Ability) -> bool:
    return ability_name == other.get_ability_name()


func execute():
    assert(false, "The execute method should be implemented.")
