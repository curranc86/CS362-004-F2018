/*************************************************************************************
 * CS362 Assignment 3
 * Name: Christina Curran
 * File: cardtest4.c
 * **********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Sea Hag card test
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

	printf("\n**Testing Sea Hag card**\n");

	//copy current game into a test game variable for comparison
	memcpy(&test, &gm, sizeof(struct gameState));
	//test Village card
	cardEffect(sea_hag, choice1, choice2, choice3, &gm, handPos, &bonus);
	player = whoseTurn(&test);

	//check player hand count
	if(test.handCount[player] == gm.handCount[player]){
		printf ("Player Hand Count: PASS\n");
	}
	else{
		printf ("Player Hand Count: FAIL\n");
	}

	//check if card discarded
	if(test.discardCount[player] == gm.discardCount[player]){
		printf("Village card discarded: PASS\n");
	}
	else{
		printf("Village card discarded: FAIL\n");
	}

	printf("**Sea Hag card testing complete**\n\n");
}
