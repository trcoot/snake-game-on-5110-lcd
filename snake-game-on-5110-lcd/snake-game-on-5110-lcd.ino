/**========================================================================
 * ?                              ABOUT
 * @author         :  trcoot@github
 * @email          :  jojokagami@gmail.com
 * @description    :  Snake Game on 5110 LCD with Arduino UNO
 *========================================================================**/

// a simple header written by myself
// this header is written for driving the 5110 LCD
// game bitmap inside
#include "lcd_5110_driver.h"

// MAP_ROWS: the rows of the game world
// MAP_J: the coloums of the game world
// SNAKE_SPEED: the interval of the snake moving into the next block
#define MAP_ROWS		  6
#define MAP_COLS		  10
#define SNAKE_SPEED		  200
#define JOYSTICK_X_PIN	  A0
#define JOYSTICK_Y_PIN	  A1
#define CLK_PIN			  7
#define DIN_PIN			  6
#define DC_PIN			  5
#define CE_PIN			  4
#define RST_PIN			  3
#define GAME_OVER_DELAY	  4000
#define WELCOME_IMG_DELAY 4000

// (CLK, DIN, D/C, CE, RST);
Lcd_5110_Display display =
	Lcd_5110_Display(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);

/**=======================
 * !     WARNING
 *   global variables
 *======================**/

// define the things in the game world
enum snake_game {
	body_up,
	body_up_left,
	body_left_up,
	body_left,
	body_left_down,
	body_down_left,
	body_down,
	body_down_right,
	body_right_down,
	body_right,
	body_up_right,
	body_right_up,
	food,
	empty
};

// define the direction from game input(JoyStick)
enum cmd_direction { cmd_up, cmd_left, cmd_down, cmd_right };

// the whole game world will be present in this array
int game_world[MAP_ROWS][MAP_COLS];

// the command which controls the direction of the snake
// the command has only 4 condition: up, down, left and right
// in this project, the game_cmd will be generate from the joystick
int game_cmd;

int snake_length, head_i, head_j, tail_i, tail_j;

bool game_over = false;

/*========= end of global variables=========*/

// this function helps us combine the direction
int bodyDireComb(int prio, int rear) {
	switch (prio) {
	case body_up:
		switch (rear) {
		case body_left: return body_up_left;
		case body_right: return body_up_right;
		default: return prio;
		}
	case body_left:
		switch (rear) {
		case body_up: return body_left_up;
		case body_down: return body_left_down;
		default: return prio;
		}
	case body_down:
		switch (rear) {
		case body_left: return body_down_left;
		case body_right: return body_down_right;
		default: return prio;
		}
	case body_right:
		switch (rear) {
		case body_up: return body_right_up;
		case body_down: return body_right_down;
		default: return prio;
		}
	}
}

// get another direciton from a mixed direction
int bodyDireExce(int mix_dire, int dire) {
	switch (mix_dire) {

	case body_up_left:
	case body_left_up:
		if (dire == body_up) return body_left;
		else return body_up;

	case body_left_down:
	case body_down_left:
		if (dire == body_left) return body_down;
		else return body_left;

	case body_down_right:
	case body_right_down:
		if (dire == body_down) return body_right;
		else return body_down;

	case body_right_up:
	case body_up_right:
		if (dire == body_right) return body_up;
		else return body_right;

	default: return dire;
	}
}

// reset the game
void gameReset() {
	// clear the game world
	for (int i = 0; i < MAP_ROWS; i++)
		for (int j = 0; j < MAP_COLS; j++)
			game_world[i][j] = empty;

	// initialize the game world
	game_world[2][3] = body_left;
	game_world[2][4] = body_left;
	game_world[2][5] = body_left;
	game_world[4][7] = food;

	// the default direction of the snake is left
	game_cmd = cmd_left;

	// mark the position of the head and tail
	head_i		 = 2;
	head_j		 = 3;
	tail_i		 = 2;
	tail_j		 = 5;
	snake_length = 3;
	game_over	 = false;
}

// get the snake game-input
void getGameInput() {
	int pre_cmd	   = game_cmd;
	long timestamp = millis();

	while (millis() < timestamp + SNAKE_SPEED) {
		// determine the direction of the snake
		analogRead(JOYSTICK_Y_PIN) < 400 ? game_cmd = cmd_left : 0;
		analogRead(JOYSTICK_Y_PIN) > 600 ? game_cmd = cmd_right : 0;
		analogRead(JOYSTICK_X_PIN) < 400 ? game_cmd = cmd_down : 0;
		analogRead(JOYSTICK_X_PIN) > 600 ? game_cmd = cmd_up : 0;

		// ignore directional change by 180 degrees
		game_cmd + 2 == pre_cmd ? game_cmd = pre_cmd : 0;
		game_cmd - 2 == pre_cmd ? game_cmd = pre_cmd : 0;
	}
}

