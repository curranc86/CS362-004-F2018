#include "../dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

void compareStates(struct gameState * test, struct gameState * expected);
void assert(int current, int expected, char * name);
void fillGameStateRandom(struct gameState * state);
int randInt(int min, int max);

void cardEffect_smithy(struct gameState* state, int currentPlayer, int handPos);
/*
void cardEffect_smithy(struct gameState* state, int currentPlayer, int handPos) {
	//+3 Cards
	for (int i = 0; i < 3; i++)
	{
		drawCard(handPos, state);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
}
*/

void oracle(struct gameState * state, int currentPlayer, int handPos) {
	// Draw Three cards
	for (int _ = 0; _ < 3; ++_){
		state->hand[currentPlayer][state->handCount[currentPlayer]++] = state->deck[currentPlayer][--(state->deckCount[currentPlayer])];
	}
	// Put the smithy card into the played cards
	state->playedCards[state->playedCardCount++] = state->hand[currentPlayer][handPos];

	// Discard the smithy card
	state->hand[currentPlayer][handPos] = state->hand[currentPlayer][--(state->handCount[currentPlayer])];
	state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
}

unsigned seed;

int main() {
	seed = time(NULL);
//	seed = 5;	
	srand(seed);

	unsigned trials = 5000;

	while (trials > 0) {
		struct gameState state = { 0 };
		struct gameState oracleState = { 0 };

		fillGameStateRandom(&state);
		int handPos = randInt(0, state.handCount[state.whoseTurn]);
		state.hand[state.whoseTurn][handPos] = smithy; // Make sure that the card currently in our hand 

		memcpy(&oracleState, &state, sizeof(struct gameState));

		oracle(&oracleState, oracleState.whoseTurn, handPos);
		cardEffect_smithy(&state, state.whoseTurn, handPos);

		compareStates(&state, &oracleState);

		--trials;
	}
}

// --- Utilities ---

int randInt(int min, int max) {
	return rand() % (max - min) + min;
}
void fillGameStateRandom(struct gameState * state) {
	int kingdomCards[10] = {
		 adventurer,
		 gardens,
		 embargo,
		 village,
		 minion,
		 mine,
		 cutpurse,
		 sea_hag,
		 tribute,
		 smithy
	};
	initializeGame(randInt(2, 5), kingdomCards, 1, state); // No need to include a random seed.  We will be manually shuffling the decks + creating plausible game decks and hands.

	// Initialize hands (not all will be used, just the number in the handCount)
	int * all = (int *)state->hand;
	for (unsigned i = 0; i < MAX_PLAYERS * MAX_HAND; ++i) {
		all[i] = randInt(curse, treasure_map + 1);
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		state->handCount[i] = randInt(5, MAX_HAND);
	}

	// Initialize all the decks
	all = (int *)state->deck;
	for (unsigned i = 0; i < MAX_PLAYERS * MAX_DECK; ++i) {
		all[i] = randInt(curse, treasure_map + 1);
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		state->deckCount[i] = randInt(13, MAX_DECK);
	}

	// Initialize all the discards
	all = (int *)state->discard;
	for (unsigned i = 0; i < MAX_PLAYERS * MAX_DECK; ++i) {
		all[i] = randInt(curse, treasure_map + 1);
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		state->discardCount[i] = randInt(13, MAX_DECK);
	}

	// Set reasonable defaults for these:
	state->whoseTurn = randInt(0, state->numPlayers);
	state->phase = 0;
	state->coins = randInt(0, 700);
	state->numActions = randInt(1, 10);
	state->numBuys = randInt(0, 10);
}

void assert(int current, int expected, char * name) {
	static unsigned totalErrors = 0;
	if (current != expected) {
		printf("Assertion failed: %s should have been %i but was instead %i.\n", name, expected, current);
		if (++totalErrors > 10) {
			printf("Aborted due to 10 previous errors.\n For reproduction purposes, this random seed was: %u\n", seed);
			exit(5);
		}
	}
}

void compareStates(struct gameState * test, struct gameState * expected) {
	assert(test->numPlayers, expected->numPlayers, "numPlayers");
	for (unsigned i = 0; i < treasure_map + 1; ++i) {
		char buffer[100];
		sprintf(buffer, "supplyCount[%u]", i);
		assert(test->supplyCount[i], expected->supplyCount[i], buffer);
	}
	for (unsigned i = 0; i < treasure_map + 1; ++i) {
		char buffer[100];
		sprintf(buffer, "embargoTokens[%u]", i);
		assert(test->embargoTokens[i], expected->embargoTokens[i], buffer);
	}
	assert(test->outpostPlayed, expected->outpostPlayed, "outpostPlayed");
	assert(test->outpostTurn, expected->outpostTurn, "outpostTurn");
	assert(test->whoseTurn, expected->whoseTurn, "whoseTurn");
	assert(test->phase, expected->phase, "phase");
	assert(test->numActions, expected->numActions, "numActions");
	assert(test->coins, expected->coins, "coins");
	assert(test->numBuys, expected->numBuys, "numBuys");
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		for (unsigned j = 0; j < MAX_HAND; ++j) {
			char buffer[100];
			sprintf(buffer, "hand[%u][%u]", i, j);
			assert(test->hand[i][j], expected->hand[i][j], buffer);
		}
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		char buffer[100];
		sprintf(buffer, "handCount[%u]", i);
		assert(test->handCount[i], expected->handCount[i], buffer);
	}

	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		for (unsigned j = 0; j < MAX_DECK; ++j) {
			char buffer[100];
			sprintf(buffer, "deck[%u][%u]", i, j);
			assert(test->deck[i][j], expected->deck[i][j], buffer);
		}
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		char buffer[100];
		sprintf(buffer, "deckCount[%u]", i);
		assert(test->deckCount[i], expected->deckCount[i], buffer);
	}

	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		for (unsigned j = 0; j < MAX_DECK; ++j) {
			char buffer[100];
			sprintf(buffer, "discard[%u][%u]", i, j);
			assert(test->discard[i][j], expected->discard[i][j], buffer);
		}
	}
	for (unsigned i = 0; i < MAX_PLAYERS; ++i) {
		char buffer[100];
		sprintf(buffer, "discardCount[%u]", i);
		assert(test->discardCount[i], expected->discardCount[i], buffer);
	}
	for (unsigned i = 0; i < MAX_DECK; ++i) {
		char buffer[100];
		sprintf(buffer, "playedCards[%u]", i);
		assert(test->playedCards[i], expected->playedCards[i], buffer);
	}
	assert(test->playedCardCount, expected->playedCardCount, "playedCardCount");
}