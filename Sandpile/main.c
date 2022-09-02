#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void populate_grid(int grid[23][23]) {
    int i, j;
    for (i = 0; i < 23; i++) {
        for (j = 0; j < 23; j++) {
            grid[i][j] = 0;
        }
    }
}

int check_center_sink(int row, int col, int height) {
    if (row == 11 && col == 11 && height == -1) {return 1;}
    return 0;
}


void print_grid(int grid[23][23]) {
    int i, j;
    for (i = 0; i < 23; i++) {
        for (j = 0; j < 23; j++) {
            if (grid[i][j] == -1) {
                printf("%s ", "#");
            } else {
                printf("%d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void populate_neighbors(int grid[23][23], int row, int col) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int x = row + i;
            int y = col + j;
            if (x < 0 || x > 22 || y < 0 || y > 22 || grid[x][y] == -1 || (i == 0 && j == 0)) {
                continue;
            }
            grid[row + i][col + j] += 1;
        }
    }
}

void sand_topple(int grid[23][23]) {
    int i, j, z;
    z = 1;
    while (z) {
        z = 0;
        for (i = 0; i < 23; i++) {
            for (j = 0; j < 23; j++) {
                if (grid[i][j] > 8) {
                    grid[i][j] -= 8;
                    populate_neighbors(grid, i, j);
                    z = 1;
                }
            }
    }
    }

}

int main(int argc, char *argv[]) {
    int grid[23][23];
    populate_grid(grid);
    int i, j , row, col, height;
    j = 1;
    i = 1;
    int mSeconds = 1000000;
    while (i < argc) {
        if (strcmp(argv[i], "--fps") == 0) {
            sscanf(argv[i+1], "%d", &mSeconds);
            i +=2;
            mSeconds = 1000000 / mSeconds;
            if (argc == 3) {
                break;
            }
        }
        sscanf(argv[i], "%d", &row);
        sscanf(argv[i+1], "%d", &col);
        sscanf(argv[i+2], "%d", &height);

        if (check_center_sink(row, col, height)) {
            printf("Sink cannot be in the center");
            j = 0;
            break;
        }
        grid[row][col] = height;
        i += 3;
    }
    if (j) {
        print_grid(grid);
    }

    i = 0;
    while (j) { 
        // unsigned int mSeconds = 1000000;
        int returnCode;

        returnCode = usleep(mSeconds);
        grid[11][11] += 1;        
        
        sand_topple(grid);
        print_grid(grid);
        i += 1;
    }
    return 0;
}