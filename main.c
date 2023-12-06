#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rlgl.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


#define	max_points	100
#define max_lines	50
#define GraphSpeed	7.0f

typedef struct Points {
	int radius;
	Vector2 position;
	bool active;
} Points;
typedef struct Lines {
	bool active;
	Vector2 size;
	Vector2 position;
} Lines;
typedef struct Graph_Pos {
	bool active;
	int radius;
	Vector2 position;
	Vector2 speed;
} Graph_Pos;

static Points points[max_points] = { 0 };
static Lines lines[max_lines] = { 0 };
static Graph_Pos graph_pos = { 0 };

const int screenWidth = 800;
const int screenHeight = 450;

static void Init();
static void Update(Camera2D camera);
static void Draw(Camera2D camera);
static void UpdateDrawFrame(Camera2D camera);
static void Unload();

bool graph = false;


Texture2D multiply = LoadTexture("resources/operators/multiply_button.png");
Texture2D division = LoadTexture("resources/operators/division_button.png");
Texture2D subtract = LoadTexture("resources/operators/subtract_button.png");
Texture2D addition = LoadTexture("resources/operators/addition_button.png");
Texture2D enter = LoadTexture("resources/operators/equals_button.png");

Texture2D zero = LoadTexture("resources/ints/zero_button.png");
Texture2D one = LoadTexture("resources/ints/one_button.png");
Texture2D two = LoadTexture("resources/ints/two_button.png");
Texture2D three = LoadTexture("resources/ints/three_button.png");
Texture2D four = LoadTexture("resource/ints/four_button.png");
Texture2D five = LoadTexture("resources/ints/five_button.png");
Texture2D six = LoadTexture("resources/ints/six_button.png");
Texture2D seven = LoadTexture("resources/ints/seven_button.png");
Texture2D eight = LoadTexture("resources/ints/eight_button.png");
Texture2D nine = LoadTexture("resource/ints/nine_button.png");

Texture2D x = LoadTexture("resources/graph/x_button.png");

Texture2D exponent = LoadTexture("resources/others/exponent_button.png");
Texture2D cubed = LoadTexture("resources/others/cubed_button.png");
Texture2D squared = LoadTexture("resource/others/squared_button.png");
Texture2D E = LoadTexture("resources/others/x10_button.png");
Texture2D pi = LoadTexture("resources/others/pi_button.png");

int main(Camera2D camera) {
	InitWindow(screenWidth, screenHeight, "your calculator");
	Init();
	while(!WindowShouldClose()) {
		UpdateDrawFrame(camera);
	}
	Unload();
	CloseWindow();
	return 0;
}

static void Init(void) {
	Camera2D camera;
	camera.zoom = 1.0f;
	
	for (int i = 0; i < max_lines; i++) {
		lines[i].position = (Vector2) { 0, y-int };
		lines[i].active = false;
	}
	for (int i = 0; i < max_points; i++) {
		points[i].active = false;
		points[i].radius = 5;
	}
	graph_pos.active = false;
	graph_pos.radius = 0;
	graph_pos.position = (Vector2) { GetScreenWidth()/2 -30, GetScreenHeight()/2 -30 };
	graph_pos.speed = (Vector2) { 0, 0 };
}

static void Update(Camera2D camera) {
	if (graph) {
		if (IsKeyPressed(KEY_TAB)) graph_pos.active = true;
		if (graph_pos.active) {
			if (IsKeyDown(KEY_UP)) {
				graph_pos.position.y += GraphSpeed;
			} else if (IsKeyDown(KEY_DOWN)) {
				graph_pos.position.y -= GraphSpeed;
			} else if (IsKeyDown(KEY_LEFT)) {
				graph_pos.position.x -= GraphSpeed;
			} else if (IsKeyDown(KEY_RIGHT)) {
				graph_pos.position.x += GraphSpeed;
			}
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f/camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
			camera.offset = GetMousePosition();
			camera.target = mouseWorldPos;
			const float zoomIncrement = 0.125;
			camera.zoom += (wheel*zoomIncrement);
			if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
		}
	}
}

static void Draw(Camera2D camera, Rectangle textbox) {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		if (graph) {
			BeginMode2D(camera);
				rlPushMatrix();
					rlTranslatef(0,25*50,0);
					rlRotatef(90,1,0,0);
					DrawGrid(100,50);
				rlPopMatrix();
			EndMode2D();
		}
	EndDrawing();
}

static void UpdateDrawFrame(Camera2D camera, Rectangle textbox) {
	Update(camera, textbox);
	Draw(camera, textbox);
}

static void Unload(void) {
	UnloadTexture(multiply);
	UnloadTexture(division);
	UnloadTexture(subtraction);
	UnloadTexture(addition);
	UnloadTexture(enter);

	UnloadTexture(zero);
	UnloadTexture(one);
	UnloadTexture(two);
	UnloadTexture(three);
	UnloadTexture(four);
	UnloadTexture(five);
	UnloadTexture(six);
	UnloadTexture(seven);
	UnloadTexture(eight);
	UnloadTexture(nine);

	UnloadTexture(x);

	UnloadTexture(exponent);
	UnloadTexture(cubed);
	UnloadTexture(squared);
	UnloadTexture(E);
	UnloadTexture(pi);
}
