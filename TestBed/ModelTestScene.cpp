#include "ModelTestScene.h"

ModelTestScene::ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tModelTestScene()", __FILENAME__, __LINE__);
}


ModelTestScene::~ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~ModelTestScene()", __FILENAME__, __LINE__);
}

void ModelTestScene::initialize(SceneContext* pSceneContext)
{
	Scene::initialize(pSceneContext);

	//SuGameObject* go;
	//MeshRenderer* houseMesh;
	//// ModelImporter Tests
	//go = new SuGameObject(glm::vec3(0, 0, 0));
	//if (!go) cout << "Failed to create GameObject" << endl;
	//
	//houseMesh = new MeshRenderer(go, "models/house/house.3ds");

	//// this break it for some reason
	//go->AddComponent<MeshRenderer>(houseMesh);

	float size = 100;
	float numberOfDivisions = 100;
	float increments = size * 2.0f / numberOfDivisions;
	unsigned int gridNumVerts = numberOfDivisions * 4 + 4;
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
		gridColor.push_back(vec3(1, 0, 0));
		gridColor.push_back(vec3(1, 0, 0));
	}

	// Points for the vertical lines
	for (float x = -size; x < size; x += increments)
	{
		// line from
		vec3 pointA = vec3(x, 0, -size);
		// to
		vec3 pointB = vec3(x, 0, size);

		grid.push_back(pointA);
		grid.push_back(pointB);
		gridColor.push_back(vec3(1, 0, 0));
		gridColor.push_back(vec3(1, 0, 0));
	}

	SuGameObject* debugPlane = new SuGameObject(vec3(0, 0, 0));

	debugPlane->modelId = ModelManager::LoadModel("debugPlane", &grid[0][0], &gridColor[0][0], gridNumVerts);
	//glDisableVertexArrayAttrib(*debugPlane->modelId, 1);

	SuGameObject* box = new SuGameObject(vec3(0.0f, 0.0f, 0.0f));
	// Transform* t = box->GetComponent<Transform>();


	box->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	//glDisableVertexArrayAttrib(*box->modelId, 2);
	box->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");


	SuGameObject* house = new SuGameObject(vec3(0, 0, 0));
	house->modelId = ModelManager::LoadModel("models/house/house.obj");
	//glDisableVertexArrayAttrib(*house->modelId, 2);
	house->textureId = ModelManager::LoadTexture("models/house/house2.png");

	mGameObjects.push_back(debugPlane);
	mGameObjects.push_back(box);
	mGameObjects.push_back(house);

}

void ModelTestScene::destroy()
{
}
