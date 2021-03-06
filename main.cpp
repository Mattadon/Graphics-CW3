/* General includes */
#include <iostream>
#include <vector>

#include "Include/UVSphereGeometry.h"
#include "Include/TriangleMesh.h"
#include "Include/GraphicsObject.h"
#include "Include/OBJMesh.h"
#include "Include/tank/TankObject.h"
#include "Include/transport/TransportObject.h"
#include "Include/Skybox.h"
#include "Include/Animation.h"
#include "Include/BLCamera.h"

//Physics
#include "Include/CWPhysicsObject.h"
#include "Include/PhysicsWrapperMini/PhysicsObjectTypes.h"
#include "Include/PhysicsWrapperMini/PhysicsWorld.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 0.0f);
FPS_Camera camera(cameraPos);
ThreeD_Camera tourCamera(cameraPos);

/* Screen parameters */
const int width = 1600;
const int height = 900;

/* Functions to handle input */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_movement(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void HandleInput();

void RenderQuad();

/* Stuff to read the mouse input to move the camera */
GLfloat lastX = width / 2.0;
GLfloat lastY = height / 2.0;

bool firstMouseInput = true;

//Mouse button flags
bool leftMouse = false;

//Key pressed flags
bool keys[1024];

//For calculating delta time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat simulationTime = 0.0f;

//For camera selection
static int cameraMode = 0;
bool stillRunning = true;

std::vector<CWObject*> gObjects;

int main(void)
{
    /* Attempt to initialise GLFW3, the window manager */
	if(!glfwInit())
	{
		std::cout << "Failed to start GLFW3" << std::endl;
		exit(EXIT_FAILURE);
	}

	/* Set up the main window */
	GLFWwindow* window = glfwCreateWindow(width, height, "Battle Zone: Skylands", NULL, NULL);
	if(!window)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* Set the required callback functions */
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_movement);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Set up GLEW before using any OpenGL functions */
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW." << std::endl;
		return -1;
	}

	/* Tell OpenGL the size of the rendering window */
	glViewport(0, 0, width, height);

	/* Turn on depth testing to make stuff in front actually look like it's in front. */
	glEnable(GL_DEPTH_TEST);

    /* Load the shader programs */
	Shader celShader("Shaders/CelShader.vert", "Shaders/CelShader.frag");
	Shader skyboxShader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");
	Shader waterfallShader("Shaders/WaterfallShader.vert", "Shaders/WaterfallShader.frag");
	Shader unlitShader("Shaders/UnlitShader.vert", "Shaders/UnlitShader.frag");
	//For shadows
	Shader depthShader("Shaders/DepthShader.vert", "Shaders/DepthShader.frag");

	Skybox sky("Images/Skybox/Skybox");

	PhysicsWorld world(1.0f, false);

	PhysicsBall cameraCollider(camera.GetCameraPosition(), &world);
	camera.addCollider(&cameraCollider);

	/* Create some lights */
    std::vector<LightSource*> lights;
    DirectionalLight sun(glm::vec3(5.0f, -5.0f, 2.0f), glm::vec3(0.4f), glm::vec3(0.8f), glm::vec3(1.0f));
    PointLight duskPoint(LIGHT_POS, 1.0, 0.01, 0.032, 0, glm::vec3(0.0f, 0.1f, 0.2f), glm::vec3(0.0f, 0.4f, 0.8f), glm::vec3(0.0f, 0.5f, 1.0f));
    PointLight dawnPoint(LIGHT_POS, 1.0, 0.01, 0.032, 1, glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lights.push_back(&sun);
    lights.push_back(&duskPoint);
    lights.push_back(&dawnPoint);

    GLfloat cyan[3] = {0.0f, 1.0f, 1.0f};
    TriangleMesh duskProjectileMesh(GetParticleSphere(0.5f), "na", cyan);
    PhysicsBall duskProjectileBody(true, 0.5f, 2.0f, glm::vec3(50.0f, 120.0f, 0.0f), &world);
    CWPhysicsLamp duskProjectile(&duskProjectileMesh, &duskProjectileBody, glm::vec3(0.0f), duskPoint);

    GLfloat green[3] = {0.0f, 1.0f, 0.0f};
    TriangleMesh dawnProjectileMesh(GetParticleSphere(0.5f), "na", green);
    PhysicsBall dawnProjectileBody(true, 0.5f, 2.0f, glm::vec3(50.0f, 120.0f, 5.0f), &world);
    CWPhysicsLamp dawnProjectile(&dawnProjectileMesh, &dawnProjectileBody, glm::vec3(0.0f), dawnPoint);

    /* Create the first tank */
    TankObject duskTank("Images/DuskTank/DuelTankBody_Dusk", "Images/DuskTank/DuelTankTurret_Dusk", "Images/DuskTank/DuelTankGun_Dusk", glm::vec3(0.0f, 5.0f, -30.0f), glm::quat(), duskProjectile);
    gObjects.push_back(&duskTank);

    /* Create the second tank */
    TankObject dawnTank("Images/DawnTank/DuelTankBody_Dawn", "Images/DawnTank/DuelTankTurret_Dawn", "Images/DawnTank/DuelTankGun_Dawn", glm::vec3(0.0f, 5.0f, 30.0f), glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), dawnProjectile);
    gObjects.push_back(&dawnTank);

    /* Create the first transport */
    TransportObject duskTransport("Images/DuskTransport/Transport", glm::vec3(0.0f, 10.0f, -30.0f), glm::quat());
    gObjects.push_back(&duskTransport);

    /* Create the second transport */
    TransportObject dawnTransport("Images/DawnTransport/Transport_Dawn", glm::vec3(0.0f, 5.0f, 30.0f), glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    gObjects.push_back(&dawnTransport);

    SetupAnimation(duskTank, dawnTank, duskTransport, dawnTransport, tourCamera);

    /* Environment objects */
    PhysicsConvexMesh rockCollider(false, "Models/Rock1.obj", 1.0f, glm::vec3(38.0f, 20.0f, -27.0f), glm::vec3(0.0f), &world);
    const struct Material rock1Mat = {"Images/Rock/Rock1_DIFFUSE.png", "Images/Rock/Rock1_SPECULAR.png", 8.0f};
    OBJMesh rock1Mesh("Models/Rock1.obj", rock1Mat);
    CWPhysicsObject rockObject(&rock1Mesh, &rockCollider, glm::vec3(0.0f));
    gObjects.push_back(&rockObject);

    PhysicsConvexMesh floatingIslandCollider(false, "Models/FloatingIsland1.obj", 1.0f, glm::vec3(40.0f, 30.0f, -25.0f), glm::vec3(0.0f), &world);
    const struct Material floatingIsland1Mat = {"Images/Rock/FloatingIsland1DIFFUSE.png", "Images/Rock/Rock1_SPECULAR.png", 8.0f};
    OBJMesh floatingIsland1Mesh("Models/FloatingIsland1.obj", floatingIsland1Mat);
    CWPhysicsObject floatingIslandObject(&floatingIsland1Mesh, &floatingIslandCollider, glm::vec3(0.0f));
    gObjects.push_back(&floatingIslandObject);

    PhysicsConvexMesh mainIslandCollider(false, "Models/MainIslandCollision.obj", 1.0f, glm::vec3(0.0f), glm::vec3(0.0f), &world);
    const struct Material mainIslandMat = {"Images/Rock/MainIsland_DIFFUSE.png", "Images/Rock/Rock1_SPECULAR.png", 8.0f};
    OBJMesh mainIslandMesh("Models/MainIsland.obj", mainIslandMat);
    CWPhysicsObject mainIslandObject(&mainIslandMesh, &mainIslandCollider, glm::vec3(0.0f));
    gObjects.push_back(&mainIslandObject);

    PhysicsConvexMesh smallIslandCollider(false, "Models/SmallIsland.obj", 1.0f, glm::vec3(50.0f, 100.0f, -10.0f), glm::vec3(0.0f, 30.0f, 0.0f), &world);
    const struct Material smallIslandMat = {"Images/Rock/MainIsland_DIFFUSE.png", "Images/Rock/Rock1_SPECULAR.png", 8.0f};
    OBJMesh smallIslandMesh("Models/SmallIsland.obj", smallIslandMat);
    CWPhysicsObject smallIslandObject(&smallIslandMesh, &smallIslandCollider, glm::vec3(0.0f));
    gObjects.push_back(&smallIslandObject);

    const struct Material mainIslandWaterfallMat = {"Images/Rock/River_DIFFUSE.png", "Images/Rock/River_SPECULAR.png", 16.0f};
    OBJMesh mainIslandWaterfallMesh("Models/MainIslandWaterfall.obj", mainIslandWaterfallMat);
    GraphicsObject mainIslandWaterfallObject(&mainIslandWaterfallMesh, glm::vec3(0.0f), glm::quat());
    gObjects.push_back(&mainIslandWaterfallObject);

    const struct Material smallWaterfallMat = {"Images/Rock/River_DIFFUSE.png", "Images/Rock/River_SPECULAR.png", 16.0f};
    OBJMesh smallWaterfallMesh("Models/SmallWaterfall.obj", smallWaterfallMat);
    GraphicsObject smallWaterfallObject(&smallWaterfallMesh, glm::vec3(50.0f, 100.0f, -10.0f), glm::angleAxis(glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    gObjects.push_back(&smallWaterfallObject);

	/* Main loop */
	while(!glfwWindowShouldClose(window) && stillRunning)
	{
	    //Calculate the time since the last frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		simulationTime += deltaTime;

		glfwPollEvents();
		HandleInput();

		world.stepWorld(deltaTime);

		duskProjectile.UpdateLight(deltaTime);
		dawnProjectile.UpdateLight(deltaTime);

		camera.cameraMove(deltaTime);
		tourCamera.MotionTween(simulationTime);

		/* Generate the view matrix */
		glm::mat4 view;
		/* Generate the projection matrix */
		glm::mat4 projection;

		switch(cameraMode)
		{
        default:
        case 0:
            view = camera.GetViewMatrix();
            break;
        case 1:
            view = glm::lookAt(glm::vec3(36.7f, 1.54f, 57.6f), glm::vec3(36.1f, 1.99f, 56.93f), glm::vec3(0.28f, 0.89f, 0.35f));
            break;
        case 2:
            view = glm::lookAt(glm::vec3(0.0f, 150.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 3:
            view = tourCamera.GetViewMatrix();
            break;
		}

        projection = glm::perspective(glm::radians(camera.Fov), (GLfloat)width / (GLfloat)height, 0.1f, 400.0f);
		glm::mat4 lightSpaceMatrix = sun.CalculateShadows(depthShader, gObjects, view, projection, lights);

		/* Rendering commands */
		glViewport(0, 0, width, height);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //Black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		celShader.Use();

        for(int i = 0; i < lights.size(); i++)
        {
            lights[i]->ApplyLighting(celShader);
        }

		glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sun.depthMap);
		glUniform1i(glGetUniformLocation(celShader.getShaderProgram(), "shadowMap"), 2);

		for(int i = 0; i < gObjects.size() - 2; i++)
        {
            gObjects[i]->MotionTween(simulationTime);
            gObjects[i]->Draw(celShader, view, projection, lightSpaceMatrix);
        }

        unlitShader.Use();
        duskProjectile.Draw(unlitShader, view, projection, lightSpaceMatrix);
        dawnProjectile.Draw(unlitShader, view, projection, lightSpaceMatrix);

        waterfallShader.Use();

        for(int i = 0; i < lights.size(); i++)
        {
            lights[i]->ApplyLighting(waterfallShader);
        }

        GLint waterfallTimerLocation = glGetUniformLocation(waterfallShader.getShaderProgram(), "timeOffset");
        glUniform1f(waterfallTimerLocation, currentFrame * -0.1);
        mainIslandWaterfallObject.Draw(waterfallShader, view, projection, lightSpaceMatrix);
		smallWaterfallObject.Draw(waterfallShader, view, projection, lightSpaceMatrix);

		glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sun.depthMap);
		glUniform1i(glGetUniformLocation(waterfallShader.getShaderProgram(), "shadowMap"), 2);

		//Draw the skybox last
		skyboxShader.Use();
		sky.Draw(skyboxShader, view, projection);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwSwapBuffers(window);
	}

	/* Terminate properly */
	glfwTerminate();

	return 0;
}

void ResetAnimation()
{
    simulationTime = 0;

    for(int i = 0; i < gObjects.size(); i++)
    {
        gObjects[i]->ResetObject();
    }
    tourCamera.ResetObject();
}

void HandleInput()
{
    if(keys[GLFW_KEY_LEFT])
        camera.mouse_input(-200.0f * deltaTime, 0.0f);
    else if(keys[GLFW_KEY_RIGHT])
        camera.mouse_input(200.0f * deltaTime, 0.0f);

    if(keys[GLFW_KEY_PAGE_UP])
        camera.mouse_input(0.0f, 200.0f * deltaTime);
    else if(keys[GLFW_KEY_PAGE_DOWN])
        camera.mouse_input(0.0f, -200.0f * deltaTime);

    if(keys[GLFW_KEY_UP])
        camera.accelerate(2.0f);
    else if(keys[GLFW_KEY_DOWN])
        camera.accelerate(-2.0f);

    if(keys[GLFW_KEY_SPACE])
        camera.brake();
}

/*
* Record the states of keys when one changes
*/
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Check to see if a new key has been pressed or released
	if (action == GLFW_PRESS)
	{
		keys[key] = true;

		//Additional checks for scene selection
		if(keys[GLFW_KEY_E] || keys[GLFW_KEY_M])
            cameraMode = 0; //Free cam
        else if(keys[GLFW_KEY_P])
            cameraMode = 1; //Screenshot
            //camera.PrintCoords();
        else if(keys[GLFW_KEY_L])
            cameraMode = 2; //Top-down
        else if(keys[GLFW_KEY_T])
            cameraMode = 3;
        else if(keys[GLFW_KEY_R])
            ResetAnimation();
        else if(keys[GLFW_KEY_Z])
            camera.ResetCamera();
        else if(keys[GLFW_KEY_Q] || keys[GLFW_KEY_ESCAPE])
            stillRunning = false; //Set the flag to close next frame
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

/*
* Record the changes in position of the mouse, use it to update the camera
*/
void mouse_movement(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouseInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouseInput = false;
	}

	//Difference between current moose position and previous
	GLfloat deltaX = xPos - lastX;
	GLfloat deltaY = lastY - yPos;

	//Update previous
	lastX = xPos;
	lastY = yPos;


	if (leftMouse)
	{
        camera.mouse_input(deltaX, deltaY);
	}
}

/*
* Record the state of the middle mouse when it changes
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		leftMouse = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		leftMouse = false;
}
