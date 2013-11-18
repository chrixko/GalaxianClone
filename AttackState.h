#pragma once

#include "InvaderState.h"

class AttackState :	public InvaderState {
	public:
		AttackState(Invader* parent);
		~AttackState(void);

        float TargetX;
        float TargetY;

        float VelocityX;
        float VelocityY;        

		void Init();
		void Update(float deltaTime);

        bool Shooting;
    private:
        float shootTimer;
        float shootTime;
        float shootCount;
};