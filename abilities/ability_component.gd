class_name AbilityComponent
extends Node


## Abilities without any input binding for activation
var _abilities_without_binding: Array[Ability] = []
## Abilities that are activated by inputs
var _abilities_by_binding: Dictionary = {}


func get_abilities(binding: StringName) -> Array:
    if(binding == null || binding.is_empty()):
        return _abilities_without_binding

    else :
        if(_abilities_by_binding.get(binding) == null):
            _abilities_by_binding[binding] = []

        return _abilities_by_binding[binding]


func add_ability(ability: Ability) -> void:
    var binding: StringName = ability.input_binding
    var abilities_binded: Array = get_abilities(binding)
    abilities_binded.append(ability)


func remove_ability(ability: Ability) -> void:
    var binding: StringName = ability.input_binding
    var abilities_binded: Array = get_abilities(binding)
    abilities_binded.erase(ability)


func wait_and_remove_ability(ability: Ability) -> void:
    var binding: StringName = ability.input_binding
    var abilities_binded: Array = get_abilities(binding)
    var index_to_remove: int = abilities_binded.find(ability)

    if(index_to_remove > -1):
        if(ability.is_active):
            ability.finished.connect(_on_ability_finished_remove_ability)
        else:
            remove_ability(ability)


func _on_ability_finished_remove_ability(finished_ability: Ability):
    remove_ability(finished_ability)
    finished_ability.finished.disconnect(_on_ability_finished_remove_ability)


func activate_by_input_binding(binding: StringName):
    var abilities_binded: Array = get_abilities(binding)

    if(abilities_binded != null && abilities_binded.size() > 0):
        try_activate_ability(abilities_binded[0])


func activate_by_name(ability_name: String) -> void:
    for ability in self._abilities_without_binding:
        if(ability.get_ability_name() == ability_name):
            try_activate_ability(ability)
            break


func activate_by_tag(tag: Tag) -> void:
    for ability in self._abilities_without_binding:
        if(ability.tag.equals(tag)):
            try_activate_ability(ability)
            break


func try_activate_ability(ability: Ability) -> void:
    if(can_be_activated(ability)):
        ability.is_active = true
        ability.execute()


func can_be_activated(ability: Ability) -> bool:
    return !ability.is_active \
        && all_required_tags_are_present(ability) \
        && no_blocking_tag_are_present(ability)


## Determines if all required tags for activation are present in active abilities
func all_required_tags_are_present(ability: Ability) -> bool:
    return ability.activation_required_tags.all(is_part_of_active_tags)


## Determines no blocking tags are present in active abilities
func no_blocking_tag_are_present(ability: Ability) -> bool:
    return !ability.activation_blocking_tags.any(is_part_of_active_tags)


func get_active_abilities() -> Array:
    return get_all_abilities().filter(func(ability: Ability): return ability.is_active)


func get_active_tags() -> Array[Tag]:
    var activeTags: Array[Tag] = []
    for activeAbility in get_active_abilities():
        activeTags.append(activeAbility.tag)

    return activeTags


## True if the tag passed as argument matches an already active tag
func is_part_of_active_tags(tag: Tag) -> bool:
    assert(tag != null)
    return get_active_tags().any(func(active: Tag): return active.equals(tag))


func get_all_abilities() -> Array:
    var all_abilities: Array = [] + _abilities_without_binding

    for binding in _abilities_by_binding.keys():
        all_abilities += _abilities_by_binding[binding]

    return all_abilities
