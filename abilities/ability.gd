class_name Ability
extends Node


var ability_name: String


func asser_valid_ability() -> void:
    assert(!ability_name.is_empty())


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass


func get_ability_name() -> String:
    return ability_name


func equals(other: Ability) -> bool:
    return ability_name == other.get_ability_name()


func execute():
    pass
