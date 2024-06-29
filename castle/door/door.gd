class_name Door
extends Area2D


@export var door_destination: Door


## Abilities given by the door to travelers
## Key : Character, Value : Ability
var navigation_abilities: Dictionary = {}

# Called when the node enters the scene tree for the first time.
func _ready():
    $Sprites.play("default")

    body_entered.connect(_on_character_start_overlapping)
    body_exited.connect(_on_character_stop_overlapping)


func _on_character_start_overlapping(body: Node2D):
    if(body is Character):
        var door_initially_not_overlapped: bool = get_bodies_overlapping() == 0

        if(door_initially_not_overlapped):
            $Sprites.play("opening")

        var character : Character = body as Character
        var enter_door_ability: NavigateThroughDoor = NavigateThroughDoor.new(character, self)
        character.ability_component.add_ability(enter_door_ability)

        navigation_abilities[character] = enter_door_ability


func _on_character_stop_overlapping(body: Node2D):
    if(body is Character):
        var character_leaving: Character = body as Character
        var ability_to_remove: Ability = navigation_abilities.get(character_leaving)
        navigation_abilities.erase(character_leaving)
        character_leaving.ability_component.wait_and_remove_ability(ability_to_remove)

        if(get_bodies_overlapping() == 0):
            $Sprites.play_backwards("opening")


func get_bodies_overlapping():
    return self.navigation_abilities.size()
