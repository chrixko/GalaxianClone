#pragma once

#include "entity.h"
#include "InvaderState.h"

enum InvaderClass {
    INVADER_BLUE = 0,
    INVADER_PURPLE = 1,
    INVADER_RED = 2,
    INVADER_COMMANDER = 3
};

class Invader : public Entity {
    public:
        Invader(InvaderClass invaderClass);
        ~Invader(void);

        InvaderClass Class;

		Animation* IdleAnimation;
		Animation* ExplodeAnimation;

        int FlySoundChannel;

		InvaderState* Idle;
		InvaderState* Explode;
		InvaderState* Arc;
		InvaderState* Attack;
        InvaderState* GoHome;
        InvaderState* FollowCommander;

		InvaderState* CurrentState;

		int SwarmX;
		int SwarmY;

		void SwitchState(InvaderState* state) { state->Init(); CurrentState = state; }

		void Init();
        void Update(float deltaTime);
        void Destroy();

        void RestrainPosition();

        void Fire(float targetX, float targetY);
        void ScorePoints();
};