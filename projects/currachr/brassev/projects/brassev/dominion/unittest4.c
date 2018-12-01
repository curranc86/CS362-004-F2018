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

//Unit testing: updateCoins
void main (int argc, char** argv){

	int i = 0;
	struct gameState gm;
	gm.coins = 0;

	printf("\n**Unit Test 4: updateCoins**\n");

	//gold
	printf("T1: GOLD\n");
	for(i=0; i<10; i++){
		gm.hand[0][i] = gold;
		//printf("%c", gm.hand[0][i]);
	}
	updateCoins(0, &gm, 0);
	if (gm.coins == 30){
		printf("Gold coins %d/30: PASS\n", gm.coins);
	}
	else{
		printf("Gold coins %d/30: FAIL\n", gm.coins);
	}

	//silver
	printf("T2: SILVER\n");
	for(i=0; i<10; i++){
		gm.hand[0][i] = silver;
	}
	updateCoins(0, &gm, 0);
	if (gm.coins == 20){
		printf("Silver coins %d/20: PASS\n", gm.coins);
	}
	else{
		printf("Silver coins %d/20: FAIL\n", gm.coins);
	}

	//copper
	printf("T3: COPPER\n");
	for(i=0; i<10; i++){
		gm.hand[0][i] = copper;
	}
	updateCoins(0, &gm, 0);
	if (gm.coins == 10){
		printf("Copper coins %d/10: PASS\n", gm.coins);
	}
	else{
		printf("Copper coins %d/10: FAIL\n", gm.coins);
	}

	//copper
	printf("T4: COPPER BONUS\n");
	for(i=0; i<10; i++){
		gm.hand[0][i] = copper;
	}
	updateCoins(0, &gm, 1);
	if (gm.coins == 11){
		printf("Copper coins + bonus  %d/11: PASS\n", gm.coins);
	}
	else{
		printf("Copper coins + bonus %d/11: FAIL\n", gm.coins);
	}

	printf("**Unit Test 4: updateCoins complete**\n\n");
}
