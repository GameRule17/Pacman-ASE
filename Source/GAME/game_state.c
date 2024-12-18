#import "game_state.h"

/* **************************** FUNCTION PROTOTYPES **************************** */
void setGamePause();
void removeGamePause();
void restartGame();
void updateCountdown();
void updateScoreAndCheckVictory(int addValue);

/* **************************** GLOBAL VARIABLES **************************** */

int countdown = MAX_TIME_SECONDS;
int num_lifes = INITIAL_NUM_LIFES;
int score = 0;
int threshold = 1000;
int game_pause = 1;
int num_eated_pills = 0;

/* ******************** GAME STATE FUNCTIONS ******************** */

void setGamePause() {
	game_pause = 1;
	drawPauseBox();
	disable_timer(0);
	disable_timer(1);
}

void removeGamePause() {
	game_pause = 0;
	drawBoard(0);
	enable_timer(0);
	enable_timer(1);
}

void restartGame() {
	clearGameOverScreen();
	drawBoard(1);
	setGamePause();
	enableINT0();
	countdown = MAX_TIME_SECONDS; // Reset countdown statistic
	drawTimeLeft();
}

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		disable_timer(0);
		disable_timer(1);
		num_lifes--;
		if(num_lifes == -1) {
			disable_RIT(); // Disable using all types of buttons
			drawGameEndedScreen(); // Game ended with no more lives left
		} else {
			disableINT0(); // No sense of pausing the game in game over screen
			enableKEY1(); // Make possible to click KEY1 to restart the game
			drawGameOverScreen(); // Game ended with at least 1 life left
		}
	} else {
		drawTimeLeft();
	}
}

void updateScoreAndCheckVictory(int addValue) {
	score = score + addValue;
	
	// To manage adding a new life every 1000 points obtained
	if (score >= threshold) {
		num_lifes = num_lifes + 1;
		drawLives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		threshold = threshold + 1000;
	}
	
	// Check Victory
	num_eated_pills++;
	if (num_eated_pills == MAX_NUM_PILLS) {
		game_pause = 1;
		disable_timer(0);
		disable_timer(1);
		disable_RIT(); // Disable using all types of buttons
		drawVictoryScreen();
	}
}

