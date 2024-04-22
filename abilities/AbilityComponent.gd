class_name AbilityComponent
extends Node


var _abilities: Array[Ability] = []


func add_ability(ability: Ability):
    var already_present: bool = _abilities.any(ability.equals)
    if(!already_present):
        _abilities.append(ability)


func remove_ability(ability: Ability):
    _abilities.erase(ability)


func activate_by_name(ability_name: String):
    for ability in self._abilities:
        if(ability.get_ability_name() == ability_name):
            ability.execute()


## Activates all abilities that share the same tag passed as argument
func activate_by_tag(tag: Tag):
    for ability in self._abilities:
        if(ability.tag.equals(tag)):
            ability.execute()
