/*************************************************************************************
 * CS362 Assignment 3
 * Name: Christina Curran
 * File: cardtest1.c
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
	//initialize game, as done in playdom.c and add test game
	struct gameState gm,test;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		     sea_hag, tribute, smithy};
	int player = 0;
	int i;			//iterator
	int advenCount1;
	int advenCount2;
	
	//starting a game and cards
	initializeGame (numPlayers, k, seed, &gm);	

	printf("\n**Testing Adventurer card**\n");

	//copy current game into a test game variable for comparison
	memcpy(&test, &gm, sizeof(struct gameState));
	//test adventurer card
	refactorAdventurer(&gm);

	player = whoseTurn(&test);

	//Check Deck Coount
	if (test.deckCount[player] == gm.deckCount[player]){
		printf("Deck count: PASS\n");
	}
	else{
		printf("Deck count: FAIL\n");
	}

	//check player hand count
	if(test.handCount[player]-1 == gm.handCount[player]){
		printf ("Player Hand Count: PASS\n");
	}
	else{
		printf ("Player Hand Count: FAIL\n");
	}

	//check player's hand
	if(gm.hand[player][test.handCount[player]] != 1){
		printf ("Card added to player's hand: PASS\n");
	}
	else{
		printf ("Card added to player's hand: FAIL\n");
	}

	//check Adventurer card count in hand
	for (i=0; i<gm.handCount[0]; i++){
		if(gm.hand[0][i] = adventurer){
			advenCount1++;
		}
	}
	for (i=0; i<test.handCount[0]; i++){
		if (test.hand[0][i] = adventurer){
			advenCount2++;
		}
	}
	if (advenCount1 == advenCount2-1){
		printf("Adventurer cards in hand: PASS\n");
	}
	else{
		printf("Adventurer cards in hand: FAIL\n");
	}

	//check if player played a card
	if(test.playedCardCount+2 == gm.playedCardCount){
		printf("Played Adventurer card: PASS\n");
	}
	else{
		printf("Played Adventurer card: FAIL\n");
	}

	//Check if Adventurer action added
	if(test.numActions+2 == gm.numActions){
		printf("Actions added: PASS\n");
	}
	else{
		printf("Actions added: FAIL\n");
	}

	//check if card discarded
	if(test.discardCount[player] == gm.discardCount[player]){
		printf("Adventurer card discarded: PASS\n");
	}
	else{
		printf("Adventurer card discarded: FAIL\n");
	}

	printf("**Adventurer card testing complete**\n\n");
}
