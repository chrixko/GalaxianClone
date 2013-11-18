#pragma once

#include "InvaderState.h"

class FollowCommanderState : public InvaderState {
    public:
        FollowCommanderState(Invader* parent);
        ~FollowCommanderState(void);

        Invader* Commander;

        float positionOffsetX;
        float positionOffsetY;

        void Init();
        void Update(float deltaTime);
};

