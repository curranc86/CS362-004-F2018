/*************************************************************************************
 * CS362 Assignment 4
 * Name: Christina Curran
 * File: randomtest2.c (for smithy)
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
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
		     tribute, smithy, council_room};
	int numPlayers = 2;
	int currentPlayer = 0;		//setting to 0 to start with player 1
	int seed = 1000;
	int deckSize;
	int handSize;
	int handPos;
	int deckStart;
	int deckTest;
	int handStart;
	int handTest;
	int discardStart;
	int discardTest;
	int fail = 0;
	int failNum = 0;
	int passNum = 0;

	//seed randomizaiton based on time
	srand(time(NULL));
	
	//run many, many random game tests to try and show how valid tests are
	for (i=0; i<999; i++){
		initializeGame(numPlayers, k, seed, &G);
		//randomize deck size and hand size
		deckSize = rand() % (MAX_DECK+1);	//add 1 to ensure not 0
		handSize = rand() % (deckSize+1);	//add 1 to ensure not 0

		//set up randomization of cards in deck
		//reference = dominion.c
		G.deckCount[0] = deckSize-handSize;
		G.handCount[0] = handSize;

		//get hand pos.
		handPos = G.hand[currentPlayer][G.handCount[currentPlayer]-1];
		//get deck, hand, and discards before smithy 
		deckStart = G.deckCount[0];
		handStart = G.handCount[0];
		discardStart = G.playedCardCount;


		//run smithy  card to test
		refactorSmithy(&G, handPos);

		//after running adventurer card, test number of coins
		deckTest = G.deckCount[0];
		handTest = G.handCount[0];
		discardTest = G.playedCardCount;

		//now, check for pass fail of test
		//smithy = draw 3 cards
		//first, we check that our hand after the test is +2 (only 2 beause
		//we have to discard 1 too)
		if (handTest != (handStart+2)){
			printf("\nTEST FAIL: incorrect number of cards drawn\n");
			failNum++;
			fail = 1;
		}
		//now check and make sure 3 were drawn from deck
		if (deckTest != (deckStart-3)){
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
