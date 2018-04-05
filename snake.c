// gcc -o snake snake.c -lncurses

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>

#include "llist.h"

#define DELAY 100000

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

void quit(void);

int main(int argc, char** argv)
{
	initscr();
	noecho();     /* Don't echo keypresses           */
	curs_set(0);  /* Don't display the cursor        */
	cbreak();     /* Don't wait for CR to take input */
	timeout(1); /* ms to wait for user input */
	// nodelay(stdscr, false);

	enum Direction dir = RIGHT;
	LList* snake = llist_new((uint8_t[]){ 10, 10 });
	llist_push(snake, (uint8_t[]){ 11, 10 });
	llist_push(snake, (uint8_t[]){ 12, 10 });

	int c = 0;
	while (true) {
		clear();

		c = getch();
		switch (c) {
			case 'q': quit();
			case 's': dir = DOWN;  break;
			case 'w': dir = UP;    break;
			case 'd': dir = RIGHT; break;
			case 'a': dir = LEFT;  break;
		}
		for (struct Node* n = snake; n->next; n = n->next) {
			switch (dir) {
				case RIGHT: n->data[0] += 1; break;
				case LEFT : n->data[0] -= 1; break;
				case UP   : n->data[1] -= 1; break;
				case DOWN : n->data[1] += 1; break;
			}
			mvprintw(n->data[1], n->data[0], "o");
		}

		refresh();
		usleep(DELAY);
	}

	return 0;
}

void quit()
{
	endwin();
	exit(0);
}
