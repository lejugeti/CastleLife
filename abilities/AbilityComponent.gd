class_name AbilityComponent
extends Node


var _abilities: Array[Ability] = []


func add_ability(ability: Ability) -> void:
    var already_present: bool = _abilities.any(ability.equals)
    if(!already_present):
        _abilities.append(ability)


func remove_ability(ability: Ability) -> void:
    _abilities.erase(ability)


func activate_by_name(ability_name: String) -> void:
    for ability in self._abilities:
        if(ability.get_ability_name() == ability_name):
            try_activate_ability(ability)


## Activates all abilities that share the same tag passed as argument
func activate_by_tag(tag: Tag) -> void:
    for ability in self._abilities:
        if(ability.tag.equals(tag)):
            try_activate_ability(ability)


func try_activate_ability(ability: Ability) -> void:
    if(can_be_activated(ability)):
        ability.is_active = true
        ability.execute()


func can_be_activated(ability: Ability) -> bool:
    return all_required_tags_are_present(ability)


## Determines if all required tags for activation are present in active abilities
func all_required_tags_are_present(ability: Ability) -> bool:
    return ability.activation_required_tags.all(is_part_of_active_tags)


func get_active_abilities() -> Array[Ability]:
    return _abilities.filter(func(ability: Ability): return ability.is_active)


func get_active_tags() -> Array[Tag]:
    var activeTags: Array[Tag] = []
    for activeAbility in get_active_abilities():
        activeTags.append(activeAbility.tag)

    return activeTags


## True if the tag passed as argument matches an already active tag
func is_part_of_active_tags(tag: Tag) -> bool:
    assert(tag != null)
    return get_active_tags().any(func(active: Tag): return active.equals(tag))
