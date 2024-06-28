class_name NavigateThroughDoor
extends Ability

static var NAME: String = "navigate_through_door"
static var TAG: Tag = Tag.new("Navigation.Door")

const STANDING_ANIMATION: String = "standing"
const DOOR_IN_ANIMATION: String = "door_in"
const DOOR_OUT_ANIMATION: String = "door_out"

## Character traveling through the door
var _character: Character
## Door in which the character will enter
var _door_to_use: Door

signal door_in_animation_finished
signal door_out_animation_finished


func _init(character: Character, door: Door):
    self.ability_name = NAME;
    self.tag = TAG

    super.assert_valid_ability()
    _character = character
    _door_to_use = door


func execute():
    _character.movement_blocked = true
    _character.sprites.animation_finished.connect(_on_sprites_animation_finished)
    _character.sprites.play(DOOR_IN_ANIMATION)


func _on_sprites_animation_finished():
    var animation_finished: String = _character.sprites.animation
    if(animation_finished == DOOR_IN_ANIMATION):
        var travel_position: Vector2 = Vector2(_door_to_use.door_destination.get_position())
        _character.set_position(travel_position)
        _character.sprites.play(DOOR_OUT_ANIMATION)
    elif(animation_finished == DOOR_OUT_ANIMATION):
        _character.sprites.animation_finished.disconnect(_on_sprites_animation_finished)
        _character.sprites.play(STANDING_ANIMATION)
        _character.movement_blocked = false

        self.is_active = false
        finished.emit(self)
