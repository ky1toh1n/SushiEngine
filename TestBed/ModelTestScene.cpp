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

	mGameObjects.push_back(debugPlane);
	//mGameObjects.push_back(orientation);

	// -------------------------------------------------------------------------
	
	sun = new SuGameObject(vec3(0.0f, 0.0f, 0.0f));
	sun->name = "Sun";
	sunTransform = sun->GetComponent<Transform>();
	
	sun->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	sun->textureId = ModelManager::LoadTexture("models/planets/sun.jpg");
	mGameObjects.push_back(sun);

	mercury = new SuGameObject(vec3(3.416f, 0.0f, 0.0f));
	mercuryTransform = mercury->GetComponent<Transform>();
	mercuryTransform->mScale = new vec3(0.035f, 0.035f, 0.035f);
	mercury->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	mercury->textureId = ModelManager::LoadTexture("models/planets/mercury.jpg");
	mGameObjects.push_back(mercury);

	venus = new SuGameObject(vec3(3.7773f, 0.0f, 0.0f));
	venusTransform = venus->GetComponent<Transform>();
	venusTransform->mScale = new vec3(0.086f, 0.086f, 0.086f);
	venus->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	venus->textureId = ModelManager::LoadTexture("models/planets/venus.jpg");
	mGameObjects.push_back(venus);

	earth = new SuGameObject(vec3(4.075f, 0.0f, 0.0f));
	earthTransform = earth->GetComponent<Transform>();
	earthTransform->mScale = new vec3(0.091f, 0.091f, 0.091f);
	earth->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	earth->textureId = ModelManager::LoadTexture("models/planets/earth.jpg");
	mGameObjects.push_back(earth);

	mars = new SuGameObject(vec3(4.1637f, 0.0f, 0.0f));
	marsTransform = mars->GetComponent<Transform>();
	marsTransform->mScale = new vec3(0.048f, 0.048f, 0.048f);
	mars->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	mars->textureId = ModelManager::LoadTexture("models/planets/mars.jpg");
	mGameObjects.push_back(mars);

	jupiter = new SuGameObject(vec3(8.593f, 0.0f, 0.0f));
	jupiterTransform = jupiter->GetComponent<Transform>();
	jupiterTransform->mScale = new vec3(1.0f, 1.0f, 1.0f);
	jupiter->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	jupiter->textureId = ModelManager::LoadTexture("models/planets/jupiter.jpg");
	mGameObjects.push_back(jupiter);

	saturn = new SuGameObject(vec3(13.29f, 0.0f, 0.0f));
	saturnTransform = saturn->GetComponent<Transform>();
	saturnTransform->mScale = new vec3(0.83f, 0.83f, 0.83f);
	saturn->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	saturn->textureId = ModelManager::LoadTexture("models/planets/saturn.jpg");
	mGameObjects.push_back(saturn);

	uranus = new SuGameObject(vec3(23.67f, 0.0f, 0.0f));
	uranusTransform = uranus->GetComponent<Transform>();
	uranusTransform->mScale = new vec3(0.36f, 0.36f, 0.36f);
	uranus->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	uranus->textureId = ModelManager::LoadTexture("models/planets/uranus.jpg");
	mGameObjects.push_back(uranus);

	neptune = new SuGameObject(vec3(35.35f, 0.0f, 0.0f));
	neptuneTransform = neptune->GetComponent<Transform>();
	neptuneTransform->mScale = new vec3(0.53f, 0.35f, 0.35f);
	neptune->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	neptune->textureId = ModelManager::LoadTexture("models/planets/neptune.jpg");
	mGameObjects.push_back(neptune);

	sunTransform->mScale = new vec3(5.0, 5.0, 5.0);

	SuGameObject* space = new SuGameObject(vec3(0.0f, 0.0f, 0.0f));
	Transform* spaceTransform = space->GetComponent<Transform>();
	spaceTransform->mScale = new vec3(100.0, 100.0, 100.0);
	space->modelId = ModelManager::LoadModel("models/planets/planet.obj");
	space->textureId = ModelManager::LoadTexture("models/planets/skybox/space_rt.png");
	mGameObjects.push_back(space);
}

void ModelTestScene::destroy()
{
}


void ModelTestScene::update(float deltaTime)
{
	Scene::update(deltaTime);
	elapsed += deltaTime;
	if (elapsed > 0.25f)
	{
		if (input->isKeyDown(GLFW_KEY_O))
		{
			if (speedMultiplier < 10.0f)
			{
				speedMultiplier += 1.0f;
				elapsed = 0.0f;
			}
		}
		if (input->isKeyDown(GLFW_KEY_P))
		{
			if (speedMultiplier > 1.0f)
			{
				speedMultiplier -= 1.0f;
				elapsed = 0.0f;
			}
		}

		if (input->isKeyDown(GLFW_KEY_SPACE))
		{
			pause = !pause;
			elapsed = 0.0f;
		}
	}

	if (!pause)
	{
		sunTransform->mRotation->y += 0.1f * speedMultiplier * deltaTime;

		mercuryTransform->mRotation->y += 0.4787f * speedMultiplier * deltaTime;

		venusTransform->mRotation->y += 0.3502f * speedMultiplier * deltaTime;
		//venusTransform->mLocalRotation->y += 1.0f * deltaTime;

		earthTransform->mRotation->y += 0.2978f * speedMultiplier * deltaTime;
		//earthTransform->mLocalRotation->y += 1.0f * deltaTime;

		marsTransform->mRotation->y += 0.2407f * speedMultiplier * deltaTime;

		jupiterTransform->mRotation->y += 0.1307f * speedMultiplier * deltaTime;

		saturnTransform->mRotation->y += 0.0969f * speedMultiplier * deltaTime;

		uranusTransform->mRotation->y += 0.0681f * speedMultiplier * deltaTime;

		neptuneTransform->mRotation->y += 0.0543f * speedMultiplier * deltaTime;
	}
}
