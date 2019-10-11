#pragma once
#include "pch.h"
#include "Vector2.h"
bool GetLineIntersection(Vector2 startA, Vector2 dirA, Vector2 startB, Vector2 dirB, float& tA, float& tB);
Vector2 GetVectorToSegment(Vector2 start, Vector2 end, Vector2 point);