class_name DummyAbility
extends Ability

static var NAME: String = "Dummy"


func _init():
    self.ability_name = NAME;
    self.tag = Tag.new("Dummy")

    super.assert_valid_ability()


func execute():
    print("Dummy ability activated")
