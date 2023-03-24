#pragma once
#include <unordered_map>

#include "ObjectBase.h"
#include "ObjectTag.h"
#include "Math.h"

class ObjectManager final
{
public:
	static void Initialize();

	static void Entry(ObjectBase* newObj);
	static void Relese(ObjectBase* releseObj);
	static void ReleseAllObj();

	static void Update(float deltaTime);
	static void Draw();

	static void Collition();

	static ObjectBase* GetFirstObject(ObjectTag tag);
	static void Finalize();

private:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* Instance;
	std::vector<ObjectBase*> pendingObjects;
	std::unordered_map<ObjectTag, std::vector<ObjectBase*>> objects;
};

