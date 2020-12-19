#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

using std::string;
using std::vector;

struct ObjData
{
	vector<glm::vec4> verts;
	vector<float> verts1D;
	vector<unsigned int> elements;
	//vector<glm::vec2> uv;
};


ObjData ParseOBJModel(const string path)
{
	ObjData data;

	std::ifstream stream(path);

	string line;
	std::stringstream ss[3];

	vector<glm::vec4> verts;
	vector<float> verts1D;
	vector<unsigned int> indices;

	glm::vec4 vert;
	std::string component;

	int whiteSpaces = 0;

	int fIndex = 0;
	int count = 0;

	while (std::getline(stream, line))
	{
		// Get Vertices
		if (line[0] == 'v' && line[1] == ' ')
		{
			whiteSpaces = 0;

			for (auto c : line)
			{
				if (c != 'v')
				{
					if (c != ' ')
					{
						component.append(1, c);
					}

					if (c == ' ' && component.length() > 0)
					{
						if (whiteSpaces == 0)
						{
							vert.x = std::stof(component);
							//verts1D.push_back(vert.x * scale);
						}
						else if (whiteSpaces == 1)
						{
							vert.y = std::stof(component);
							//verts1D.push_back(vert.y * scale);
						}

						component.clear();

						whiteSpaces++;
					}
				}
			}

			vert.z = -(std::stof(component));

			component.clear();

			//vert = pers * vert;
			auto magnitude = glm::sqrt(glm::dot(vert, vert));
			//vert = vert / magnitude;
			vert.w = 1;

			verts1D.push_back(vert.x);
			verts1D.push_back(vert.y);
			verts1D.push_back(vert.z);
			verts1D.push_back(vert.w);

			verts.push_back(vert);
		}

		component.clear();


		//Get indices
		int group = 0;
		int lastindice = 0;

		if (line[0] == 'f' && line[1] == ' ')
		{

			/*if (line.substr(0, 2) == "f ")
			{
				std::istringstream s(line.substr(2));
				unsigned int a, b, c;
				s >> a;
				s >> b;
				s >> c;

				indices.push_back(a -1);
				indices.push_back(b - 1);
				indices.push_back(c - 1);
			}*/
			fIndex = 0;

			for (auto c : line)
			{

				if (c != 'f')
				{
					if (c != ' ' && c != '/')
					{
						component.append(1, c);
					}
					else if (component.length() > 0)
					{
						count++;

						if (fIndex == 0 || fIndex == 3 || fIndex == 6 || fIndex == 9)
							indices.push_back(std::stoi(component) - 1);

						/*if (fIndex == 16)
						{
							std::cout << "yeah ";
						}*/
						//if (count < 60)
						//{
						//	/*if(fIndex == 0 || fIndex == 3 || fIndex == 6 || fIndex == 9)
						//	std::cout << component << "/";*/
						//}
						//if (++group == 3)
						//{
						//	//std::cout << " ";
						//	group = 0;
						//}

						fIndex++;

						component.clear();
					}
				}
				else
				{
					//count++;
					//indices.push_back(lastindice);

					//std::cout << std::endl;
				}
			}



			//fIndex = 0;
			//std::cout << component << std::endl;
		}
	}

	return { verts,  verts1D, indices };
}