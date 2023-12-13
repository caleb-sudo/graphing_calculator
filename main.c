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
#define max_sects	200

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

typedef enum Operator_pressed = { ADD, SUB, DIVIDE, MULTIPLY, ENTER, LESS, GREATER, EQUAL_GREATER, EQUAL_LESS } Operator_pressed; 
typedef enum Digit_pressed = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE } Digit_pressed;
typedef enum Button_pressed = { NEG, FRAC, LOG, SQ, CUBED, EXP, SQR, PI_ANS, LOG, ABS, ANS, SIN, TAN, COS, NEG_SIN, NEG_TAN, NEG_COS, L_BRAK, R_BRAK, CLR, DEL, COMMA, E } Button_pressed;
typedef enum Graph_pressed = { Y_EQUALS, X, GRAPH, TRACE, TABLE } Graph_pressed;


bool title = true;
bool norm = false;
bool graph = false;

float answer;
float sq_root_ans, squared_ans, cubed_ans, expo_ans, e_ans, pi_ans, log_ans;
float tan_ans, sin_ans, cos_ans, neg_tan_ans, neg_sin_ans, neg_cos_ans;
float less_ans, greater_ans, equal_less_ans, equal_greater_ans; 
float sum = (float) num1 + num2;
float diff = (float) num1 - num2;
float div = (float) num1 / num2;
float product = (float) num1 * num2;

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
	Texture2D divide = LoadTexture("resources/operators/division_button.png");
	Texture2D sub = LoadTexture("resources/operators/subtract_button.png");
	Texture2D add = LoadTexture("resources/operators/addition_button.png");
	Texture2D enter = LoadTexture("resources/operators/equals_button.png");
	Texture2D greater = LoadTexture("resources/operators/greater_button.png");
	Texture2D less = LoadTexture("resources/operators/less_button.png");
	Texture2D equal_less = LoadTexture("resources/operators/equal-less_button.png");
	Texture2D equal_greater = LoadTexture("resources/operators/eqqal-greater_button.png");

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
	Texture2D table = LoadTexture("resources/graph/table_button.png");
	Texture2D graph = LoadTexture("resources/graph/graph_button.png");
	Texture2D trace = LoadTexture("resources/graph/trace_button.png");

	Texture2D exponent = LoadTexture("resources/others/exponent_button.png");
	Texture2D cubed = LoadTexture("resources/others/cubed_button.png");
	Texture2D squared = LoadTexture("resource/others/squared_button.png");
	Texture2D E = LoadTexture("resources/others/x10_button.png");
	Texture2D pi = LoadTexture("resources/others/pi_button.png");
	Texture2D del = LoadTexture("resources/others/delete_button.png");
	Texture2D clear = LoadTexture("resources/others/clear_button.png");
	Texture2D sqr = LoadTexture("resources/others/sq_button.png");
	Texture2D neg = LoadTexture("resources/others/neg_button.png");
	Texture2D sin_button = LoadTexture("resources/others/sin_button.png");
	Texture2D cos_button = LoadTexture("resource/others/cos_button.png");
	Texture2D tan_button = LoadTexture("resources/others/tan_button.png");
	Texture2D neg_tan = LoadTexture("reources/others/tan-1_button.png");
	Texture2D neg_cos = LoadTexture("resources/others/cos-1_button.png");
	Texture2D neg_sin = LoadTexture("resources/others/sin-1_button.png");
	Texture2D first_brak = LoadTexture("resources/others/first-braket_button.png");
	Texture2D second_brak = LoadTexture("resources/others/second-braket_button.png");
	Texture2D decimal = LoadTexture("resources/others/decimal_button.png");
	Texture2D comma = LoadTexture("resources/others/comma_button.png");
	Texture2D log = LoadTexture("resources/others/log_button.png");
	Texture2D abs = LoadTexture("resources/others/abs_button.png");
	Texture2D ans = LoadTexture("resources/others/ans_button.png");

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

		if (CheckCollisionPointRec(mousePoint, zero) || IsKeyPressed(KEY_ZERO)) {
			digit.pressed = ZERO;
		} else if (CheckCollisionPointRec(mousePoint, one) || IsKeyPressed(KEY_ONE)) {
			digit.pressed = ONE;
		} else if (CheckCollisionPointRec(mousePoint, two) || IsKeyPressed(KEY_TWO)) {
			digit.pressed = TWO;
		} else if (CheckCollisionPointRec(mousePoint, three) || IsKeyPressed(KEY_THREE)) {
			digit.pressed = THREE;
		} else if (CheckCollisionPointRec(mousePoint, four) || IsKeyPressed(KEY_FOUR)) {
			digit.pressed = FOUR;
		} else if (CheckCollisionPointRec(mousePoint, five) || IsKeyPressed(KEY_FIVE)) {
			digit.pressed = FIVE;
		} else if (CheckCollisionPointRec(mousePoint, six) || IsKeyPressed(KEY_SIX)) {
			digit.pressed = SIX;
		} else if (CheckCollisionPointRec(mousePoint, seven) || IsKeyPressed(KEY_SEVEN)) {
			digit.pressed = SEVEN;
		} else if (CheckCollisionPointRec(mousePoint, eight) || IsKeyPressed(KEY_EIGHT)) {
			digit.pressed = EIGHT;
		} else if (CheckCollisionPointRec(mousePoint, nine) || IsKeyPressed(KEY_NINE)) {
			digit.pressed = NINE;
		}

		if (CheckCollisionPointRec(mousePoint, add)) {
			op.pressed = ADD;
		} else if (CheckCollisionPointRec(mousePoint, sub) || IsKeyPressed(KEY_MINUS)) {
			op.pressed = SUB;
		} else if (CheckCollisionPointRec(mousePoint, multiply)) {
			op.pressed = MULTIPLY;
		} else if (CheckCollisionPointRec(mousePoint, divide) || IsKeyPressed(KEY_SLASH)) {
			op.pressed = DIVIDE;
		} else if (CheckCollisionPointRec(mousePoint, enter) || IsKeyPressed(KEY_ENTER)) {
			op.pressed = ENTER;
		} else if (CheckCollisionPointRec(mousePoint, greater)) {
			op.pressed = GREATER;
		} else if (CheckCollisionPointRec(mousePoint, less)) {
			op.pressed = LESS;
		} else if (CheckCollisionPointRec(mousePoint, equal_greater)) {
			op.pressed = EQUAL_GREATER;
		} else if (CheckCollisionPointRec(mousePoint, equal_less)) {
			op.pressed = EQUAL_LESS;
		}

		if (CheckCollisionPointRec(mousePoint, log) || IsKeyPressed(KEY_L)) {
			button.pressed = LOG;
		} else if (CheckCollisionPointRec(mousePoint, pi)) {
			button.pressed = PI_ANS;
		} else if (CheckCollisionPointRec(mousePoint, sin)) {
			button.pressed = SIN;
		} else if (CheckCollisionPointRec(mousePoint, tan)) {
			button.pressed = TAN;
		} else if (CheckCollisionPointRec(mousePoint, cos)) {
			button.pressed = COS;
		} else if (CheckCollisionPointRec(mousePoint, neg_sin)) {
			button.pressed = NEG_SIN;
		} else if (CheckCollisionPointRec(mousePoint, neg_tan)) {
			button.pressed = NEG_TAN;
		} else if (CheckCollisionPointRec(mousePoint, neg_cos)) {
			button.pressed = NEG_COS;
		} else if (CheckCollisionPointRec(mousePoint, ans)) {
			button.pressed = ANS;
		} else if (CheckCollisionPointRec(mousePoint, abs)) {
			button.pressed = ABS;
		} else if (CheckCollisionPointRec(mousePoint, squared)) {
			button.pressed = SQ;
		} else if (CheckCollisionPointRec(mousePoint, cubed)) {
			button.pressed = CUBED;
		} else if (CheckCollisionPointRec(mousePoint, sqr)) {
			button.pressed = SQR;
		} else if (CheckCollisionPointRec(mousePoint, neg) || IsKeyPressed(KEY_MINUS)) {
			button.pressed = NEG;
		} else if (CheckCollisionPointRec(mousePoint, clear)) {
			button.pressed = CLR;
		} else if (CheckCollisionPointRec(mousePoint, del) || IsKeyPressed(KEY_BACKSPACE)) {
			button.pressed = DEL;
		} else if (CheckCollisionPointRec(mousePoint, comma) || IsKeyPressed(KEY_COMMA)) {
			button.pressed = COMMA;
		} else if (CheckCollisionPointRec(mousePoint, decimal) || IsKeyPressed(KEY_PERIOD)) {
			button.pressed = DECIMAL;
		} else if (CheckCollisionPointRec(mousePoint, first_brak) || IsKeyPressed(KEY_LEFT_BRACKET)) {
			button.pressed = L_BRAK;
		} else if (CheckCollisionPointRec(mousePoint, second_brak) || IsKeyPressed(KEY_RIGHT_BRACKET)) { 
			button.pressed = R_BRAK;
		}

		if (CheckCollisionPointRec(mousePoint, y_equals || IsKeyPressed(KEY_Y)) {
			graph.pressed = Y_EQUALS;
		} else if (CheckCollisionPointRec(mousePoint, graph) || IsKeyPressed(KEY_G)) {
			graph.pressed = GRAPH;
		} else if (CheckCollisionPointRec(mousePoint, x) || IsKeyPressed(KEY_X)) {
			graph.pressed = X;
		} else if (CheckCollisionPointRec(mousePoint, table) || IsKeyPressed(KEY_T) ) {
			graph.pressed = TABLE;
		} else if (CheckCollisionPointRec(mousePoint, trace) || IsKeyPressed(KEY_R)) {
			graph.pressed = TRACE;
		}
	}
	if (TABLE) {
		InitWindow(screenWidth, screenHeight, "table");
		while (!WindowShouldClose()) {
			Rectangle t-table_y = { screenWidth, screenHeight, screenWidth/2, 30, screenHeight };
			for (int i = 0, i < max_sects, i++) {
				rectangle t-table_x = { screenWidth, screenHeight-3*i, screenWidth, 5 };
				float x;
				float y;
			}
		}
	}

		CloseWindow();
	
	if (graph) {
		if (IsKeyPressed(KEY_TAB)) graph_pos.active = true;
		if (IsKeyPressed(KEY_BACKSPACE)) {
			graph = false;
			norm = true;
		}
		if (CheckCollisionPointRec(mousePoint, start_graph_bounds) || IsKeyPressed(KEY_G)) {
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
	if(IsKeyPressed(KEY_ESCAPE)) CloseWindow();

}
static void Draw(Camera2D camera) {
	BeginDrawing();
		ClearBackground(RAYWHITE);

		if (norm) {
			DrawTexture(zero, 0, 800);
			DrawTexture(one, 0, 770);
			DrawTexture(two. 0, 740);
			DrawTexture(three, 0, 710);
			DrawTexture(four, 30, 800);
			DrawTexture(five, 30, 770);
			DrawTexture(six, 30, 740);
			DrawTexture(seven, 30, 710);
			DrawTexture(eight, 60, 800);
			DrawTexture(nine, 60, 770);

			DrawTexture(add, 0, 680);
			DrawTexture(sub, 0, 650);
			DrawTextute(multiply, 0, 620);
			DrawTexture(divide, 0, 590);
		}
		
		double num1, num2;

		if (ADD) DrawText(TextFormat("%lf + %lf = %f", num1 + num2 = sum = answer), 700, 400, BLACK);
		if (SUB) DrawText(TextFormat("%lf - %lf = %f", num1 - num2 = diff = answer), 700, 400, BLACK);
		if (MULTIPLY) DrawText(TextFormat("%lf * %lf = %f", num1 * num2 = product = answer), 700, 400, BLACK);
		if (DIVIDE) DrawText(TextFormat("%lf / %lf = %f", num1 / num2 = div = answer), 700, 400, BLACK);
		if (LESS) {
			if (num1 < num2) {
				DrawText(TextFormat("%lf < %lf = %f", num1 < num2 = answer), 700, 400, BLACk);
			}
			if (num2 < num1) {
				DrawText(TextFormat("%lf < %lf = %f", num2 < num1 = answer), 700, 400, BLACK);
			}
		}
		if (GREATER) {
			if (num1 > num2) {
				DrawText(TextFormat("%lf > %lf = %f", num1 > num2 = answer), 700, 400, BLACK);
			}
			if (num2 > num1) {
				DrawText(TextFormat("%lf > %lf = %f", num2 > num1 = answer), 700, 400, BLACK);
			}
		}
		if (EQUAL_LESS) {
			if (num1 = num2 || num1 < num2) {
				DrawText(TextFormat("%lf =< %lf = %f", num1, num2, answer), 700, 400, BLACK);
			}
			if (num2 = num1 || num2 < num1) {
				DrawText(TextFormat("%lf =< %lf = %f", num2, num1, answer), 700, 400, BLACK);
			}
		}
		if (EQUAL_GREATER) {
			if (num1 = num2 || num1 > num1) {
				DrawText(TextFormat("%lf => %lf = %f", num1, num2, answer), 700, 400, BLACK);
			}
			if (num2 = num1 || num2 > num1) {
				DrawText(TextFormat("%lf => %lf = %f", num2, num1, answer), 700, 400, BLACK);
			}
		}

		double num;
		double exp;

		if (SQ) DrawText(TextFormat("%lf^2 = %f", num * num = square = answer), 700, 400, BLACK);
		if (CUBED) DrawText(TextFormat("%lf^3 = %f", num * num * num = cube = answer), 700, 400, BLACK);
		if (EXPO) DrawText(TextFormat("%lf^%lf", pow(num, exp)), 700, 400, BLACK);
		if (SQR) DrawText(TextFormat("sq(%lf) = %f", sqrt(num) = sq = answer), 700, 400, BLACK);
		if (PI_ANS) DrawText(TextFormat("pi * %lf", PI*num), 700, 400, BLACK);
		if (TAN) DrawText(TextFormat("tan(%lf) = %f", tan(num) = answer), 700, 400, BLACK);
		if (SIN) DrawText(TextFormat("sin(%lf) = %f", sin(num)) = answer, 700, 400, BLACK);
		if (COS) DrawText(TextFormat("cos(%lf) = %f", cos(num) = answer), 700, 400, BLACK);
		if (NEG_TAN) DrawText(TextFormat("-tan(%lf) = %f", -tan(num) = answer), 700, 400, BLACK);
		if (NEG_SIN) DrawText(TextFormat("-sin(%lf) = %f", -sin(num) = answer), 700, 400, BLACK);
		if (NEG_COS) DrawText(TextFormat("-cos(%lf) = %f", -cos(num) = answer), 700, 400, BLACK);
		if (ANS) DrawText(TextFormat("%f = %f", answer = answer), 700, 400, BLACK);
		if (ABS) DrawText(TextFormat(""), 700, 400, BLACK);
		if (LOG) DrawText(TextFormet(""), 700, 400, BLACK);
		if (FRAC) DrawText(TextFormat(""), 700, 400, BLACK);
		if (E) DrawText(TextFormat("%lfe", num*pow(10, exp)), 700, 400, BLACK);
		if (COMMA) DrawText(TextFormat(" , "), 700, 400, BLACK);
		if (DECIMAL) DrawText(TextFormat("."), 700, 400, BLACK);
		
		if (answer) { 
			DrawText(TextFormat("%f = %f", answer = answer), 700, 400, BLACK);
		} else {
			answer = num;
		}

		if (TABLE) {
			for (int i = 0; i < max_stacs; i++) {
				DrawRectangleRec(t-table_x.x, t-table_x.y);
				DrawText(TextFormat("%f", x), 100, 300, BLACK);
				DrawText(TextFormat("%f", y), 300, 300, BLACK);
			}
			DrawRectangleRec(t-table_y.x, t-tabel_y.y);
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

static void UpdateDrawFrame(Camera2D camera) {
	Update(camera);
	Draw(camera);
}

static void Unload(void) {
	UnloadTexture(multiply);
	UnloadTexture(division);
	UnloadTexture(subtract);
	UnloadTexture(addition);
	UnloadTexture(enter);
	UnloadTexture(greater);
	UnloadTexture(less);
	UnloadTexture(equal_less);
	UnloadTexture(equal_greater);

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
	UnloadTexture(table);
	UnloadTexture(graph);
	UnloadTexture(trace);

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
