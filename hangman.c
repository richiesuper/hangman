#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE \
	"Usage: %s \"WORD|PHRASE\"\n"
#define MAXSTRLEN 16
/* 2 * MAXSTRLEN wide * MAXSTRLEN long + MAXSTRLEN newlines + 1 NUL */
#define MAXHANGMMANLEN 2 * MAXSTRLEN * MAXSTRLEN + MAXSTRLEN + 1
#define HANGMANSTR \
	"     +====================++    \n" \
	"     |        \\\\          ||    \n" \
	"    _|_         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  | x x |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    /|\\                 \\\\||    \n" \
	"   / | \\                  ||    \n" \
	"  /  |  \\                 ||    \n" \
	" /   |   \\                ||    \n" \
	"/    |    \\               ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n" \

int
main(int argc, char *argv[])
{
	/**
	 * gameover: controls the game loop
	 * score: tracks user points
	 * input: user input
	 * answer: guessed word or phrase
	 * hangman: hangman "graphics"
	 */
	int gameover = 0, score = 0;
	char input, answer[MAXSTRLEN], hangman[MAXHANGMMANLEN] = HANGMANSTR;

	if (argc != 2) {
		fprintf(stderr, USAGE, argv[0]);

		return EXIT_FAILURE;
	}

	strncpy(answer, argv[1], MAXSTRLEN - 1);
	answer[MAXSTRLEN - 1] = '\0';

#ifdef UNIX
	system("clear");
#else
	system("cls");
#endif

	while (!gameover && (input = getchar()) != EOF) {
	}

	return EXIT_SUCCESS;
}
