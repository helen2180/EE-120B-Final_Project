#ifndef SCREENS_H_
#define SCREENS_H_

// Nokia 5110 screen functions
void title_screen();
void game_over_screen ();
void win_screen ();
void play_again_screen();

void demo_init();
void demo_up();
void demo_down();
void demo_left();
void demo_right();

void play_init();
void play_up();
void play_down();
void play_left();
void play_right();


void title_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 0);
	nokia_lcd_write_string("Just", 2);
	nokia_lcd_set_cursor(15, 15);
	nokia_lcd_write_string("Dance", 2);
	nokia_lcd_set_cursor(12, 35);
	nokia_lcd_write_string("Revolution", 1);
	nokia_lcd_render();
}

void demo_init() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_render();
}

void demo_up() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(28, 20);
	nokia_lcd_write_string("Up", 3);
	nokia_lcd_render();
}

void demo_down() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Down", 3);
	nokia_lcd_render();
}

void demo_left() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Left", 3);
	nokia_lcd_render();
}

void demo_right() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(2, 20);
	nokia_lcd_write_string("Right", 3);
	nokia_lcd_render();
}

void play_init() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_render();
}

void play_up() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(28, 20);
	nokia_lcd_write_string("Up", 3);
	nokia_lcd_render();
}

void play_down() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Down", 3);
	nokia_lcd_render();
}

void play_left() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Left", 3);
	nokia_lcd_render();
}

void play_right() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(2, 20);
	nokia_lcd_write_string("Right", 3);
	nokia_lcd_render();
}

void game_over_screen () {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 5);
	nokia_lcd_write_string("Game", 2);
	nokia_lcd_set_cursor(20, 25);
	nokia_lcd_write_string("Over", 2);
	nokia_lcd_render();
}

void win_screen () {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(27, 5);
	nokia_lcd_write_string("You", 2);
	nokia_lcd_set_cursor(24, 25);
	nokia_lcd_write_string("Win!", 2);
	nokia_lcd_render();
}

void play_again_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 5);
	nokia_lcd_write_string("Play", 2);
	nokia_lcd_set_cursor(10, 25);
	nokia_lcd_write_string("Again?", 2);
	nokia_lcd_render();
}

void correct_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(5, 15);
	nokia_lcd_write_string("Correct", 2);
	nokia_lcd_render();
}

void error_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(15, 15);
	nokia_lcd_write_string("Error", 2);
	nokia_lcd_render();
}


#endif /* SCREENS_H_ */