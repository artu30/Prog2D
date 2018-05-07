#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include <litegfx.h>
#include <stb_image.h>
#include <stb_truetype.h>
#include <iostream>
#include <vector>
#include <glfw3.h>
#include <vec2.h>
#include <textureManager.h>
#include <Collider.h>
#include <Sprite.h>
#include <World.h>

using namespace std;

int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Programacion 2D - Colisiones", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Genero las texturas de los sprites
	ltex_t* characterTextureRun = loadTexture("data/run.png");
	ltex_t* characterTextureIdle = loadTexture("data/idle.png");
	ltex_t* level = loadTexture("data/background.png");
	
	Vec2 mousePos;

	// Inicializo el personaje
	Sprite character(characterTextureIdle, 1, 1);
	character.setFps(8);
	character.setColor(1, 1, 1, 1);
	Vec2 characterPivot(0.5f, 0.5f);
	character.setPivot(characterPivot);
	character.setPosition(Vec2(100.0f, 880.0f));

	// Inicializo el mundo
	World world(0.15f, 0.15f, 0.15f, level);

	// Cargo el mapa
	bool mapLoaded = world.loadMap("data/map.tmx", 1);

	// Incluyo la abeja al mundo
	world.addSprite(&character);

	// Establezco los ratios como se pide en el enunciado
	world.setScrollRatio(0, 0.4f);

	float hightToJump = 0;
	float maxHightToJump = -200.0f;
	float gravity = 200.0f;
	float characterVelocity = 0.0f;
	float maxVelocity = 200.0f;
	float minVelocity = -200.0f;
	float incrementInX = 200.0f;

	// Bucle principal
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);

		// Posicion del raton
		double mouse_x, mouse_y;
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
		
		float cameraX = world.getCameraPosition().getX();
		float cameraY = world.getCameraPosition().getY();

		const Vec2 screenSize(static_cast<float>(screenWidth), static_cast<float>(screenHeight));

		float moveToX = 0;
		float moveToY = 0;

		// Controlo el movimiento del personaje en horizontal
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			character.setScale(Vec2(1.0f, 1.0f));
			moveToX += incrementInX * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			character.setScale(Vec2(-1.0f, 1.0f));
			moveToX -= incrementInX * deltaTime;
		}
		
		// Controlo el salto del personaje con sus fuerzas usando lanzamiento vertical
		if (glfwGetKey(window, GLFW_KEY_SPACE) && character.getCanJump()) {
			hightToJump = maxHightToJump;
			characterVelocity = 0.0f;
			character.setCanJump(false);
		}
		else {
			hightToJump = 0;
		}
		moveToY += characterVelocity * deltaTime;
		float newVelocity = characterVelocity + (deltaTime * gravity) + hightToJump;
		if (newVelocity > maxVelocity){
			newVelocity = maxVelocity;
		}
		else if(newVelocity < minVelocity) {
			newVelocity = minVelocity;
		}
		characterVelocity = newVelocity;
		
		// Ajusto la textura del personaje si se mueve en x
		if (moveToX != 0) {
			character.setTexture(characterTextureRun);
			character.setFrames(6, 1);
		}
		else {
			character.setTexture(characterTextureIdle);
			character.setFrames(1, 1);
		}
		
		// Muevo el personaje
		world.moveSprite(character, Vec2(moveToX, moveToY));

		// Actualizo el mundo
		world.update(deltaTime);

		// Control de la camara con respecto al sprite y la mitad de la pantalla (para avanzar)
		Vec2 newCameraPosition;
		newCameraPosition.setX(character.getPosition().getX() - (screenSize.getX() / 2));
		newCameraPosition.setY(character.getPosition().getY() - (screenSize.getY() / 2));
		world.setCameraPosition(newCameraPosition);

		// Pinto el mundo
		world.draw(screenSize);

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    return 0;
}