class_name Door
extends Area2D


@export_node_path("Door") var door_destination_ref: NodePath

var bodies_overlapping: Array[Character] = []

signal character_quitted_door(character: Character)

# Called when the node enters the scene tree for the first time.
func _ready():
    $Sprites.play("default")

    body_entered.connect(_on_character_start_overlapping)
    body_exited.connect(_on_character_stop_overlapping)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
    pass


func _on_character_start_overlapping(body: Node2D):
    if(body is Character):
        var door_initially_not_overlapped: bool = bodies_overlapping.size() == 0
        bodies_overlapping.append(body)

        if(door_initially_not_overlapped):
            $Sprites.play("opening")

        var character : Character = body as Character
        var enter_ability: NavigateThroughDoor = NavigateThroughDoor.new(character, self)
        character.ability_container.add_ability(enter_ability)


func _on_character_stop_overlapping(body: Node2D):
    if(body is Character):
        var character: Character = body as Character
        bodies_overlapping.erase(character)
        character_quitted_door.emit(character)

        if(bodies_overlapping.size() == 0):
            $Sprites.play_backwards("opening")


func get_door_destination() -> Door:
    var destination: Door = get_node(door_destination_ref)
    assert(destination != null)
    return destination
