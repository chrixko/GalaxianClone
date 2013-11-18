#pragma once

#include "Invaderstate.h"

class IdleState : public InvaderState {
	public:
		IdleState(Invader* parent);
		~IdleState(void);

		void Update(float deltaTime);
};

