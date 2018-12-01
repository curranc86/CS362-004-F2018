/*************************************************************************************
 * CS362 Assignment 3
 * Name: Christina Curran
 * File: unittest2.c
 * **********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//Unit testing: isGameOver
void main (int argc, char** argv){

	struct gameState gm;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		     sea_hag, tribute, smithy};
	int numPlayers = 2;

	//initialize game to have something for turns to be checked on
	int game = initializeGame(numPlayers, k, 3, &gm);
	
	printf("\n**Unit Test 2: isGameOver**\n");

	printf("Is the player's turn over?\n");
	int i = isGameOver(&gm);
	if (i == 0){
		printf("PASS: turn is over, but not game\n");
	}
	
	printf("**Unit Test 2: isGameOver complete**\n\n");
}
