#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rlgl.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


#define	max_points	100
#define max_lines	50
#define max_chars	20
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
int letterCount = 0;
int framesCounter = 0;

char name[max_chars+1] = "\0";

static void Init();
static void Update(Camera2D camera, Rectangle textbox);
static void Draw(Camera2D camera, Rectangle textbox);
static void UpdateDrawFrame(Camera2D camera, Rectangle textbox);
static void Unload();

bool textBox_active = false;
bool graph = false;
bool start = true;

int main(Camera2D camera, Rectangle textbox) {
	InitWindow(screenWidth, screenHeight, "your calculator");
	Init();
	while(!WindowShouldClose()) {
		UpdateDrawFrame(camera, textbox);
	}
	Unload();
	CloseWindow();
	return 0;
}

static void Init(void) {
	Camera2D camera;
	camera.zoom = 1.0f;

	Rectangle textbox = { screenWidth/2.0f - 100, 180, 225, 50 };
	
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

static void Update(Camera2D camera, Rectangle textbox) {
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
	}
	if (start) {
		if (CheckCollisionPointRec(GetMousePosition(), textbox)) textBox_active = true;
		else textBox_active = false;
		if (textBox_active) {
			SetMouseCursor(MOUSE_CURSOR_IBEAM);
			int key = GetCharPressed();
			while (key > 0) {
				if (( key >= 32) && (key <= 125) && (letterCount < max_chars)) {
					name[letterCount] = (char)key;
					name[letterCount+1] = '\0';
					letterCount++;
				}
				key = GetCharPressed();
			}
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
		} else {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}
		if (textBox_active) {
			framesCounter++;
		} else {
			framesCounter = 0;
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
		if (start) {
			DrawRectangleRec(textbox, LIGHTGRAY);
			if (textBox_active) DrawRectangleLines((int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height, RED);
			else DrawRectangleLines((int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height, DARKGRAY);

			DrawText(name, (int)textbox.x + 5, (int)textbox.y + 8, 40, MAROON);
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, max_chars), 315, 250, 20, DARKGRAY);
			if (textBox_active) {
				if (letterCount < max_chars) {
					if (((framesCounter/20)%2) == 0) DrawText("_", (int)textbox.x + 8 + MeasureText(name, 40), (int)textbox.y + 12, 40, MAROON);
				}
				else DrawText("hello", 230, 300, 20, GRAY);
			}
		}
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

bool IsAnyKeyPressed() {
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126)) keyPressed = true;

	return keyPressed;
}

static void Unload(void) {
}
