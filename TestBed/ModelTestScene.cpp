#include "ModelTestScene.h"

ModelTestScene::ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tModelTestScene()", __FILENAME__, __LINE__);
}


ModelTestScene::~ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~ModelTestScene()", __FILENAME__, __LINE__);
}

void ModelTestScene::Initialize(AbstractRenderer * abstractRenderer)
{
	Scene::Initialize(abstractRenderer);

	//SuGameObject* go;
	//MeshRenderer* houseMesh;
	//// ModelImporter Tests
	//go = new SuGameObject(glm::vec3(0, 0, 0));
	//if (!go) cout << "Failed to create GameObject" << endl;
	//
	//houseMesh = new MeshRenderer(go, "models/house/house.3ds");

	//// this break it for some reason
	//go->AddComponent<MeshRenderer>(houseMesh);

	float size = 20;
	float numberOfDivisions = 20;
	float increments = size * 2.0f / numberOfDivisions;
	unsigned int gridNumVerts = int(numberOfDivisions * 4 + 4);
	vector<vec3> grid;
	vector<vec3> gridColor;
	int c = 0;
	// Points for the horizontal lines
	for (float y = -size; y <= size; y += increments)
	{
		// line from
		vec3 pointA = vec3(-size, 0, y);
		// to
		vec3 pointB = vec3(size, 0, y);

		//cout << pointA.x << " " << pointA.y << " " << pointA.z << endl;
		// cout << pointB.x << " " << pointB.y << " " << pointB.z << endl;

		grid.push_back(pointA);
		grid.push_back(pointB);
		gridColor.push_back(vec3(0.2, 0.2, 0.25));
		gridColor.push_back(vec3(0.2, 0.2, 0.25));
	}

	// Points for the vertical lines
	for (float x = -size; x <= size; x += increments)
	{
		// line from
		vec3 pointA = vec3(x, 0, -size);
		// to
		vec3 pointB = vec3(x, 0, size);

		grid.push_back(pointA);
		grid.push_back(pointB);
		gridColor.push_back(vec3(0.2, 0.2, 0.25));
		gridColor.push_back(vec3(0.2, 0.2, 0.25));
	}

	SuGameObject* debugPlane = new SuGameObject(vec3(0, 0, 0));

	debugPlane->modelId = ModelManager::LoadModel("debugPlane", &grid[0][0], &gridColor[0][0], gridNumVerts);
	glDisableVertexArrayAttrib(*debugPlane->modelId, 1);

	vector<vec3> helper;
	vector<vec3> helpercolor;

	// +x
	helper.push_back(vec3(0, 0, 0));
	helper.push_back(vec3(1, 0, 0));
	helpercolor.push_back(vec3(1, 0, 0));
	helpercolor.push_back(vec3(1, 0, 0));

	// +y
	helper.push_back(vec3(0, 0, 0));
	helper.push_back(vec3(0, 1, 0));
	helpercolor.push_back(vec3(0, 1, 0));
	helpercolor.push_back(vec3(0, 1, 0));

	// +z
	helper.push_back(vec3(0, 0, 0));
	helper.push_back(vec3(0, 0, 1));
	helpercolor.push_back(vec3(0, 0, 1));
	helpercolor.push_back(vec3(0, 0, 1));

	SuGameObject* orientation = new SuGameObject(vec3(0, 1, 5));
	orientation->modelId = ModelManager::LoadModel("orientation", &helper[0][0], &helpercolor[0][0], 6);
	glDisableVertexArrayAttrib(*orientation->modelId, 1);

	// -------------------------------------------------------------------------

	//SuGameObject* terrain = new SuGameObject(vec3(0, 0, 0));
	//terrain->modelId = ModelManager::LoadModel("models/SnowTerrain/SnowTerrain.obj");
	// glDisableVertexArrayAttrib(*terrain->modelId, 2);
	//terrain->textureId = ModelManager::LoadTexture("models/SnowTerrain/resnow.png");

	SuGameObject* box = new SuGameObject(vec3(-2.3f, 1.0f, 2.0f));
	Transform* boxt = box->GetComponent<Transform>();
	boxt->mRotation = new vec3(0.0f, 0.0f, 0.0f);

	box->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	glDisableVertexArrayAttrib(*box->modelId, 2);
	// box->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");
	box->textureId = ModelManager::LoadTexture("models/Crate/crate_1.jpg");


	SuGameObject* box2 = new SuGameObject(vec3(7.0f, 1.0f, 3.0f));
	Transform* boxt2 = box2->GetComponent<Transform>();
	boxt2->mRotation = new vec3(0.0f, 90.0f, 0.0f);

	box2->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	glDisableVertexArrayAttrib(*box2->modelId, 2);
	box2->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate_flipped.png");

	SuGameObject* box3 = new SuGameObject(vec3(-4.0f, 1.0f, 4.0f));
	Transform* boxt3 = box3->GetComponent<Transform>();
	boxt3->mRotation = new vec3(0.0f, 45.0f, 0.0f);

	box3->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	glDisableVertexArrayAttrib(*box2->modelId, 3);
	box3->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");

	SuGameObject* house = new SuGameObject(vec3(2, 0, 0));
	house->modelId = ModelManager::LoadModel("models/house/house.obj");
	glDisableVertexArrayAttrib(*house->modelId, 2);
	house->textureId = ModelManager::LoadTexture("models/house/house2.png");

	gameObjects.push_back(debugPlane);
	gameObjects.push_back(orientation);
	// gameObjects.push_back(terrain);
	gameObjects.push_back(box);
	gameObjects.push_back(box2);
	gameObjects.push_back(box3);
	gameObjects.push_back(house);

}

void ModelTestScene::Destroy()
{
}


void ModelTestScene::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
	float rotValue = 1.0f;
	Transform* t = gameObjects[4]->GetComponent<Transform>();
	t->mRotation = new vec3(t->mRotation->x, t->mRotation->y + rotValue * _deltaTime, t->mRotation->z);
}
