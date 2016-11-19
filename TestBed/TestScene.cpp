#include "TestScene.h"

using namespace SushiEngine;

TestScene::TestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tTestScene()", __FILENAME__, __LINE__);
}

TestScene::~TestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~TestScene()", __FILENAME__, __LINE__);
}

void TestScene::Initialize(AbstractRenderer* abstractRenderer) {
	Scene::Initialize(abstractRenderer);

	float size = 100;
	float numberOfDivisions = 100;
	float increments = size * 2.0f / numberOfDivisions;
	unsigned int gridNumVerts = numberOfDivisions * 4 + 4;
	vector<vec3> grid;
	vector<vec3> gridColor;
	int c=0;
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

		c+=2;
	}

	cout << c << endl;

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
	
	for (auto i : grid)
	{
		printf("(%f,%f,%f)\n", i.x, i.y, i.z);
	}

	printf("--------------------------------\n");

	for (auto i : gridColor)
	{
		printf("(%f,%f,%f)\n", i.x, i.y, i.z);
	}
	


	SuGameObject* debugPlane = new SuGameObject(vec3(0, 0, 0));

	debugPlane->modelId = ModelManager::LoadModel("debugPlane", &grid[0][0], &gridColor[0][0], gridNumVerts);
	printf("&grid %u\n", &grid);
	printf("&grid[0] %u\n", &grid[0]);
	printf("&grid[0][0] %u\n", &grid[0][0]);


	glBindBuffer(GL_ARRAY_BUFFER, *debugPlane->modelId);

	// SuGameObject* box = new SuGameObject(vec3(0.0f, 0.0f, 0.0f));
	// Transform* t = box->GetComponent<Transform>();

	// box->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	// box->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");

	// glBindBuffer(GL_ARRAY_BUFFER, *box->modelId);
	// glBindTexture(GL_TEXTURE_2D, *box->textureId);

}

void TestScene::Destroy() {

}
