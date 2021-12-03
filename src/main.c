#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void generateMazeWalls(const int path, int walls[]) {
	walls[0] = rand() % 2;
	for(int w = 1; w < path; w++) {
		walls[w] = walls[w - 1] == 1? 0: rand() % 2;
	}
}

void addMazeWalls(const int height, const int width, int maze[height][width], const int gap) {

	const int mid_height = ceiling(height - 1, 2);
	const int step = gap + 1;

	srand(time(NULL));		//will need random numbers, init srand before loop
	int length = width;
	for(int i = 1; i < mid_height; i += step) {		//start after outer wall and jump to after next wall until at middle
		const int path = length - 2 - 2 * gap;
		if(path > 0) {
			int walls_top[path];
			int walls_bot[path];
			memset(walls_top, 0, path*sizeof(int));
			memset(walls_bot, 0, path*sizeof(int));
			generateMazeWalls(path, walls_top);
			generateMazeWalls(path, walls_bot);
			for(int j = i + step; j < width - (i + step); j++) {
				int k = i;
				while(k < i + gap) {
					maze[k++][j] = walls_top[j - (i + step)];
				}
				k = height - i - 1;		//inverse
				while(k > (height - i - 1) - gap) {
					maze[k--][j] = walls_bot[j - (i + step)];
				}


			}
			length = path;
		}
	}

	const int mid_width = ceiling(width - 1, 2);		
	length = height;
	for(int j = 1; j < mid_width; j += step) {
		const int path = length - 2 - 2 * gap;
		if(path > 0) {
			int walls_left[path];
			int walls_right[path];
			memset(walls_left, 0, path*sizeof(int));
			memset(walls_right, 0, path*sizeof(int));
			generateMazeWalls(path, walls_left);
			generateMazeWalls(path, walls_right);
			for(int i = j + step; i < height - (j + step); i++) {
				int k = j;
				while(k < j + gap) {
					maze[i][k++] = walls_left[i - (j + step)];
				}
				k = width - j - 1;		//inverse
				while(k > (width - j - 1) - gap) {
					maze[i][k--] = walls_right[i - (j + step)];
				}


			}
			length = path;
		}
	}

}

void printMaze(const int height, const int width, const int maze[height][width], const int gap) {
//	print2dArray(height, width, maze);
//	printf("\n\n");

	int step = gap + 1;

	int mid_h = ceiling(height, 2);
	int mid_w = ceiling(width, 2);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(maze[i][j] == 1) {

					double i_prop = (double) i / (double) height;
					double j_prop = (double) j / (double) width;

					double i_inv = (double) (height - 1 - i) / (double) height;
					double j_inv = (double) (width - 1 - j) / (double) width;

					if(i < mid_h) {
						if(j < mid_w) {
							if(i_prop < j_prop) {
								if(i % step == 0) {
									printf("-");
								} else {
									printf("|");
								}
							} else if(i_prop > j_prop) {
								if(j % step == 0) {
									printf("|");
								} else {
									printf("-");
								}
							} else {
								printf("+");
							}
						} else if(j >= mid_w) {
							if(i_prop < j_inv) {
								if(i % step == 0) {
									printf("-");
								} else {
									printf("|");
								}
							} else if(i_prop > j_inv) {
								if(j % step == 0) {
									printf("|");
								} else {
									printf("-");
								}
							} else {
								printf("+");
							}

						} else {
							printf("+");
						}
					} else if(i >= mid_h) {
						if(j < mid_w) {
							if(i_inv < j_prop) {
								if(i % step == 0) {
									printf("-");
								} else {
									printf("|");
								}
							} else if(i_inv > j_prop) {
								if(j % step == 0) {
									printf("|");
								} else {
									printf("-");
								}
							} else {
								printf("+");
							}
						} else if(j >= mid_w) {
							if(i_inv < j_inv) {
								if(i % step == 0) {
									printf("-");
								} else {
									printf("|");
								}
							} else if(i_inv > j_inv) {
								if(j % step == 0) {
									printf("|");
								} else {
									printf("-");
								}
							} else {
								printf("+");
							}

						} else {
							printf("+");
						}
					} else {
						printf("?");
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
	addMazeWalls(height, width, maze, gap);

	printMaze(height, width, maze, gap);

}
