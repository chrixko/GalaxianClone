#pragma once

#include <vector>

#include "Star.h"
#include "Entity.h"

class StarField : public Entity {
	public:
		StarField(void);
		~StarField(void);
		
		std::vector<Star*> Stars;

		void Init();
		void Update(float deltaTime);
		void Destroy();
};

