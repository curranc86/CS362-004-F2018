/*************************************************************************************
 * CS362 Assignment 4
 * Name: Christina Curran
 * File: randomtesadventurer.c
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

	int i, j, h, g, c;			//iterators
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
		     tribute, smithy, council_room};
	int numPlayers = 2;
	int currentPlayer = 0;		//setting to 0 to start with player 1
	int seed = 1000;
	int deckSize;
	int hand;
	int handSize;
	int randCard;
	int randKingdom;
	int coin;
	int coinTest;
	int coinDiscard;
	int fail = 0;
	int failNum;
	int passNum;

	//seed randomizaiton based on time
	srand(time(NULL));
	
	//get number of players
	//numPlayers = rand() % 50;

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
		for (h=0; h < numPlayers; h++){
			for (j=0; j < G.deckCount[j]; j++){
				randCard = rand()% 50;
				randKingdom = rand() % 10; 
				if (randCard == 0){
					G.deck[h][j] = copper;
				}
				else if (randCard == 1){
					G.deck[h][j] = silver;
				}
				else if (randCard == 2){
					G.deck[h][j] = gold;
				}
				else {
					G.deck[h][j] = k[randKingdom];
				}
			}
		}

		//count coins in player's hand; drawn in initializeGame
		for (g=0; g<G.handCount[currentPlayer]; g++){
			if (G.hand[currentPlayer][g] == copper ||
			    G.hand[currentPlayer][g] == silver ||
			    G.hand[currentPlayer][g] == gold){
				coin++;
			} 
		}

		//run adventurer card to test
		refactorAdventurer(&G);
		//after running adventurer card, test number of coins
		coinTest = 0;
		for (g=0; g<G.handCount[currentPlayer]; g++){
			if (G.hand[currentPlayer][g] == copper ||
			    G.hand[currentPlayer][g] == silver ||
			    G.hand[currentPlayer][g] == gold){
				coinTest++;
			} 
		}

		//check discard pile for any coins
		coinDiscard = 0;
		for (c=0; c < G.discardCount[currentPlayer]; c++){
			if (G.discard[currentPlayer][c] == copper ||
			    G.discard[currentPlayer][c] == silver ||
			    G.discard[currentPlayer][c] == gold){
				coinDiscard++;
			} 
		}

		//now, check for pass fail of test
		//first, verify whether coin count is correct; should be 2+ coin
		//after adventurer card, then make sure no coins discarded
		if (coinTest < coin){
			printf ("\nTEST FAIL: not enough treasure drawn\n");
			failNum++;
			fail = 1;
		}
		if (coinTest > (coin+2)){
			printf("\nTEST FAIL: too many treasure cards drawn\n");
			failNum++;
			fail = 1;
		}
		if (coinDiscard != 0){
			printf("\nTEST FAIL: copper, silver, or gold was discarded\n");
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
