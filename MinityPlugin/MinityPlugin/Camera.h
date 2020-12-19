#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec2;

class Camera
{
private:
	mat4 _viewMatrix;
	vec3 _cameraPos;
	vec2 _cameraRot;
	mat4 _projectionMatrix;

public:

	Camera(vec3 position, vec2 rotation, float aspectRatio);
	~Camera();

	/// <summary>Called when the screen size changes.</summary>
	void OnScreenSizeChanged();
	const mat4& GetViewMatrix(vec3 cameraPos, vec2 mouseDelta);
	const mat4& GetProjectionMatrix() const;
};