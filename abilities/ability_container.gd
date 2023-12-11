class_name AbilityContainer
extends Node


var _abilities: Array[Ability] = []

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
    pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass


func add_ability(ability: Ability):
    var already_present: bool = _abilities.any(ability.equals)
    if(!already_present):
        _abilities.append(ability)


func remove_ability(ability: Ability):
    _abilities.erase(ability)

