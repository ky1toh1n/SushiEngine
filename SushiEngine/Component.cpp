#include "Component.h"

namespace SushiEngine
{
	Component::Component(const SuGameObject * fGameObject)
	{
		mGameObject = fGameObject;
	}

	Component::~Component()
	{
		delete mGameObject;
	}
}