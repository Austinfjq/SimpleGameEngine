#ifndef SIMPLE_GAMELOGIC_H
#define SIMPLE_GAMELOGIC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ShaderProgram/Shader.h>
#include <Model/Model.h>
#include <Model/Mesh.h>
#include <Camera/ThirdPersonCamera.h>

// Abstract class GameLogic
// You may create your own game logic by overriding the virtual functions and add some COOL things!
// If you want to have MORE THAN ONE logics in your game, it is suggested to create main game logic, and let this main logic
//  to control different logics.
class GameLogic
{
public:

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	virtual void ProcessInput(GLFWwindow* window, float deltaTime) = 0;
	virtual void MouseCallback(GLFWwindow* window, double xPos, double yPos) = 0;
	virtual void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) = 0;
	virtual void DrawFrame(void) = 0;
};


// This is an example logic so I decide to put it here.
class MainGameLogic :public GameLogic 
{
public:
	MainGameLogic();	// Set all things you need,
	~MainGameLogic();	// and free them when the game ends

	void ProcessInput(GLFWwindow* window, float deltaTime);
	void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void DrawFrame(void);
private:
	// Shader(s)
	LightShader *ourShader;

	// Camera(s)
	ThirdPersonCamera *camera;
	//Camera *camera;
	
	// Model(s)
	Model *ourModel;
	unsigned int diffuseMap;
	unsigned int specularMap;
	Mesh* rectangle;
	Model* recModel;

	// some settings
	bool disableCursor = false;
	bool firstMouse = true;
};



#endif 
