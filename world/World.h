#pragma once

class Visualisation;

class World
{
private:
	Visualisation *vis{ nullptr };

public:
	World();
	~World();
	
	void Run();
	bool LoadLevel();
	void Update();
};

