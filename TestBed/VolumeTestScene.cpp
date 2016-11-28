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

void VolumeTestScene::initialize(SceneContext* pSceneContext)
{
	Scene::initialize(pSceneContext);
	
	/* ------------------ Initialize all the Colliders !! -------------- */
	//Boxes first
	SuGameObject * box1 = new SuGameObject(vec3(0,0,0));
	box1->AddComponent<Collider>(new BoxCollider(box1, vec3(0,0,0), 2));
	SuGameObject * box2 = new SuGameObject(vec3(0,0,0));
	box2->AddComponent<Collider>(new BoxCollider(box2, vec3(0,2,0), 2));
	SuGameObject * box3 = new SuGameObject(vec3(0,0,0));
	box3->AddComponent<Collider>(new BoxCollider(box3, vec3(0,4,0), 2));
	
	Collider * cb1 = box1->GetComponent<Collider>();
	Collider * cb2 = box2->GetComponent<Collider>();
	Collider * cb3 = box3->GetComponent<Collider>();

	//Then spheres!! <3 <3
	SuGameObject * sp1 = new SuGameObject(vec3(0, 0, 0));
	sp1->AddComponent<Collider>(new SphereCollider(sp1, vec3(0, 0, 0), 1));
	SuGameObject * sp2 = new SuGameObject(vec3(0, 0, 0));
	sp2->AddComponent<Collider>(new SphereCollider(sp2, vec3(0, 2, 0), 1));
	SuGameObject * sp3 = new SuGameObject(vec3(0, 0, 0));
	sp3->AddComponent<Collider>(new SphereCollider(sp3, vec3(0, 4, 0), 1));

	Collider * cs1 = sp1->GetComponent<Collider>();
	Collider * cs2 = sp2->GetComponent<Collider>();
	Collider * cs3 = sp3->GetComponent<Collider>();
	/* ------------------ The True Tests Begin!! --------------- */

	// Box vs box
	cout << "Same Object\n\tBox 1 vs Box 1: " << cb1->overlaps(*cb1) << endl;
	cout << "Just Touching\n\tBox 1 vs Box 2: " << cb1->overlaps(*cb2) << endl;
	cout << "No Collision\n\tBox 1 vs Box 3: " << cb1->overlaps(*cb3) << endl;

	// Sphere vs Sphere
	cout << "\nSame Object\n\tSphere 1 vs Sphere 1: " << cs1->overlaps(*cs1) << endl;
	cout << "Just Touching\n\tSphere 1 vs Sphere 2: " << cs1->overlaps(*cs2) << endl;
	cout << "No Collision\n\tSphere 1 vs Sphere 3: " << cs1->overlaps(*cs3) << endl;

	// Box vs Sphere
	cout << "\nSame Origin\n\tBox 1 vs Sphere 1: " << cb1->overlaps(*cs1) << endl; 
	cout << "\tSphere 1 vs Box 1: " << cs1->overlaps(*cb1) << endl; 
	cout << "Just Touching\n\tBox 1 vs Sphere 2: " << cb1->overlaps(*cs2) << endl; 
	cout << "\tSphere 2 vs Box 1: " << cs2->overlaps(*cb1) << endl; 
	cout << "No Collision\n\tBox 1 vs Sphere 3: " << cb1->overlaps(*cs3) << endl; 
	cout << "\tSphere 3 vs Box 1: " << cs3->overlaps(*cb1) << endl; 
}

void VolumeTestScene::destroy() {

}
