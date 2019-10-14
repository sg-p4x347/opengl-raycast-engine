#include "pch.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(Vector3 position, float radius, string texture) : Sprite::Sprite(position, radius, texture)
{
}
