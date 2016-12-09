#include "ModelTestScene.h"

ModelTestScene::ModelTestScene()
{
	Debug::LogConstructor("ModelTestScene", __FILENAME__, __LINE__);
}


ModelTestScene::~ModelTestScene()
{
	Debug::LogDeconstructor("ModelTestScene", __FILENAME__, __LINE__);
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
	//glDisableVertexArrayAttrib(*debugPlane->modelId, 1);

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
	//glDisableVertexArrayAttrib(*orientation->modelId, 1);

	// -------------------------------------------------------------------------


	mGameObjects.push_back(debugPlane);
	mGameObjects.push_back(orientation);

	/*Here we build da maze*/
	const int mazeSize = 100;
	const int mazeWidth = 10;
	int maze[mazeSize] 
		= { 
		1,1,1,1,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,1,1,1,0,1,1,1,1,
		1,0,0,0,0,0,0,1,0,1,
		1,0,1,1,1,1,0,1,0,1,
		1,0,1,0,0,0,0,0,0,1,
		1,0,1,0,1,0,1,1,0,1,
		1,1,1,0,1,0,0,1,0,1,
		1,0,0,0,1,1,0,1,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < mazeSize; i++)
	{
		
		//wallz
		if (maze[i] == 1)
		{
			SuGameObject* box3 = new SuGameObject(
				vec3(-4.0f + (i % mazeWidth * 2),
					2.0f,
					4.0f + (i / mazeWidth * 2)));
			Transform* boxt3 = box3->GetComponent<Transform>();
			boxt3->mScale = new vec3(1.0f, 1.0f, 1.0f);
			boxt3->mRotation = new vec3(0.0f, 0.0f, 0.0f);
			box3->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
			box3->textureId = ModelManager::LoadTexture("models/Crate/aliWall.jpg");
			mGameObjects.push_back(box3);
		}

		//floorz
		{
			SuGameObject* box3 = new SuGameObject(
				vec3(-4.0f + (i % mazeWidth * 2),
					0.0f,
					4.0f + (i / mazeWidth * 2)));;
			Transform* boxt3 = box3->GetComponent<Transform>();
			boxt3->mScale = new vec3(1.0f, 1.0f, 1.0f);
			boxt3->mRotation = new vec3(0.0f, 0.0f, 0.0f);
			box3->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
			box3->textureId = ModelManager::LoadTexture("models/Crate/aliFloor.jpg");
			mGameObjects.push_back(box3);
		}

		//ceiling
		{
			SuGameObject* box3 = new SuGameObject(
				vec3(-4.0f + (i % mazeWidth * 2),
					4.0f,
					4.0f + (i / mazeWidth * 2)));;
			Transform* boxt3 = box3->GetComponent<Transform>();
			boxt3->mScale = new vec3(1.0f, 1.0f, 1.0f);
			boxt3->mRotation = new vec3(0.0f, 0.0f, 0.0f);
			box3->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
			box3->textureId = ModelManager::LoadTexture("models/Crate/aliCeiling.jpg");
			mGameObjects.push_back(box3);
		}
	}



}

void ModelTestScene::destroy()
{
}


void ModelTestScene::update(float _deltaTime)
{
	Scene::update(_deltaTime);
}
