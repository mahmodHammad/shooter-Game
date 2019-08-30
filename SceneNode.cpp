#include "SceneNode.h"

SceneNode::SceneNode()
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mchildren.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode & node)
{
	auto found=std::find_if(mchildren.begin() ,mchildren.end() ,
		[&](Ptr & p) ->bool {return p.get() == &node;} //any waY
	);
	assert(found != mchildren.end());

	mchildren.erase(found);

	Ptr result = std::move(*found);
	result->mParent = nullptr;
}


void SceneNode::update(sf::Time dt)
{
	updateChildren(dt);
	updateCurrent(dt);
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	/*operator*= combines the parent's
absolute transform with the current node's relative one. The result is the absolute
transform of the current node, which stores where in the world our scene node
is placed.*/
	states.transform *= getTransform();
	//Now, states.transform contains the absolute world transform.
	drawCurrent(target, states);

	for (const Ptr& child : mchildren)
		child->draw(target,states);
		
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{}
void SceneNode::updateCurrent(sf::Time dt)
{}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : mchildren)
		child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() 
{
	sf::Transform transform = sf::Transform::Identity;
	 for (const SceneNode* node = this;
		 node != nullptr; node = node->mParent)
		 transform = node->getTransform() * transform;
	 return transform;
}

sf::Vector2f SceneNode::getWorldPosition() 
{
	return getWorldTransform() * sf::Vector2f();
}