gcc main.c pbPlots.c supportLib.c -o main.exe -O1 -Wall -std=c99 -Wno-missing-braces -static -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -ldislin -lm
