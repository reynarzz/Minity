#pragma once
#include <vector>
#include <glm/glm.hpp>

using std::vector;
using glm::vec4;

class Mesh
{
private:
	vector<float>* _vertices;
	vector<unsigned int>* _indices;
	//vector<glm::vec2> _uv;
public:
	
	Mesh(vector<float>* vertices, vector<unsigned int>* indices);
	~Mesh();

	void SetVertices(vector<float>* vertices);
	void SetIndices(vector<unsigned int>* indices);

	vector<float>* GetVertices() const;
	vector<unsigned int>* GetIndices() const;
};
