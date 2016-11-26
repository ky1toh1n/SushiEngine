#include "VolumeTestScene.h"

using namespace SushiEngine;

VolumeTestScene::VolumeTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tVolumeTestScene()", __FILENAME__, __LINE__);
}

VolumeTestScene::~VolumeTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~VolumeTestScene()", __FILENAME__, __LINE__);
}

void VolumeTestScene::Initialize(AbstractRenderer* abstractRenderer) {
	Scene::Initialize(abstractRenderer);
	
	SuGameObject * go1 = new SuGameObject(vec3(0,0,0));
	go1->AddComponent<Collider>(new Box(go1));

	SuGameObject * go2 = new SuGameObject(vec3(0,0,0));
	go2->AddComponent<Collider>(new Sphere(go2));

	Collider * c0 = go1->GetComponent<Collider>();
	Collider * c1 = go2->GetComponent<Collider>();

	c0->overlaps(*c0);
	c0->overlaps(*c1);
	c1->overlaps(*c0);
	c1->overlaps(*c1);

}

void VolumeTestScene::Destroy() {

}
