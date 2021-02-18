#pragma once
#include <string>

using std::string;

// Base for all objects in the engine.
class Entity
{
public:
	string _name;
	Entity();
	~Entity();
};

