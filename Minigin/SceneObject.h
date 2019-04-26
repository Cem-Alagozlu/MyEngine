#pragma once
class SceneObject
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() const = 0;

		SceneObject() = default;
		virtual ~SceneObject(){}
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};