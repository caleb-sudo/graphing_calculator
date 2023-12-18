#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rlgl.h"
#include "include/raygui.h"

#include <stdlib.h> 
#include <stdbool.h>
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

typedef enum{ ADD, SUB, DIVIDE, MULTIPLY, ENTER, LESS, GREATER, EQUAL_GREATER, EQUAL_LESS } Operator_pressed; 
typedef enum{ ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE } Digit_pressed;
typedef enum{ NEG, FRAC, LOG, SQ, CUBED, EXPO, SQR, PI_ANS, LOG, ABS, ANS, SIN, TAN, COS, NEG_SIN, NEG_TAN, NEG_COS, L_BRAK, R_BRAK, CLR, DEL, COMMA, E_BUTTON, IN, EXP, MAX, MIN, LIM, MOD, DET } Button_pressed;
typedef enum{ Y_EQUALS, X, Y, GRAPH, TRACE, TABLE, COT } Graph_pressed;


bool title = true;
bool norm = false;
bool graph = false;
bool table = false;

float answer;
float sq_root_ans, expo_ans, e_ans, log_ans;
float tan_ans, sin_ans, cos_ans, neg_tan_ans, neg_sin_ans, neg_cos_ans;
float less_ans, greater_ans, equal_less_ans, equal_greater_ans;
float in_ans, exp_ans, lim_ans, min_ans, max_ans, mod_ans, det_ans;
float x, y;
float pi_ans = (float) PI*num;
float sum = (float) num1 + num2;
float diff = (float) num1 - num2;
float div = (float) num1 / num2;
float product = (float) num1 * num2;
float squared_ans = (float) num * num;
float cubed_ans = (float) num * num * num;

