/**
 * Copyright (C) 2022 Richie Seputro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program, named LICENSE.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/** header files **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** macros and symbolic constants **/

/* usage information */
#define USAGE \
	"Usage: %s FILE\n\n" \
	"FILE specification:\n" \
	"\tContains lines with max length of %d characters, including newline\n"
/* max answer word / phrase length, actually minus one NUL */
#define MAXSTRLEN 32
/* x, y dimension for hangman graphics */
#define WIDTH MAXSTRLEN
#define LENGTH MAXSTRLEN / 2
/**
 * hangman string length
 * MAXSTRLEN wide * MAXSTRLEN/2 long + MAXSTRLEN newlines + 1 NUL
 */
#define MAXHANGMMANLEN WIDTH * LENGTH + MAXSTRLEN + 1
/* hangman graphics */
#define HANGMANSTRA \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n" \
	"                                \n"
#define HANGMANSTRB \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"                \\\\        ||    \n" \
	"                  \\\\      ||    \n" \
	"                    \\\\    ||    \n" \
	"                      \\\\  ||    \n" \
	"                        \\\\||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                      ____||____\n"
#define HANGMANSTRC \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"                        \\\\||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                      ____||____\n"
#define HANGMANSTRD \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"     |                  \\\\||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                          ||    \n" \
	"                      ____||____\n"
#define HANGMANSTRE \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"     |                  \\\\||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"    /                     ||    \n" \
	"   /                      ||    \n" \
	"  /                       ||    \n" \
	" /                        ||    \n" \
	"/                     ____||____\n"
#define HANGMANSTRF \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"     |                  \\\\||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"     |                    ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
#define HANGMANSTRG \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    _|                  \\\\||    \n" \
	"   / |                    ||    \n" \
	"  /  |                    ||    \n" \
	" /   |                    ||    \n" \
	"/    |                    ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
#define HANGMANSTRH \
	"     +====================++    \n" \
	"              \\\\          ||    \n" \
	"    ___         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    _|_                 \\\\||    \n" \
	"   / | \\                  ||    \n" \
	"  /  |  \\                 ||    \n" \
	" /   |   \\                ||    \n" \
	"/    |    \\               ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
#define HANGMANSTRI \
	"     +====================++    \n" \
	"     |        \\\\          ||    \n" \
	"    _|_         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  |     |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    _|_                 \\\\||    \n" \
	"   / | \\                  ||    \n" \
	"  /  |  \\                 ||    \n" \
	" /   |   \\                ||    \n" \
	"/    |    \\               ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
#define HANGMANSTRJ \
	"     +====================++    \n" \
	"     |        \\\\          ||    \n" \
	"    _|_         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  | x   |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    _|_                 \\\\||    \n" \
	"   / | \\                  ||    \n" \
	"  /  |  \\                 ||    \n" \
	" /   |   \\                ||    \n" \
	"/    |    \\               ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
#define HANGMANSTRK \
	"     +====================++    \n" \
	"     |        \\\\          ||    \n" \
	"    _|_         \\\\        ||    \n" \
	"   /   \\          \\\\      ||    \n" \
	"  | x x |           \\\\    ||    \n" \
	"   \\___/              \\\\  ||    \n" \
	"    _|_                 \\\\||    \n" \
	"   / | \\                  ||    \n" \
	"  /  |  \\                 ||    \n" \
	" /   |   \\                ||    \n" \
	"/    |    \\               ||    \n" \
	"    /^\\                   ||    \n" \
	"   /   \\                  ||    \n" \
	"  /     \\                 ||    \n" \
	" /       \\                ||    \n" \
	"/         \\           ____||____\n"
/* you can only enter wrong input 10 times! */
#define MAXWRONGS 10
/* the value to be added to score for each correct character */
#define CHARVALUE 50
/* number of characters in alphabet */
#define ALPHABETNUM 26

