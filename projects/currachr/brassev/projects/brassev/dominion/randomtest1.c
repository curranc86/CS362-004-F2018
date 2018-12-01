/*************************************************************************************
 * CS362 Assignment 4
 * Name: Christina Curran
 * File: randomtest1.c (for great hall)
 * **********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

int main(){

	int i;			//iterators
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
		     tribute, smithy, council_room};
	int numPlayers = 2;
	int currentPlayer = 0;		//setting to 0 to start with player 1
	int seed = 1000;
	int deckSize;
	int handSize;
	int actionStart;
	int actionTest;
	int handStart;
	int handTest;
	int deckStart;
	int deckTest;
	int discardStart;
	int discardTest;
	int fail = 0;
	int failNum = 0;
	int passNum = 0;

	//seed randomizaiton based on time
	srand(time(NULL));
	
	//run many, many random game tests to try and show how valid tests are
	for (i=0; i<9999; i++){
		initializeGame(numPlayers, k, seed, &G);
		//randomize deck size and hand size
		deckSize = rand() % (MAX_DECK+1);	//add 1 to ensure not 0
		handSize = rand() % (deckSize+1);	//add 1 to ensure not 0

		//set up randomization of cards in deck
		//reference = dominion.c
		G.deckCount[0] = deckSize-handSize;
		G.handCount[0] = handSize;

		//get deck, hand, and discards before smithy 
		deckStart = G.deckCount[0];
		handStart = G.handCount[0];
		discardStart = G.playedCardCount;
		actionStart = G.numActions;

		//run great hall card to test
		cardEffect(great_hall, choice1, choice2, choice3, &G, handPos, &bonus);

		//after running adventurer card, test number of coins
		deckTest = G.deckCount[0];
		handTest = G.handCount[0];
		discardTest = G.playedCardCount;
		actionStart = G.numActions;

		//now, check for pass fail of test
		//first, we check that our hand after the test is the same; discarded
		//one and drew 1
		if (handTest != handStart){
			printf("\nTEST FAIL: incorrect number of cards drawn\n");
			failNum++;
			fail = 1;
		}
		//now check and make sure 1 were drawn from deck
		if (deckTest != (deckStart-1)){
			printf("\nTEST FAIL: incorrect number of cards taken from deck\n");
			failNum++;
			fail = 1;
		}
		//now, verify that a card was discarded
		if (discardTest != (discardStart+1)){
			printf("\nTEST FAIL: incorrect number of cards discarded\n");
			failNum++;
			fail = 1;
		}
		//last, we check that our action went up 1
		if (actionTest != (actionStart+1)){
			printf("\nTEST FAIL: incorrect number of cards added\n");
			failNum++;
			fail = 1;
		}
		if (fail == 0){
			printf("\nTESTS PASSED\n");
			passNum++;
		}
	}

	//output number of passes and fails
	printf("\nTests PASSED: %d\n", passNum);
	printf("\nTests FAILED: %d\n", failNum);

	return 0;
}
