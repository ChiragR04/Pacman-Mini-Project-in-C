#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // For kbhit() and getch()
#include <windows.h> // For Sleep()

#define H 100   // Playfield height
#define W 100  // Playfield width

char playfield[H][W] = {
    "****************************************",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "* .................................... *",
    "****************************************"
};

int food_collect = 0, game_end = 0;
int py = 1, px = 1;   // Pacman coordinates
int gy1 = 1, gx1 = W-2, gy2 = H-2, gx2 = 1;  // Ghost coordinates

void game_result() {
    printf("\n\n\n\n\n\n\n\n\n");
    if (food_collect == 500) {
        printf("\t\t\t       Congratulations!!\n");
        printf("\t\t\t     You won the game!!\n");
    } else {
        printf("\t\t\t        Better luck next time!!\n");
        printf("\t\t\t  You lost the game!!\n");
    }
    printf("\t\t\t Your total score is %d\n", food_collect);
}

void move_ghosts() {
    if (gy1 == 1 && gx1 > 1) {
        gx1--;   // Move 1st ghost left
    } else if (gx1 == 1 && gy1 < 7) {
        gy1++;   // Move 1st ghost down
    } else if (gy1 == 7 && gx1 < W-2) {
        gx1++;   // Move 1st ghost right
    } else if (gx1 == W-2 && gy1 > 1) {
        gy1--;   // Move 1st ghost up
    }

    if (gy2 == H-2 && gx2 < W-2) {
        gx2++;  // Move 2nd ghost right
    } else if (gx2 == W-2 && gy2 > 7) {
        gy2--;  // Move 2nd ghost up
    } else if (gy2 == 7 && gx2 > 1) {
        gx2--;  // Move 2nd ghost left
    } else if (gx2 == 1 && gy2 < H-2) {
        gy2++;  // Move 2nd ghost down
    }
}

void user_input() {
    // Wait for user input with non-blocking kbhit()
    if (kbhit()) {
        char c1 = getch();
        switch (c1) {
            case 'w': py -= 1; break;  // Move up
            case 's': py += 1; break;  // Move down
            case 'a': px -= 1; break;  // Move left
            case 'd': px += 1; break;  // Move right
        }
    }

    // Ensure Pacman doesn't go out of bounds
    if (py < 1) py = 1;
    if (px < 1) px = 1;
    if (py > H-2) py = H-2;
    if (px > W-2) px = W-2;
}

void setup() {
    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            if (playfield[i][j] == '#') {
                playfield[i][j] = ' ';
            }
            if (playfield[i][j] == '@') {
                playfield[i][j] = '.';
            }
        }
    }

    // Check if Pacman is collecting food
    if (playfield[py][px] == '.') {
        food_collect++;
        playfield[py][px] = ' ';  // Remove the food once collected
    }

    playfield[py][px] = '#';  // Mark Pacman's position
    playfield[gy1][gx1] = '@';  // Mark ghost 1
    playfield[gy2][gx2] = '@';  // Mark ghost 2

    // Check if Pacman has collided with ghosts
    if ((py == gy1 && px == gx1) || (py == gy2 && px == gx2)) {
        game_end = 1;  // End game if collision occurs
    }

    // End the game if food collect limit is reached
    if (food_collect >= 500) {
        game_end = 1;  // End game if all food is collected
    }
}

void draw_playfield() {
    int i, j;
    printf("\n\n\n\n");
    for (i = 0; i < H; i++) {
        printf("\t\t");
        for (j = 0; j < W; j++) {
            printf("%c", playfield[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", food_collect);
}

int main() {
    // Game starts here
    while (!game_end) {  // Loop until the game ends
        setup();         // Set up the game
        draw_playfield(); // Draw the playfield
        user_input();    // Wait for user input
        move_ghosts();   // Move ghosts
        Sleep(200);      // Pause for 200 milliseconds
    }
    game_result();       // Show result when game ends
    return 0;
}


