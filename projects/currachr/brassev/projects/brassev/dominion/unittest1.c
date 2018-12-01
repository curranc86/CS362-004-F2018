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

//Unit testing: buyCard
void main (int argc, char** argv){
	
	struct gameState gm;
	gm.numBuys = 2;
	gm.coins = 2;
	
	printf("\n**Unit Test 1: buyCard**\n");

	printf("T1: Insufficient coins to buy card\n");
	int t = buyCard(2, &gm);
	if (t == -1){
		printf("PASS: unable to buy card\n");
	}
	else{
		printf("FAIL\n");
	}

	printf("T2: Sufficient coins to buy card\n");
	gm.coins = 10;
	t = buyCard(2, &gm);
	if (t == 0){
		printf("PASS: able to buy card\n");
	}
	else{
		printf("FAIL\n");
	}

	printf("T3: Sufficient coins to buy card but no buys left\n");
	gm.numBuys = 0;
	t = buyCard(2, &gm);
	if (t == -1){
		printf("PASS: unable to buy card; no more buys\n");
	}
	else{
		printf("FAIL\n");
	}
	
	printf("**Unit Test 1: buyCard complete**\n\n");
}
