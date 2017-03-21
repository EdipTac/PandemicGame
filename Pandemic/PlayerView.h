#pragma once

#include <vector>
#include "Observer.h"
#include "Player.h"



class PlayerView :public Observer
{
public:
	PlayerView(Player* player);

	~PlayerView();

	void update() override;

	Player* theSubject() const;

private:
	Player* _theSubject;


};