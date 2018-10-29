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

//Adventurer card test
void main(){
	
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0;
	//initialize game, as done in playdom.c and add test game
	struct gameState gm,test;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		     sea_hag, tribute, smithy};
	int player = 0;
	int i;			//iterator
	int smithCount1;
	int smithCount2;
	
	//starting a game and cards
	initializeGame (numPlayers, k, seed, &gm);	

	printf("\n**Testing Smithy card**\n");

	//copy current game into a test game variable for comparison
	memcpy(&test, &gm, sizeof(struct gameState));
	//test Smithy card
	refactorSmithy(&gm, handPos);

	player = whoseTurn(&test);

	//check player hand count
	if(test.handCount[player] == gm.handCount[player]){
		printf ("Player Hand Count: PASS\n");
	}
	else{
		printf ("Player Hand Count: FAIL\n");
	}

	//check player's hand
	if(gm.hand[player][test.handCount[player]] != -1){
		printf ("Card added to player's hand: PASS\n");
	}
	else{
		printf ("Card added to player's hand: FAIL\n");
	}

	//check Smithy card count in hand
	for (i=0; i<gm.handCount[0]; i++){
		if(gm.hand[0][i] = smithy){
			smithCount1++;
		}
	}
	for (i=0; i<test.handCount[0]; i++){
		if (test.hand[0][i] = smithy){
			smithCount2++;
		}
	}
	if (smithCount1 == smithCount2-1){
		printf("Smithy cards in hand: PASS\n");
	}
	else{
		printf("Smithy cards in hand: FAIL\n");
	}

	//check if player played a card
	if(test.playedCardCount+2 == gm.playedCardCount){
		printf("Played Smithy card: PASS\n");
	}
	else{
		printf("Played Smithy card: FAIL\n");
	}

	//check if card discarded
	if(test.discardCount[player] == gm.discardCount[player]){
		printf("Smithy card discarded: PASS\n");
	}
	else{
		printf("Smithy card discarded: FAIL\n");
	}

	printf("**Smithy card testing complete**\n\n");
}
