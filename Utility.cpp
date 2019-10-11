#include "pch.h"
#include "Utility.h"

bool GetLineIntersection(Vector2 startA, Vector2 dirA, Vector2 startB, Vector2 dirB, float& tA, float& tB)
{
	if (dirA.Dot(dirB.Right()) != 0.f) {
		tA = (dirB.X * (startA.Y - startB.Y) + dirB.Y * (startB.X - startA.X)) / (dirA.X * dirB.Y - dirA.Y * dirB.X);
		tB = (dirA.X * (startB.Y - startA.Y) + dirA.Y * (startA.X - startB.X)) / (dirB.X * dirA.Y - dirB.Y * dirA.X);
		return true;
	}
	return false;
}

Vector2 GetVectorToSegment(Vector2 start, Vector2 end, Vector2 point)
{

	Vector2 segmentDir = end - start;
	float projection = segmentDir.Normalized().Dot(point - start);
	if (projection <= 0) {
		return point - start;
	}
	else if (projection >= segmentDir.Length()) {
		return point - end;
	}
	else {
		Vector2 segmentNormal = segmentDir.Right().Normalized();
		return segmentNormal * segmentNormal.Dot(point - start);
	}

}