/** main: program start **/
int
main(int argc, char *argv[])
{
	/**
	 * fp: file pointer
	 * gameover: boolean, controls the game loop
	 * score: tracks user points
	 * found: boolean, true if input is found in answer
	 * wrongcount: number of wrong inputs
	 * correctchars: number of correct chars in a verification sweep
	 * inputmem: A-Z map of user input (26 uppercase characters)
	 * correctlyguessed: boolean, if current word is guessed correctly
	 * cleared: boolean, if current guess word is cleared
	 * i : iterator for loops
	 * input: user input
	 * lastinput: last user input character
	 * answer: guessed word or phrase
	 * display: the currently correct user input
	 * hangman: pointer to hangman "graphic" states made of strings;
	 *          there are 11 states, from nothing at all to dead hanged man
	 */
	FILE *fp;
	int gameover = 0;
	unsigned score = 0;
	int found = 0;
	int wrongcount = 0;
	int correctchars = 0;
	int inputmem[ALPHABETNUM];
	int correctlyguessed;
	int cleared = 1; /* initially set to 1 */
	int i;
	char input;
	char lastinput;
	char answer[MAXSTRLEN];
	char display[MAXSTRLEN];
	char *hangman[MAXWRONGS + 1] = {
		HANGMANSTRA,
		HANGMANSTRB,
		HANGMANSTRC,
		HANGMANSTRD,
		HANGMANSTRE,
		HANGMANSTRF,
		HANGMANSTRG,
		HANGMANSTRH,
		HANGMANSTRI,
		HANGMANSTRJ,
		HANGMANSTRK,
	};

	/* if argc is not 2, print usage and exit with failure code */
	if (argc != 2) {
		fprintf(stderr, USAGE, argv[0], MAXSTRLEN);

		return EXIT_FAILURE;
	}

	/* if failed to open file pointed to by fp, terminate program */
	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ERROR: Failed to open '%s'\n\n", argv[1]);
		fprintf(stderr, USAGE, argv[0], MAXSTRLEN);

		return EXIT_FAILURE;
	}

	/* main game loop */
	while (!gameover) {
		/* assign initial values to vars */
		correctchars = 0;
		found = 0;

		/* if guess word / phrase is cleared */
		if (cleared) {
			/* copy a line from fp as our answer */
			if ((fgets(answer, MAXSTRLEN, fp)) != NULL) {
				/* replace read newline with NUL */
				answer[strcspn(answer, "\n")] = '\0';

				/* convert answer to uppercased chars */
				for (i = 0; answer[i] != '\0'; ++i)
					answer[i] = toupper(answer[i]);
			} else {
				/* we reached the end of file or fgets failed to read */
				gameover = 1;
				break;
			}

			/**
			 * copy answer to display:
			 * if answer[i] is not space, copy it as underscore
			 * else keep it the same
			 */
			for (i = 0; answer[i] != '\0'; ++i)
				display[i] = (answer[i] != ' ') ? '_' : answer[i];
			display[i] = '\0';

			/* fill inputmem with zeroes if current guess word is cleared */
			memset(inputmem, 0, sizeof(inputmem));

			/* reset cleared to 0 */
			cleared = 0;

			/* reset wrongcount to 0 */
			wrongcount = 0;
		}

		/* clear the screen */
#ifdef UNIX
		system("clear");
#else
		system("cls");
#endif

		/* print hangman and display and score and input prompt */
		printf(hangman[wrongcount]);
		fflush(stdout);
		printf("%s\n", display);
		fflush(stdout);
		printf("Score: %d\n", score);
		fflush(stdout);
		printf("INPUT: ");
		fflush(stdout);

		/* assign NUL to lastinput */
		lastinput = '\0';

		/* get user input until newline or EOF */
		while ((input = getchar()) != EOF && input != '\n')
			lastinput = input;

		/* if EOF is encountered, break out of loop */
		if (input == EOF)
			break;

		/* if we got a newline, use lastinput for input, else just use input */
		if (input == '\n')
			input = toupper(lastinput);
		else
			input = toupper(input);

		puts("");
		fflush(stdout);

		/* find if input is in answer */
		for (i = 0; answer[i] != '\0'; ++i) {
			/* if so, change display accordingly and turn the 'found' flag on */
			if (input == answer[i] && input != ' '
                && inputmem[input - 'A'] == 0) {
				display[i] = answer[i];
				correctchars++;
				found = 1;
			}
		}

		/* flag input as already taken */
		if (isupper(input))
			inputmem[input - 'A'] = 1;

		/* compute score */
		score += correctchars * CHARVALUE;

		/* if input is not found, add wrongcount */
		if (found == 0) {
			wrongcount++;
		} else {
			/* assume that answer has been correctly guessed */
			correctlyguessed = 1;

			/* check if answer has been correctly fully guessed */
			for (i = 0; display[i] != '\0'; ++i) {
				/* if not... */
				if (display[i] == '_') {
					correctlyguessed = 0;
					break;
				}
			}

			/* if correctly guessed, that means the current word is cleared */
			if (correctlyguessed)
				cleared = 1;
		}

		/* determine if game will continue or not */
		if (wrongcount >= MAXWRONGS)
			gameover = 1;
	}

	/* close fp */
	fclose(fp);

	/* clear the screen one last time */
#ifdef UNIX
	system("clear");
#else
	system("cls");
#endif

	/* final info */
	printf(hangman[wrongcount]);
	fflush(stdout);
	printf("%s\n", display);
	fflush(stdout);
	printf("GAMEOVER!\nFinal score: %d\n", score);
	fflush(stdout);

	return EXIT_SUCCESS;
}
