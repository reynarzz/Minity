#pragma once
#include <vector>
#include <glm/glm.hpp>

using std::vector;
using glm::vec4;

class Mesh
{
private:
	unsigned int _stride;

	vector<float>* _vertices;
	vector<unsigned int>* _indices;
	//vector<glm::vec2> _uv;
	//vector<glm::vec3> _normals;
public:
	Mesh(vector<float>* vertices, vector<unsigned int>* indices);
	~Mesh();

	void SetVertices(vector<float>* vertices);
	void SetIndices(vector<unsigned int>* indices);

	vector<float>* GetVertices() const;
	vector<unsigned int>* GetIndices() const;
};