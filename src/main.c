#include <stdio.h>
#include <string.h>

#include "array_functions.h"

typedef enum{false, true} bool;


int ceiling(const int x, const int div) {
	return (x + div - 1) / div;
}

void initialiseMaze(const int height, const int width, int maze[height][width], const int gap) {

	const int step = gap + 1;
	const int mid = ceiling(height - 1, 2);		//middle height (i) index

	const int prev_lims = ceiling(mid, step);
	int prev_start_lims[prev_lims];
	int prev_end_lims[prev_lims];
	memset(prev_start_lims, 0, prev_lims*sizeof(int));
	memset(prev_end_lims, 0, prev_lims*sizeof(int));

	int start_lim = 0;
	int end_lim = width - 1;

	int i;
	for(i = 0; i <= mid; i++) {
		if(i % step == 0) {
			for(int j = 0; j < width; j++) {
				maze[i][j] = (start_lim <= j && j <= end_lim)
						|| inArray(j, prev_lims, prev_start_lims)
						|| inArray(j, prev_lims, prev_end_lims)
						? 1 : 0;
			}

			prev_start_lims[i / step] = start_lim;
			prev_end_lims[i / step] = end_lim;
			start_lim += step;
			end_lim -= step;
		} else {
			for(int j = 0; j < width; j++) {
				maze[i][j] = inArray(j, prev_lims, prev_start_lims)
						|| inArray(j, prev_lims, prev_end_lims) 
						? 1 : 0;
			}
		}
	}
	start_lim -= step;
	end_lim += step;

	for(/*i*/; i < height; i++) {
		if(i % step == 0) {
			for(int j = 0; j < width; j++) {
				maze[i][j] = (start_lim <= j && j <= end_lim)
						|| inArray(j, prev_lims, prev_start_lims)
						|| inArray(j, prev_lims, prev_end_lims)
						? 1 : 0;
			}

			int desc_lims_index = (prev_lims - 1) - ((i / step) - prev_lims);
			prev_start_lims[desc_lims_index] = 0;
			prev_end_lims[desc_lims_index] = 0;
			start_lim -= step;
			end_lim += step;
		} else {
			for(int j = 0; j < width; j++) {
				maze[i][j] = inArray(j, prev_lims, prev_start_lims)
						|| inArray(j, prev_lims, prev_end_lims) 
						? 1 : 0;
			}
		}
	}

}

void printMaze(int height, int width, int maze[height][width]) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(maze[i][j] == 1) {
				if((j != 0 && maze[i][j - 1] == 1) || (j != width - 1 && maze[i][j + 1] == 1)) {
					printf("-");
				} else {
					printf("|");
				}
			} else {
				printf(".");
			}
		}	
		printf("\n");
	}
}

int getUnsignedIntegerInput(const char* string) {
	int input;
	printf("%s", string);
	scanf("%d", &input);
	if(input < 0) {
		printf("Bad input, try again...\n");
		return getUnsignedIntegerInput(string);
	}
	return input;
}

int roundUpToNearestMazeSeqTerm(const int x, const int gap) {		//a(n) = (2*gap + 2)n - gap
	return (x + gap) % (2 * gap + 2)? roundUpToNearestMazeSeqTerm(x + 1, gap): x;
}

int main() {

	printf("Enter Maze Dimensions (heigth & width will be rounded to appropriate integers)...\n");
	const unsigned int gap = getUnsignedIntegerInput("Path Width: ");
	const unsigned int height = roundUpToNearestMazeSeqTerm(getUnsignedIntegerInput("Maze Height: "), gap);
	const unsigned int width = roundUpToNearestMazeSeqTerm(getUnsignedIntegerInput("Maze Width: "), gap);
	printf("\nGenerating Maze[%d][%d] with %d wide paths...\n\n", height, width, gap);

	int maze[height][width];

	initialiseMaze(height, width, maze, gap);
	print2dArray(height, width, maze);
	printf("\n\n");
	printMaze(height, width, maze);

}
