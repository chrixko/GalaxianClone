#pragma once

#include "Entity.h"
#include "Invader.h"

class InvaderSwarm : public Entity {
    public:
        InvaderSwarm(void);
        ~InvaderSwarm(void);        

        Invader* InvaderFormation[10][6];

        void Init();
        void Update(float deltaTime);
        void Destroy();

        void InitiateAttack();
        void AddInvader(Invader* invader);
        void RemoveInvader(Invader* invader);
    private:
        Invader* getLeftInvader();
        Invader* getRightInvader();     

        Invader* getInvader(InvaderClass invClass, int fromX, int toX);

        bool invadersHitWall();

        InvaderClass randomClass();
        
        Invader* getSubstitudeInvader();
        void collectAllies(Invader* commander);

        float totalTime;
        float attackTimer;
        float attackTime;

        float idleSoundChannel;
};