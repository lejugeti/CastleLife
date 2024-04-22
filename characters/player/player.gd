class_name Player
extends Character


@export var speed: int = 200
@export var gravity: int = 200


# Called when the node enters the scene tree for the first time.
func _ready():
    sprites = $Sprites
    sprites.play()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
    var move_up: bool = Input.is_action_just_pressed("move_up")
    if move_up:
        up_key_pressed.emit()



func _physics_process(delta):
    var move_left: bool = Input.is_action_pressed("move_left")
    var move_right: bool = Input.is_action_pressed("move_right")

    velocity.x = 0
    velocity.y += gravity * delta

    if(!movement_blocked):
        if move_left:
            velocity.x = -speed
            $Sprites.play("running")
            if(!$Sprites.flip_h):
                $Sprites.flip_h = true
                $Sprites.offset.x *= -1

        if move_right:
            velocity.x = speed;
            $Sprites.play("running")
            if($Sprites.flip_h):
                $Sprites.flip_h = false
                $Sprites.offset.x *= -1

    if not move_left && not move_right && $Sprites.animation == "running":
        $Sprites.play("standing")


    move_and_slide()

