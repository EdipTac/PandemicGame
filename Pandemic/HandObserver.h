#pragma once

#include "Player.h"
#include "PolyObserver.h"

class HandObserver :
	public PolyObserver<Player>
{
public:
	virtual ~HandObserver() override;
	virtual void update() override;
};

