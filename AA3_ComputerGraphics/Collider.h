#pragma once
#include "Vector3.h"

class Collider
{
protected:
	Vector3 pos;
	float scale;

public:
	Collider(Vector3 initialPos)
	{
		pos = initialPos;
	}

	virtual ~Collider() {}

	Vector3 GetPos()
	{
		return pos;
	}

	void SetPos(Vector3 newPos)
	{
		pos = newPos;
	}

	void SetScale(float newScale)
	{
		scale = newScale;
	}
};