#pragma once

class Invader;

class InvaderState {
	public:
		InvaderState(Invader* parent);
		~InvaderState(void);

		Invader* Parent;

		virtual void Init() {};
		virtual void Update(float deltaTime) {};
};

