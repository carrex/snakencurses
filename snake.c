// gcc -std=gnu99 -Wall -o snake snake.c -lncurses && ./snake

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "llist.h"

#define DELAY 100000

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

static void gen_food(short* food);
void quit(void);

short maxx;
short maxy;

int main(int argc, char** argv)
{
	initscr();
	getmaxyx(stdscr, maxy, maxx);
	noecho();    /* Don't echo keypresses           */
	curs_set(0); /* Don't display the cursor        */
	cbreak();    /* Don't wait for CR to take input */
	timeout(50); /* ms to wait for user input       */

	enum Direction dir = RIGHT;
	LList snake = llist_new((short[]){ 10, 10 });
	llist_push(snake, (short[]){ 9, 10 });
	llist_push(snake, (short[]){ 8, 10 });
	llist_push(snake, (short[]){ 7, 10 });
	llist_push(snake, (short[]){ 6, 10 });

	short food[] = { -1, 0 };
	gen_food(food);
	// while(1);

	short px, py;
	int c = 0;
	while (1) {
		clear();

		c = getch();
		switch (c) {
			case 'q': quit();
			case 'w': dir == RIGHT || dir == LEFT? dir = UP   : dir; break;
			case 's': dir == RIGHT || dir == LEFT? dir = DOWN : dir; break;
			case 'd': dir == UP    || dir == DOWN? dir = RIGHT: dir; break;
			case 'a': dir == UP    || dir == DOWN? dir = LEFT : dir; break;
		}

		/* Messy movement code */
		px = snake->data[0];
		py = snake->data[1];
		for (struct Node* n = snake; n; n = n->next) {
			if (px == food[0] && py == food[1]) {
				llist_insert(snake, (short[]){ px, py }, 1);
				gen_food(food);
				break;
			}
			if (n->next) {
				short tmpx = n->next->data[0];
				short tmpy = n->next->data[1];
				n->next->data[0] = px;
				n->next->data[1] = py;
				px = tmpx;
				py = tmpy;
			}
		}
		switch (dir) {
			case RIGHT: snake->data[0] += 1; break;
			case LEFT : snake->data[0] -= 1; break;
			case UP   : snake->data[1] -= 1; break;
			case DOWN : snake->data[1] += 1; break;
		}

		/* Draw the snake */
		int i = 0;
		for (struct Node* n = snake; n; n = n->next, i++) {
			mvprintw(n->data[1], n->data[0], "o");
			mvprintw(i, 0, "%d:%d", n->data[1], n->data[0]);
		}
		mvprintw(food[1], food[0], "*");

		refresh();
		usleep(DELAY);
	}

	return 0;
}

static void gen_food(short* food)
{
	time_t* t = 0;
	srand((unsigned int)time(t));
	food[0] = (short)(rand() % maxx);
	food[1] = (short)(rand() % maxy);
}

void quit()
{
	endwin();
	exit(0);
}
