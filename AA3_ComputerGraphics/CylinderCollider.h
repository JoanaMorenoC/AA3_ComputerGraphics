#pragma once
#include "Vector3.h"

class CylinderCollider
{
private:
	Vector3 pos;
	float scale;
	float radius;

public:
	CylinderCollider(Vector3 initialPos, float radiusToSet)
		: pos(initialPos), radius(radiusToSet)
	{

	}

	bool CollidesWith(CylinderCollider* other)
	{
		Vector3 distanceVector = pos - other->GetPos();
		distanceVector.y = 0;

		float distance = distanceVector.length();
		float sumOfRadii = radius + other->GetRadius();

		if (distance >= sumOfRadii)
			return false;

		float intersectionDepth = sumOfRadii - distance;
		Vector3 pushDirection = distanceVector.Normalized();

		Vector3 newPos = pos + pushDirection * intersectionDepth;
		pos = newPos;

		return true;
	}

	float GetRadius()
	{
		return radius * scale;
	}

	Vector3 GetPos()
	{
		return pos;
	}

	void SetScale(float newScale)
	{
		scale = newScale;
	}

	void SetPos(Vector3 newPos)
	{
		pos = newPos;
	}
};