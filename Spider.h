#pragma once
#include "pch.h"
#include "Agent.h"
class Spider : public Agent
{
public:
	Spider(Vector3 position);
	virtual void Update(double& elapsed, World* world) override;
	float SpideySenseRange;
};

