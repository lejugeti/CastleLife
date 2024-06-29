class_name Character
extends CharacterBody2D

var ability_component: AbilityComponent = AbilityComponent.new()
var sprites: AnimatedSprite2D

var movement_blocked: bool = false

signal interact_btn_pressed

