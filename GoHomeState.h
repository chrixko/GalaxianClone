#pragma once

#include "InvaderState.h"

class GoHomeState : public InvaderState {
    public:
        GoHomeState(Invader* parent);
        ~GoHomeState(void);

        void Init();
        void Update(float deltaTime);
};

