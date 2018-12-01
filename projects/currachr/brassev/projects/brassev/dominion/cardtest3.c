/*************************************************************************************
 * CS362 Assignment 3
 * Name: Christina Curran
 * File: cardtest3.c
 * **********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Village card test
void main(){
	
	int numPlayers = 2;
	int seed = 1000;
	//initialize game, as done in playdom.c and add test game
	struct gameState gm,test;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		     sea_hag, tribute, smithy};
	int handPos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	int player = 0;
	
	//starting a game and cards
	initializeGame (numPlayers, k, seed, &gm);	

	printf("\n**Testing Village card**\n");

	//copy current game into a test game variable for comparison
	memcpy(&test, &gm, sizeof(struct gameState));
	//test Village card
	cardEffect(village, choice1, choice2, choice3, &gm, handPos, &bonus);
	player = whoseTurn(&test);

	//check player hand count
	if(test.handCount[player]+1 == gm.handCount[player]){
		printf ("Player Hand Count: PASS\n");
	}
	else{
		printf ("Player Hand Count: FAIL\n");
		printf("Expected: %d\n", (test.handCount[player]+1));
		printf("Actual: %d\n", gm.handCount[player]);
}

	//check player's hand
	if(gm.hand[player][test.handCount[player]] != -1){
		printf ("Card added to player's hand: PASS\n");
	}
	else{
		printf ("Card added to player's hand: FAIL\n");
}

	//check if player played a card
	if(test.playedCardCount+1 == gm.playedCardCount){
		printf("Played Village card: PASS\n");
	}
	else{
		printf("Played Village card: FAIL\n");
		printf("Expected: %d\n", (test.playedCardCount+1));
		printf("Actual: %d\n", gm.playedCardCount);
}

	//check if card discarded
	if(test.discardCount[player]+1 == gm.discardCount[player]){
		printf("Village card discarded: PASS\n");
	}
	else{
		printf("Village card discarded: FAIL\n");
		printf("Expected: %d\n", (test.discardCount[player]+1));
		printf("Actual: %d\n", gm.discardCount[player]);
}

	//Check if Village action added
	if((test.numActions+3) == gm.numActions){
		printf("Actions added: PASS\n");
	}
	else{
		printf("Actions added: FAIL\n");
		printf("Expected: %d\n", (test.numActions+3));
		printf("Actual: %d\n", gm.numActions);
}
	printf("**Village card testing complete**\n\n");
}
