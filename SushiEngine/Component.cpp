#include "Component.h"

namespace SushiEngine
{
	Component::Component(SuGameObject * _gameObject)
	{
		mGameObject = _gameObject;
	}

	Component::~Component()
	{
		delete mGameObject;
	}
}