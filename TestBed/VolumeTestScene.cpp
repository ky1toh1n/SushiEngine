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
	go1->AddComponent<Collider>(new BoxCollider(go1, vec3(0,0,0), 1));

	SuGameObject * go2 = new SuGameObject(vec3(0,0,0));
	go2->AddComponent<Collider>(new SphereCollider(go2, vec3(1,0,0),1));

	Collider * c0 = go1->GetComponent<Collider>();
	Collider * c1 = go2->GetComponent<Collider>();
	
	cout << "Box on same box collision: " << c0->overlaps(*c0) << endl;
	cout << "Sphere on same sphere collision: " << c1->overlaps(*c1) << endl;
	cout << "Box on Sphere collision: " << c0->overlaps(*c1) << endl;
}

void VolumeTestScene::Destroy() {

}
