/*************************************************************************************
 * CS362 Assignment 3
 * Name: Christina Curran
 * File: unittest1.c
 * **********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//Unit testing: whoseTurn
void main (int argc, char** argv){

	struct gameState gm1;
	struct gameState gm2;
	gm1.whoseTurn = 1;
	gm2.whoseTurn = 2;
	
	printf("\n**Unit Test 3: whoseTurn**\n");

	//check player 1
	if(whoseTurn(&gm1) == 1){
		printf("Player 1: PASS\n");
	}
	else{
		printf("Player 1: FAIL\n");
	}

	//check player 2
	if(whoseTurn(&gm2) == 2){
		printf("Player 2: PASS\n");
	}
	else{
		printf("Player 2: FAIL\n");
	}
	printf("**Unit Test 3: whoseTurn complete**\n\n");
	
}
