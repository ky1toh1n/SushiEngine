//#include "Transform.h"
//
//namespace SushiEngine
//{
//	Transform::Transform(const SuGameObject * _gameObject) : Component(_gameObject)
//	{
//		position = new vec3(0.0f, 0.0f, 0.0f);
//		rotation = new quat(0.0f, 0.0f, 0.0f, 0.0f);
//		scale = new vec3(1.0f, 1.0f, 1.0f);
//	}
//
//	Transform::Transform(const SuGameObject * _gameObject, vec3 _pos) : Component(_gameObject)
//	{
//		position = &_pos;
//		rotation = new quat(0.0f, 0.0f, 0.0f, 0.0f);
//		scale = new vec3(1.0f, 1.0f, 1.0f);
//	}
//
//	Transform::Transform(const SuGameObject * _gameObject, vec3 _pos, quat _rot) : Component(_gameObject)
//	{
//		position = &_pos;
//		rotation = &_rot;
//		scale = new vec3(1.0f, 1.0f, 1.0f);
//	}
//
//	Transform::Transform(const SuGameObject * _gameObject, vec3 _pos, quat _rot, vec3 _scale) : Component(_gameObject)
//	{
//		position = &_pos;
//		rotation = &_rot;
//		scale = &_scale;
//	}
//
//
//	Transform::~Transform()
//	{
//		delete position;
//		position = nullptr;
//		delete rotation;
//		rotation = nullptr;
//		delete scale;
//		scale = nullptr;
//	}
//}