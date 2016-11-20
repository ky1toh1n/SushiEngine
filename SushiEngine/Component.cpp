#include "Component.h"

namespace SushiEngine
{
	Component::Component(const SuGameObject * pGameObject)
	{
		mGameObject = pGameObject;
	}

	Component::~Component()
	{
		mGameObject = nullptr;
	}
}