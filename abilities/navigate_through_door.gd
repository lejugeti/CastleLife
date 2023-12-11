class_name NavigateThroughDoor
extends Ability

const STANDING_ANIMATION: String = "standing"
const DOOR_IN_ANIMATION: String = "door_in"
const DOOR_OUT_ANIMATION: String = "door_out"

## Character traveling through the door
var _character: Character
## Door in which the character will enter
var _door_to_use: Door

var executing: bool = false

signal door_in_animation_finished
signal door_out_animation_finished


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
    pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass


func _init(character: Character, door: Door):
    _character = character
    _door_to_use = door

    _character.up_key_pressed.connect(execute)
    _door_to_use.character_quitted_door.connect(_on_door_character_quitted_door)


func execute():
    if(!executing):
        executing = true
        _character.movement_blocked = true
        _character.sprites.animation_finished.connect(_on_sprites_animation_finished)
        _character.sprites.play(DOOR_IN_ANIMATION)


func _on_sprites_animation_finished():
    var animation_finished: String = _character.sprites.animation
    if(animation_finished == DOOR_IN_ANIMATION):
        var travel_position: Vector2 = Vector2(_door_to_use.get_door_destination().get_position())
        _character.set_position(travel_position)
        _character.sprites.play(DOOR_OUT_ANIMATION)
    elif(animation_finished == DOOR_OUT_ANIMATION):
        _character.sprites.animation_finished.disconnect(_on_sprites_animation_finished)
        _character.sprites.play(STANDING_ANIMATION)
        _character.movement_blocked = false


## Used when character leaves the door in order to disconnect all signals and remove
## the ability from character
func _on_door_character_quitted_door(character_leaving: Character):
    if(_character == character_leaving):
        _character.up_key_pressed.disconnect(execute)
        _door_to_use.character_quitted_door.disconnect(_on_door_character_quitted_door)
        _character.ability_container.remove_ability(self)

