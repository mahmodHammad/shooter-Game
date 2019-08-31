#pragma once
#include<SFML\Graphics.hpp>
#include<memory>
#include<map>
#include<assert.h>
#include<iostream>
namespace Textures { enum ID { Eagle, Raptor, Desert }; };


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id,const std::string& filename);

	template<typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter &secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
private:
	std::map<Identifier,std::unique_ptr<Resource>> mResourceMap;
};

#include"ResourceHandler.inl"
//a7aaa  what the hell <<i wanted my  templete at first to be defined before creation LOL !>>
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

