#pragma once
#include"Entity.h"

class Aircraft:public Entity
{
public:
	enum Type{Eagle,Raptor};


private:
	Type mType;
	sf::Sprite msprite;

public:
	Aircraft(Type type, const TextureHolder& textures);
		,sf::RenderStates states) const;
};
