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
		std::cout << "Player pos: (" << pos.x << ", " << pos.y << ", " << pos.z << ")";
		std::cout << "Other pos: (" << other->GetPos().x << ", " << other->GetPos().y << ", " << other->GetPos().z << ")" << std::endl;

		Vector3 distanceVector = pos - other->GetPos();
		distanceVector.y = 0;

		float distance = distanceVector.length();
		float sumOfRadii = radius + other->GetRadius();

		std::cout << "Distance: " << distance << " | Radii: " << sumOfRadii << std::endl;
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