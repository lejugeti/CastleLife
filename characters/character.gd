class_name Character
extends CharacterBody2D

var ability_container: AbilityContainer = AbilityContainer.new()
var sprites: AnimatedSprite2D

var movement_blocked: bool = false

signal up_key_pressed


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
    pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass
