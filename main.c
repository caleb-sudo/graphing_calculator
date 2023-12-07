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

bool title = true;
bool norm = false;
bool graph = false;
bool button_pressed = false;

int sq_num;

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

	Vector2 mousePoint = { 0.0f, 0.0f };

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
	Texture2D y_equals = LoadTexture("resources/graph/Y=_button.png");

	Texture2D exponent = LoadTexture("resources/others/exponent_button.png");
	Texture2D cubed = LoadTexture("resources/others/cubed_button.png");
	Texture2D squared = LoadTexture("resource/others/squared_button.png");
	Texture2D E = LoadTexture("resources/others/x10_button.png");
	Texture2D pi = LoadTexture("resources/others/pi_button.png");
	Texture2D del = LoadTexture("resources/others/delete_button.png");
	Texture2D clear = LoadTexture("resources/others/clear_button.png");
	Texture2D sq = LoadTexture("resources/others/sq_button.png");
	Texture2D neg = LoadTexture("resources/others/neg_button.png");
	Texture2D sin_button = LoadTexture("resources/others/sin_button.png");
	Texture2D cos_button = LoadTexture("resource/others/cos_button.png");
	Texture2D tan_button = LoadTexture("resources/others/tan_button.png");
	Texture2D neg_tan = LoadTexture("reources/others/tan-1_button.png");
	Texture2D neg_cos = LoadTexture("resources/others/cos-1_button.png");
	Texture2D neg_sin = LoadTexture("resources/others/sin-1_button.png");
	Texture2D first_bracket = LoadTexture("resources/others/first-braket_button.png");
	Texture2D second_bracket = LoadTexture("resources/others/second-braket_button.png");
	Texture2D decimal = LoadTexture("resources/others/decimal_button.png");
	Texture2D comma = LoadTexture("resources/others/comma_button.png");
	Texture2D log_buttom = LoadTexture("resources/others/log_button.png");
	Texture2D abs = LoadTexture("resources/others/abs_button.png");
	Texture2D ans = LoadTexture("resources/others/ans_button.png");
	
	Rectangle one_bounds = { screenWidth/2 - 30, screenHeight/2 - 30, 30, 30 };
	Rectangle two_bounds = { screenWidth/2 -60, screenHeight/2 -30, 30, 30 };
	Rectangle three_bounds = { screenWidth/2 -90, screenHeight/2 -30, 30, 30 };
	Rectangle four_bounds = { screenWidth/2 + 30, screenHeight/2 -30, 30, 30 };
	Rectangle five_bounds = { screenWidth/2 +60, screenHeight/2 -30, 30, 30 };
	Rectangle six_bounds = { screenWidth/2 +90, screenHeight/2 -30, 30, 30 };
	Rectangle seven_bounds = { screenWidth/2 -30, screenHeight/2 -60, 30, 30 };
	Rectangle eight_bounds = { screenWidth/2 -60, screenHeight/2 -60, 30, 30 };
	Rectangle nine_bounds = { screenWidth/2 -90, screenHeight/2 -60, 30, 30 };
	Rectangle zero_bounds = { screenWidth/2 +30, screenHeight/2 -60, 30, 30 };

	Rectangle add_bounds = { screenWidth/2 +60, screenHeight +30, 30, 30 };
	Rectangle multiply_bounds = { screenWidth/2 +60, screenHeight +60, 30, 30 };
	Rectangle sub_bounds = { screenWidth/2 +60, screenHeight +90, 30, 30 };
	Rectangle div_bounds = { screenWidth/2 +60, screenHeight +120, 30, 30 };
	Rectangle enter_bounds = { screenWidth/2 +60, screenHeight +150, 30, 30 };
	
	Rectangle neg_bounds = { screenWidth/2 +30, screenHeight +150, 30, 30 };
	Rectangle decimal_bounds = { screenWidth/2 +60, screenHeight/2 -60, 30, 30 };
	Rectangle squared_bounds = { screenWidth/2 -30, screenHeight/2 +30, 30, 30 };
	Rectangle cubed_bounds = { screenWidth/2 -60, screenHeight/2 +30, 30, 30 };
	Rectangle exponent_bounds = { screenWidth/2 -90, screenHeight+30, 30, 30 };
	Rectangle first_braket_bounds = { screenWidth+30, screenHeight+30, 30, 30 };
        Rectangle second_braket_bounds = { screenWidth+60, screenHeight+30, 30, 30 };
	Rectangle comma_bounds = { screenWidth +90, screenHeight+30, 30, 30 }; 	



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
	if (title) {
		if (IsKeyPressed(KEY_ENTER)) norm = true;
	}
	if (norm) {
		mousePoint = GetMousePosition();
		button_pressed = false;
		if (CheckCollisionPointRec(mousePoint, one_bounds) || IsKeyPressed(KEY_ONE)) {
			//print one
		} else if (CheckCollisionPointRec(mousePoint, two_bounds) || IsKeyPressed(KEY_TWO)) {
			//print two
		} else if (CheckCollisionPointRec(mousePoint, three_bounds) || IsKeyPressed(KEY_THREE)) {
			//print three
		} else if (CheckCollisionPointRec(mousePoint, four_bounds) || IsKeyPressed(KEY_FOUR)) {
			//print four
		} else if (CheckCollisionPointRec(mousePoint, five_bounds) || IsKeyPressed(KEY_FIVE)) {
			//print five
		} else if (CheckCollisionPointRec(mousePoint, six_bounds) || IsKeyPressed(KEY_SIX)) {
			//print six
		} else if (CheckCollisionPointRec(mousePoint, seven_bounds) || IsKeyPressed(KEY_SEVEN)) {
			//print seven
		} else if (CheckCollisionPointRec(mousePoint, eight_bounds) || IsKeyPressed(KEY_EIGHT)) {
			//print eight
		} else if (CheckCollisionPointRec(mousePoint, nine_bounds) || IsKeyPressed(KEY_NINE)) {
			//prints nine
		} else if (CheckCollisionPointRec(mousePoint, zero_bounds) || IsKeyPressed(KEY_ZERO)) {
			//prints zero
		} else if (CheckCollisionPointRec(mousePoint, sub_bounds) || IsKeyPressed(KEY_MINUS)) {
			//prints -
		} else if (CheckCollisionPointRec(mousePoint, enter_bounds) || IsKeyPressed(KEY_EQUAL)) {
			// enters equation
		} else if (CheckCollisionPointRec(mousePoint, multiply_bounds)) {
			//prints *
		} else if (CheckCollisionPointRec(mousePoint, add_bounds)) {
			//prints +
		} else if (CheckCollisionPointRec(mousePoint, sub_bounds)) {
			//prints
		} else if (CheckCollisionPointRec(mousePoint, first_braket_bounds) || IsKeyPressed(KEY_LEFT_BRACKET)) {
			//prints (
		} else if (CheckCollisionPointRec(mousePoint, second_braket_bounds) || IsKeyPressed(KEY_RIGHT_BRACKET)) {
			// prints )
		} else if (CheckCollisionPointRec(mousePoint, division_bounds) || IsKeyPressed(KEY_BACKSLASH)) {
			// prints division symbol
		} else if (CheckCollisionPointRec(mousePoint, decimal_bounds) || IsKeyPressed(KEY_PERIOD)) {
			// prints decimal
		} else if (CheckCollisionPointRec(mousePoint, y=_bounds) || IsKeyPressed(KEY_Y)) {
			graph = true;
		} else if (CheckCollisionPointRec(mousePoint, comma_bounds) || IsKeyPressed(KEY_COMMA)) {
			// prints ,
		} else if (CheckCollisionPointRec(mousePoint, del_bounds) || IsKeyPressed(KEY_BACKSPACE)) {
			// deletes one
		} else if (CheckCollisionPointRec(mousePoint, clr_bounds) || IsKeyPressed(KEY_C)) {
			// clears screen
		} else if (CheckCollisionPointRec(mousePoint, tan_bounds)) {
		} else if (CheckCollisionPointRec(mousePoint, sin_bounds)) {
		} else if (CheckCollisionPointRec(mousePoint, cos_bounds)) {
		} else if (CheckCollisionPointRec(mousePoint, neg_tan_bounds)) {
		} else if (CheckCollisionPointRec(mousePoint, neg_sin_bounds)) {
		} else if (CheckCollisionPointRec(mousePoint, neg_cos_bounds)) { 
		}

	}
	if (graph) {
		if (IsKeyPressed(KEY_TAB)) graph_pos.active = true;
		if (IsKeyPressed(KEY_BACKSPACE)) {
			graph = false;
			norm = true;
		}
		if (CheckCollisionPointRec(mousePoint, start_graph_bounds) || IsKeyPressed(KEY_G)) {
			// draw
		} else if (CheckCollisionPointRec(mousePoint, table_bounds) || IsKeyPressed(KEY_T)) {
		}
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
	if(IsKeyPressed(KEY_ESC)) CloseWindow();
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
	UnloadTexture(subtract);
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
	UnloadTexture(y_equals);

	UnloadTexture(exponent);
	UnloadTexture(cubed);
	UnloadTexture(squared);
	UnloadTexture(E);
	UnloadTexture(pi);
	UnloadTexture(del);
	UnloadTexture(clear);
	UnloadTexture(sq);
	UnloadTexture(neg);
	UnloadTexture(sin_button);
	UnloadTexture(cos_button);
	UnloadTexture(tan_button);
	UnloadTexture(neg_tan);
	UnloadTexture(neg_cos);
	UnloadTexture(neg_sin);
	UnloadTexture(first_bracket);
	UnloadTexture(second_bracket);
	UnloadTexture(decimal);
	UnloadTexture(comma);
	UnloadTexture(log_button);
	UnloadTexture(abs);
	UnloadTexture(ans);
}