int main(Camera2D camera) {
	InitWindow(screenWidth, screenHeight, "your calculator");
	Camera2D camera;
	camera.zoom = 1.0f;

	Vector2 mousePoint = { 0.0f, 0.0f };

	Texture2D multiply = LoadTexture("resources/textures/operators/multiply_button.png");
	Texture2D divide = LoadTexture("resources/textures/operators/division_button.png");
	Texture2D sub = LoadTexture("resources/textures/operators/subtract_button.png");
	Texture2D add = LoadTexture("resources/textures/operators/addition_button.png");
	Texture2D enter = LoadTexture("resources/textures/operators/equals_button.png");
	Texture2D greater = LoadTexture("resources/textures/operators/greater_button.png");
	Texture2D less = LoadTexture("resources/textures/operators/less_button.png");
	Texture2D equal_less = LoadTexture("resources/textures/operators/equal-less_button.png");
	Texture2D equal_greater = LoadTexture("resources/textures/operators/eqqal-greater_button.png");

	Texture2D zero = LoadTexture("resources/textures/ints/zero_button.png");
	Texture2D one = LoadTexture("resources/textures/ints/one_button.png");
	Texture2D two = LoadTexture("resources/textures/ints/two_button.png");
	Texture2D three = LoadTexture("resources/textures/ints/three_button.png");
	Texture2D four = LoadTexture("resource/textures/ints/four_button.png");
	Texture2D five = LoadTexture("resources/textures/ints/five_button.png");
	Texture2D six = LoadTexture("resources/textures/ints/six_button.png");
	Texture2D seven = LoadTexture("resources/textures/ints/seven_button.png");
	Texture2D eight = LoadTexture("resources/textures/ints/eight_button.png");
	Texture2D nine = LoadTexture("resource/textures/ints/nine_button.png");

	Texture2D x_button = LoadTexture("resources/textures/graph/x_button.png");
	Texture2D y_button = LoadTexture("resources/textures/graph/y_button.png");
	Texture2D y_equals = LoadTexture("resources/textures/graph/Y=_button.png");
	Texture2D table = LoadTexture("resources/textures/graph/table_button.png");
	Texture2D graph = LoadTexture("resources/textures/graph/graph_button.png");
	Texture2D trace = LoadTexture("resources/textures/graph/trace_button.png");
	Texture2D cot = LoadTexture("resources/textures/graph/cot_button.png");

	Texture2D exponent = LoadTexture("resources/textures/others/exponent_button.png");
	Texture2D cubed = LoadTexture("resources/textures/others/cubed_button.png");
	Texture2D squared = LoadTexture("resource/textures/others/squared_button.png");
	Texture2D e_button = LoadTexture("resources/textures/others/x10_button.png");
	Texture2D pi = LoadTexture("resources/textures/others/pi_button.png");
	Texture2D del = LoadTexture("resources/textures/others/delete_button.png");
	Texture2D clear = LoadTexture("resources/textures/others/clear_button.png");
	Texture2D sqr = LoadTexture("resources/textures/others/sq_button.png");
	Texture2D neg = LoadTexture("resources/textures/others/neg_button.png");
	Texture2D sin_button = LoadTexture("resources/textures/others/sin_button.png");
	Texture2D cos_button = LoadTexture("resource/textures/others/cos_button.png");
	Texture2D tan_button = LoadTexture("resources/textures/others/tan_button.png");
	Texture2D neg_tan = LoadTexture("reources/textures/others/tan-1_button.png");
	Texture2D neg_cos = LoadTexture("resources/textures/others/cos-1_button.png"); 
	Texture2D neg_sin = LoadTexture("resources/textures/others/sin-1_button.png");
	Texture2D left_brak = LoadTexture("resources/textures/others/first-braket_button.png");
	Texture2D right_brak = LoadTexture("resources/textures/others/second-braket_button.png");
	Texture2D decimal = LoadTexture("resources/textures/others/decimal_button.png");
	Texture2D comma = LoadTexture("resources/textures/others/comma_button.png");
	Texture2D log = LoadTexture("resources/textures/others/log_button.png");
	Texture2D abs = LoadTexture("resources/textures/others/abs_button.png");
	Texture2D ans = LoadTexture("resources/textures/others/ans_button.png");
	Texture2D in = LoadTexture("resources/textures/others/in_button.png");
	Texture2D exp = LoadTexture("resources/textures/others/exp_button.png");
	Texture2D max = LoadTexture("resources/textures/others/max_button.png");
	Texture2D min = LoadTexture("resources/textures/others/min_button.png");
	Texture2D det = LoadTexture("resources/textures/others/det_button.png");
	Texture2D mod = LoadTexture("resources/textures/others/mod_button.png");
	Texture2D lim = LoadTexture("resources/textures/others/lim_button.png");

	if (graph) {
		for (int i = 0; i < max_points; i++) {
			points[i].radius = 5;
			points[i].active = true;
			points[i].poisition = (Vector2) {  };
		}
		for (int i = 0; i < max_lines; i++) {
			lines[i].active = true;
			lines[i].size = (Vector2) { };
			lines[i].position = (Vector2) { };
		}
		graph_pos.active = false;
		graph_pos.radius = 0;
		graph_pos.position = (Vector2) { GetScreenWidth()/2 -30, GetScreenHeight()/2 -30 };
		graph_pos.speed = (Vector2) { 0, 0 };
	}
	while(!WindowShouldClose()) {
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
		} else if (CheckCollisionPointRec(mousePoint, left_brak) || IsKeyPressed(KEY_LEFT_BRACKET)) {
			button.pressed = L_BRAK;
		} else if (CheckCollisionPointRec(mousePoint, right_brak) || IsKeyPressed(KEY_RIGHT_BRACKET)) { 
			button.pressed = R_BRAK;
		} else if (CheckCollisionPointRec(mousePoint, in)) {
			button.pressed = IN;
		} else if (CheckCollisionPointRec(mousePoint, exp)) {
			button.pressed = EXP;
		} else if (CheckCollisionPointRec(mousePoint, min)) {
			button.pressed = MIN;
		} else if (CheckCollisionPointRec(mousePoint, max)) {
			button.pressed = MAX; 
		} else if (CheckCollisionPointRec(mousePoint, det)) {
			button.pressed = DET;
		} else if (CheckCollisionPointRec(mousePoint, mod)) {
			button.pressed = MOD;
		} else if (CheckCollisionPointRec(mousePoint, lim)) {
			button.pressed = LIM;
		} else if (CheckCollisionPointRec(mousePoint, e_button) || IsKeyPressed(KEY_E)) {
			button.pressed = E_BUTTON;
		}

		if (CheckCollisionPointRec(mousePoint, y_equals) || IsKeyPressed(KEY_Y)) {
			graph.pressed = Y_EQUALS;
		} else if (CheckCollisionPointRec(mousePoint, graph) || IsKeyPressed(KEY_G)) {
			graph.pressed = GRAPH;
		} else if (CheckCollisionPointRec(mousePoint, x_button) || IsKeyPressed(KEY_X)) {
			graph.pressed = X;
		} else if (CheckCollisionPointRec(mousePoint, y_button) || IsKeyPressed(KEY_Y)) {
			graph.pressed = Y;
		} else if (CheckCollisionPointRec(mousePoint, table) || IsKeyPressed(KEY_T)) {
			graph.pressed = TABLE;
		} else if (CheckCollisionPointRec(mousePoint, trace) || IsKeyPressed(KEY_R)) {
			graph.pressed = TRACE;
		} else if (CheckCollisionPointRec(mousePoint, cot)) {
			graph.pressed = COT;
		}
	}
	if (graph) {
		if (IsKeyPressed(KEY_TAB)) graph_pos.active = true;
		if (IsKeyPressed(KEY_BACKSLASH)) graph_pos.active = false;
		if (IsKeyPressed(KEY_T)) table = true;
		if (IsKeyPressed(KEY_BACKSPACE)) {
			graph = false;
			norm = true;
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
	BeginDrawing();
		ClearBackground(RAYWHITE);

		if (title) {
			DrawText("Welcome! \n click enter to start", 0, 0, 40, BLACK);
		}

		if (norm) {
			DrawTexture(zero, 0, 800, WHITE);
			DrawTexture(one, 0, 770, WHITE);
			DrawTexture(two, 0, 740, WHITE);
			DrawTexture(three, 0, 710, WHITE);
			DrawTexture(four, 30, 800, WHITE);
			DrawTexture(five, 30, 770, WHITE);
			DrawTexture(six, 30, 740, WHITE);
			DrawTexture(seven, 30, 710, WHITE);
			DrawTexture(eight, 60, 800, WHITE);
			DrawTexture(nine, 60, 770, WHITE);

			DrawTexture(add, 0, 680, WHITE);
			DrawTexture(sub, 0, 650, WHITE);
			DrawTexture(multiply, 0, 620, WHITE); 
			DrawTexture(divide, 0, 590, WHITE);
			DrawTexture(enter, 30, 680, WHITE);

			DrawTexture(sin_button, 0, 830, WHITE);
			DrawTexture(cos_button, 70, 830, WHITE);
			DrawTexture(tan_button, 140, 830, WHITE);
			DrawTexture(neg_sin, 0, 860, WHITE);
			DrawTexture(neg_cos, 70, 860, WHITE);
			DrawTexture(neg_tan, 140, 860, WHITE);
			DrawTexture(log, 0, 0, WHITE);
			DrawTexture(sqr, 0, 30, WHITE);
			DrawTexture(squared, 0, 60, WHITE);
			DrawTexture(cubed, 0, 90, WHITE);
			DrawTexture(exponent, 0, 120, WHITE);
			DrawTexture(decimal, 0, 150, WHITE);
			DrawTexture(comma, 0, 180, WHITE);
			DrawTexture(neg, 0, 210, WHITE);
			DrawTexture(left_brak, 30, 210, WHITE);
			DrawTexture(right_brak, 60, 210, WHITE);
			DrawTexture(e_button, 90, 210, WHITE);
			DrawTexture(pi, 120, 210, WHITE);
			DrawTexture(ans, 200, 210, WHITE);
			DrawTexture(abs, 270, 210, WHITE);
			DrawTexture(clear, 340, 210, WHITE);
			DrawTexture(del, 420, 210, WHITE);
			DrawTexture(in, 100, 240, WHITE);
			DrawTexture(exp, 100, 300, WHITE);
			DrawTexture(lim, 300, 300, WHITE);
			DrawTexture(mod, 370, 370, WHITE);
			DrawTexture(max, 470, 470, WHITE);
			DrawTexture(min, 570, 570, WHITE);
			DrawTexture(det, 670, 670, WHITE);
			
			DrawTexture(x_button, 150, 210, WHITE);
			DrawTexture(cot, 200, 210, WHITE);
			DrawTexture(graph, 300, 210, WHITE);
			DrawTexture(table, 400, 210, WHITE);
			DrawTexture(trace, 480, 210, WHITE);
		}

		if (ONE) {
			if (1) DrawText("1", 700, 400, 20, BLACK);
			if (2) DrawText("1", 900, 400, 20, BLACK);
		}
		if (TWO) {
			if (1) DrawText("2", 700, 400, 20, BLACK);
			if (2) DrawText("2", 900, 400, 20, BLACK);
		}
		if (THREE) {
			if (1) DrawText("3", 700, 400, 20, BLACK);
			if (2) DrawText("3", 900, 400, 20, BLACK);
		}
		if (FOUR) {
			if (1) DrawText("4", 700, 400, 20, BLACK);
			if (2) DrawText("4", 900, 400, 20, BLACK);
		}
		if (FIVE) {
			if (1) DrawText("5", 700, 400, 20, BLACK);
			if (2) DrawText("5", 900, 400, 20, BLACK);
		}
		if (SIX) {
			if (1) DrawText("6", 700, 400, 20, BLACK);
			if (2) DrawText("6", 900, 400, 20, BLACK);
		}
		if (SEVEN) {
			if (1) DrawText("7", 700, 400, 20, BLACK);
			if (2) DrawText("7", 900, 400, 20, BLACK);
		}
		if (EIGHT) {
			if (1) DrawText("8", 700, 400, 20, BLACK);
			if (2) DrawText("8", 900, 400, 20, BLACK);
		}
		if (NINE) {
			if (1) DrawText("9", 700, 400, 20, BLACK);
			if (2) DrawText("9", 900, 400, 20, BLACK);
		}
		if (ZERO) {
			if (1) DrawText("0", 700, 400, 20, BLACK);
			if (2) DrawText("0", 700, 400, 20, BLACK);
		}

		if (L_BRAK) DrawText("(", 700, 400, 20, BLACK);
		if (R_BRAK) DrawText(")", 700, 400, 20, BLACK);
		
		double num1, num2;

		if (ADD) DrawText(TextFormat("%lf + %lf = %f", num1, num2, sum, answer), 700, 400, 20, BLACK);
		if (SUB) DrawText(TextFormat("%lf - %lf = %f", num1, num2, diff, answer), 700, 400, 20, BLACK);
		if (MULTIPLY) DrawText(TextFormat("%lf * %lf = %f", num1, num2, product, answer), 700, 400, 20, BLACK);
		if (DIVIDE) DrawText(TextFormat("%lf / %lf = %f", num1, num2, div, answer), 700, 400, 20, BLACK);
		if (LESS) {
			if (num1 < num2) {
				DrawText(TextFormat("%lf < %lf = %f", num1, num2, answer), 700, 400, 20, BLACK);
			}
			if (num2 < num1) {
				DrawText(TextFormat("%lf < %lf = %f", num2, num1, answer), 700, 400, 20, BLACK);
			}
		}
		if (GREATER) {
			if (num1 > num2) {
				DrawText(TextFormat("%lf > %lf = %f", num1, num2, answer), 700, 400, 20, BLACK);
			}
			if (num2 > num1) {
				DrawText(TextFormat("%lf > %lf = %f", num2, num1, answer), 700, 400, 20, BLACK);
			}
		}
		if (EQUAL_LESS) {
			if (num1 = num2 || num1 < num2) {
				DrawText(TextFormat("%lf =< %lf = %f", num1, num2, answer), 700, 400, 20, BLACK);
			}
			if (num2 = num1 || num2 < num1) {
				DrawText(TextFormat("%lf =< %lf = %f", num2, num1, answer), 700, 400, 20, BLACK);
			}
		}
		if (EQUAL_GREATER) {
			if (num1 = num2 || num1 > num1) {
				DrawText(TextFormat("%lf => %lf = %f", num1, num2, answer), 700, 400, 20, BLACK);
			}
			if (num2 = num1 || num2 > num1) {
				DrawText(TextFormat("%lf => %lf = %f", num2, num1, answer), 700, 400, 20, BLACK);
			}
		}

		double num;
		double exp;

		if (SQ) DrawText(TextFormat("%lf^2 = %f", num, num, squared_ans), 700, 400, 20, BLACK);
		if (CUBED) DrawText(TextFormat("%lf^3 = %f", num, cubed_ans), 700, 400, 20, BLACK);
		if (EXPO) DrawText(TextFormat("%lf^%lf", pow(num, exp)), 700, 400, 20, BLACK);
		if (SQR) DrawText(TextFormat("sq(%lf) = %f", sqrt(num), sq_root_ans), 700, 400, 20, BLACK);
		if (PI_ANS) DrawText(TextFormat("pi * %lf", PI*num), 700, 400, 20, BLACK);
		if (TAN) DrawText(TextFormat("tan(%lf) = %f", tan(num) = answer), 700, 400, 20, BLACK);
		if (SIN) DrawText(TextFormat("sin(%lf) = %f", sin(num)) = answer, 700, 400, 20, BLACK);
		if (COS) DrawText(TextFormat("cos(%lf) = %f", cos(num) = answer), 700, 400, 20, BLACK);
		if (NEG_TAN) DrawText(TextFormat("-tan(%lf) = %f", -tan(num) = answer), 700, 400, 20, BLACK);
		if (NEG_SIN) DrawText(TextFormat("-sin(%lf) = %f", -sin(num) = answer), 700, 400, 20, BLACK);
		if (NEG_COS) DrawText(TextFormat("-cos(%lf) = %f", -cos(num) = answer), 700, 400, 20, BLACK);
		if (ANS) DrawText(TextFormat("%f = %f", answer), 700, 400, 20, BLACK);
		if (ABS) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (LOG) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (FRAC) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (COMMA) DrawText(TextFormat(" , "), 700, 400, 20, BLACK);
		if (DECIMAL) DrawText(TextFormat(" . "), 700, 400, 20, BLACK);
		if (IN) DrawText(TextFormat("In(%lf) = %f", num, answer), 700, 400, 20, BLACK);
		if (EXP) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (LOG) DrawText(TextFormat("Log(%lf) = %f", num, answer), 700, 400, 20, BLACK);
		if (MAX) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (MIN) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (LIM) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (DET) DrawText(TextFormat(""), 700, 400, 20, BLACK);
		if (MOD) DrawText(TextFormat(""), 700, 400, 20, BLACK);

		if (X) DrawText(TextFormat("X", x), 700, 400, 20, BLACK);
		if (Y) DrawText(TextFormat("Y", y), 700, 400, 20, BLACK);
		
		if (answer) { 
			DrawText(TextFormat("%f = %f", answer = answer), 700, 400, 20, BLACK);
		} else {
			answer = num;
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
	if(IsKeyPressed(KEY_ESCAPE)) CloseWindow();
	}
	UnloadTexture(multiply);
	UnloadTexture(divide);
	UnloadTexture(sub);
	UnloadTexture(add);
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

	UnloadTexture(x_button);
	UnloadTexture(y_button);
	UnloadTexture(y_equals);
	UnloadTexture(table);
	UnloadTexture(graph);
	UnloadTexture(trace);
	UnloadTexture(cot);

	UnloadTexture(exponent);
	UnloadTexture(cubed);
	UnloadTexture(squared);
	UnloadTexture(e_button);
	UnloadTexture(pi);
	UnloadTexture(del);
	UnloadTexture(clear);
	UnloadTexture(sqr);
	UnloadTexture(neg);
	UnloadTexture(sin_button);
	UnloadTexture(cos_button);
	UnloadTexture(tan_button);
	UnloadTexture(neg_tan);
	UnloadTexture(neg_cos);
	UnloadTexture(neg_sin);
	UnloadTexture(left_brak);
	UnloadTexture(right_brak);
	UnloadTexture(decimal);
	UnloadTexture(comma);
	UnloadTexture(log);
	UnloadTexture(abs);
	UnloadTexture(ans);
	UnloadTexture(in);
	UnloadTexture(exp);
	UnloadTexture(max);
	UnloadTexture(min);
	UnloadTexture(mod);
	UnloadTexture(lim);
	UnloadTexture(det);

	CloseWindow();

	return 0;
}

