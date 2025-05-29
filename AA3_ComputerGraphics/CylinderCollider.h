#pragma once
#include "Collider.h"

class CylinderCollider : public Collider
{
private:
	float radius;

public:
	CylinderCollider(Vector3 initialPos, float radiusToSet)
		: Collider(pos), radius(radiusToSet)
	{

	}

	bool CollidesWith(Collider* other)
	{
		if (CylinderCollider* otherCyl = dynamic_cast<CylinderCollider*>(other))
		{
			Vector3 distanceVector = pos - other->GetPos();
			distanceVector.y = 0;

			float distance = distanceVector.length();
			float sumOfRadii = radius + otherCyl->GetRadius();

			if (distance >= sumOfRadii)
				return false;

			float intersectionDepth = sumOfRadii - distance;
			Vector3 pushDirection = distanceVector.Normalized();

			Vector3 newPos = pos + pushDirection * intersectionDepth;
			pos = newPos;

			return true;
		}
		
	}

	float GetRadius()
	{
		return radius * scale;
	}
};