void updateHead(int new_i, int new_j) {
	// generate new head
	game_world[new_i][new_j] = 3 * game_cmd;
	// update old head
	game_world[head_i][head_j] =
		bodyDireComb(game_world[head_i][head_j], 3 * game_cmd);
	// update the position of the head
	head_i = new_i;
	head_j = new_j;
}

void updateTail() {
	// update the position of the tail
	int old_tail = game_world[tail_i][tail_j]; // save the old tail
	game_world[tail_i][tail_j] = empty;		   // clean the old tail
	switch (old_tail) {
	case body_up: tail_i = (MAP_ROWS + tail_i - 1) % MAP_ROWS; break;
	case body_left: tail_j = (MAP_COLS + tail_j - 1) % MAP_COLS; break;
	case body_down: tail_i = (MAP_ROWS + tail_i + 1) % MAP_ROWS; break;
	case body_right: tail_j = (MAP_COLS + tail_j + 1) % MAP_COLS; break;
	}
	// update the old tail
	game_world[tail_i][tail_j] =
		bodyDireExce(game_world[tail_i][tail_j], old_tail);
}

// update the game-world
void updateGameWorld() {
	// get the position of the block where the snake's head will move in
	int next_block_i, next_block_j;
	switch (game_cmd) {
	case cmd_up:
		next_block_i = (MAP_ROWS + head_i - 1) % MAP_ROWS;
		next_block_j = head_j;
		break;
	case cmd_down:
		next_block_i = (MAP_ROWS + head_i + 1) % MAP_ROWS;
		next_block_j = head_j;
		break;
	case cmd_left:
		next_block_i = head_i;
		next_block_j = (MAP_COLS + head_j - 1) % MAP_COLS;
		break;
	case cmd_right:
		next_block_i = head_i;
		next_block_j = (MAP_COLS + head_j + 1) % MAP_COLS;
		break;
	}

	// according to the block, generate the new game world
	int next_block = game_world[next_block_i][next_block_j];
	switch (next_block) {

	// if the next block is food
	case food:
		updateHead(next_block_i, next_block_j);

		// generate the new food
		int new_food_i, new_food_j;
		do {
			new_food_i = random(0, MAP_ROWS);
			new_food_j = random(0, MAP_COLS);
		} while (game_world[new_food_i][new_food_j] != empty);
		game_world[new_food_i][new_food_j] = food;
		snake_length++;
		break;

	// if the next block is empty
	case empty:
		updateHead(next_block_i, next_block_j);
		updateTail();
		break;

	// if the next block is snake's body
	default:
		// update the tail first, then update the head.
		// the tail is a part of body, but the snake can't bite
		// the tail.
		if (next_block_i == tail_i && next_block_j == tail_j) {
			updateTail();
			updateHead(next_block_i, next_block_j);
			break;
		}
		updateHead(next_block_i, next_block_j);
		game_over = true;
		break;
	}
}

// generate the sanke game-output
void generateGameOutput() {
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			// translate the things in game world to the number of bitmap
			int bitmap_num;
			switch (game_world[i][j]) {
			case body_up:
			case body_down: bitmap_num = 0; break;
			case body_left:
			case body_right: bitmap_num = 1; break;
			case body_down_left:
			case body_right_up: bitmap_num = 7; break;
			case body_left_up:
			case body_down_right: bitmap_num = 4; break;
			case body_right_down:
			case body_up_left: bitmap_num = 5; break;
			case body_up_right:
			case body_left_down: bitmap_num = 6; break;
			case food: bitmap_num = 8; break;
			case empty: bitmap_num = 9; break;
			}
			if (i == head_i && j == head_j)
				bitmap_num = game_world[i][j] / 3 + 14;
			if (i == tail_i && j == tail_j)
				bitmap_num = game_world[i][j] / 3 + 10;
			display.printBlock(bitmap_num);
		}
		display.drawDummy();
	}
}

void setup() {
	// if analog input pin 5 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function. from
	// https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
	randomSeed(analogRead(5));
	// reset the game
	gameReset();
	display.initDisplay();
	display.showImg();
	delay(WELCOME_IMG_DELAY);
	generateGameOutput();
}

void loop() {
	if (game_over == true) {
		delay(GAME_OVER_DELAY);
		gameReset();
	}
	getGameInput();
	updateGameWorld();
	generateGameOutput();
}
