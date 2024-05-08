#include "raylib.h"
#define MAX_INPUT_CHARS     20

bool start = true;
bool calc = false;
bool graph = false;

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "");

    char name[MAX_INPUT_CHARS + 1] = "\0";
    char value;
    int letterCount = 0;

    Rectangle textBox = { screenWidth/4.0f - 190, 180, 325, 50 };
    Rectangle start_graph = { screenWidth/2.0f, screenHeight/2.0f, 300, 100 };
    bool mouseOnText = false;
    bool result = false;

    int framesCounter = 0;

    SetTargetFPS(10);
    while (!WindowShouldClose()) {
        if (start == true) {
            if (IsKeyReleased(KEY_ENTER)) {
                start = false;
                calc = true;
            }
        }
        if (calc == true) {
            if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
                mouseOnText = true;
            } else mouseOnText = false;

            if (mouseOnText) {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
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
                if (IsKeyPressed(KEY_ENTER)) {
                    letterCount = 0;
                    result = true;
                }
            } else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (mouseOnText) {
                framesCounter++;
            } else framesCounter = 0;

            if (IsKeyReleased(KEY_G)) {
                calc = false;
                graph = true;
            }
            if (graph == true) {
                system(python line.py);
            }
        }

        if (graph == true) {
            if (IsKeyReleased(KEY_C)) {
                graph = false;
                calc = true;
            }
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (start == true) {
                DrawText("press enter to start", 300, 200, 30, BLACK);
            }

            if (calc == true) {

                DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

                DrawRectangleRec(textBox, LIGHTGRAY);
                if (mouseOnText) {
                    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
                } else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

                DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

                DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

                if (mouseOnText) {
                    if (letterCount < MAX_INPUT_CHARS) {
                        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                    }
                    else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
                }
                if (result == true) DrawText(TextFormat("result %f", value), screenWidth, screenHight, 20, BLACK);
            }

            if (graph == true) {
                DrawText("press C to go back to calculator mode", 50, 200, 30, BLACK);
                DrawRectangleRec(start_graph, Black);
                DrawText("start", (int)start_graph.x, (int)start_graph.y, 100, 20, 20);
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

bool IsAnyKeyPressed() {
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
