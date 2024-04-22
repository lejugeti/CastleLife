class_name Tag
extends Node


var tag_name: String:
    get:
        return tag_name
    set(value):
        self.assert_tag_is_valid(value)
        tag_name = value


static var TAG_PATTERN: String = "^([\\w]+\\.?)+$"


func _init(tag_name):
    self.tag_name = tag_name


func assert_tag_is_valid(tag_value: String):
    var tag_regex: RegEx = RegEx.new()
    tag_regex.compile(TAG_PATTERN)
    assert(tag_regex.search(tag_value) != null)


func equals(other: Tag):
    return self.tag_name == other.tag_name
