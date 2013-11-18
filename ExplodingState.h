#pragma once

#include "invaderstate.h"

class ExplodingState : public InvaderState
{
	public:
		ExplodingState(Invader* parent);
		~ExplodingState(void);

		void Init();
		void Update(float deltaTime);
};

