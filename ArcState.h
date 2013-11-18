#pragma once

#include "Invaderstate.h"

class ArcState : public InvaderState {
	public:
		ArcState(Invader* parent, int direction);
		~ArcState(void);

		int Direction;

		void Init();
		void Update(float deltaTime);
	private:
		int pivotX;
		int pivotY;
		
		float angle;		
		int stepCount;
		float anglePerStep;
		float radius;
};

