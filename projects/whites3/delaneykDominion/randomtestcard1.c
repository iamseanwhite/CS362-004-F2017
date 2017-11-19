/* -----------------------------------------------------------------------
 * randomtestcard1.c - for remodel()
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"


//int adventurer_card(int drawntreasure, int currentPlayer, struct gameState* state, int* temphand) {


int main(){

    //game setup
    struct gameState testGameState;
    struct gameState controlGameState;
    int choice1 = 4, choice2 = 3, choice3 = 0;   // N/A
    int handPos = 3;
    int bonus = 0;
    int currentPlayer = 0;
    int selftrash = 0;
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 38;

    int r;
    for (r = 0; r < 1000; r++ ) {

        //PutSeed((long)-3234);
        srand(r);

        initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);


        //randomize cards and choices

        //testGameState.whoseTurn = floor(rand() % 2);
        testGameState.whoseTurn = currentPlayer;
        //currentPlayer = testGameState.whoseTurn;
    	testGameState.deckCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);
    	testGameState.discardCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);
    	testGameState.handCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);

    	int h;
    	for(h = 0; h < testGameState.handCount[testGameState.whoseTurn]; h++) {
    	    testGameState.hand[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}
    	for(h = 0; h < testGameState.deckCount[testGameState.whoseTurn]; h++) {
    	    testGameState.deck[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}
    	for(h = 0; h < testGameState.discardCount[testGameState.whoseTurn]; h++) {
    	    testGameState.discard[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}

        handPos = rand() % (testGameState.handCount[testGameState.whoseTurn]);
        choice1 = rand() % (testGameState.handCount[testGameState.whoseTurn]);
        //if (testGameState.hand[currentPlayer][choice1] == 12)
        //    choice1--;
        choice2 = rand() % (26) + 1;

        testGameState.hand[currentPlayer][handPos] = 12; //put remondel in hand

        printf("\n-----------Testing Remodel------------\n");


        //choice 1 = 4  //card position to burn choice 2 = 3 --------------------------

        controlGameState = testGameState;

        int x;
        printf("hand: ");
        for(x = 0; x < controlGameState.handCount[currentPlayer]; x++) {
            printf("%i, ", controlGameState.hand[currentPlayer][x]);
        }

        printf("\n");

        int returnValue = cardEffect(remodel, choice1, choice2, choice3, &testGameState, handPos, &bonus);

        printf("Choice One : %i\n", controlGameState.hand[currentPlayer][choice1]);
        printf("Choice Two : %i\n", choice2);
        printf("cost of choice one : %i\n", getCost(controlGameState.hand[currentPlayer][choice1]));
        printf("cost of choice two : %i\n", getCost(choice2));
        printf("return value: %i\n", returnValue);

        if (getCost(controlGameState.hand[currentPlayer][choice1]) < getCost(choice2) - 2)
        {
            if(returnValue == -1)
                printf("\nPassed: Remodel returned -1 because card was too expensive.");
            else
                printf("\nFailed: Remodel did not return -1 even though card was too expensive.");
        }

        else {
            if(returnValue == -1)
                printf("\nFailed: Remodel returned -1 even though card was not too expensive.");
            else {
                printf("\nPassed: Remodel did not return -1 because card was not too expensive");
            }
        }


        if (testGameState.hand[currentPlayer][choice1] == 12) {
            if (returnValue == -1) {
                printf("\n----------Passed: Trashing remodel is not allowed.---------"); //dashes because test executes rarely
            }
            else {
                printf("\n-----------Failed: Trashing remodel was allowed.------------");
                selftrash += 1;
            }
        }

        int i;
        int choice2Found = 0;
        for (i = 0; i < testGameState.discardCount[currentPlayer]; i++) {

            if (testGameState.discard[currentPlayer][i] == choice2) {
                choice2Found = 1;
            }
        }
        if (choice2Found) {
            printf("\nPassed: Choice card now in discard pile.");
        }
        else {
            printf("\nFailed: Choice card not in discard pile.");
        }

        if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] - 2) //remodel and trashed card should be now gone
               printf("\nPassed: Hand now two cards lighter");

        else {
            printf("\nFailed: Hand is not two cards lighter");
        }

        if (testGameState.handCount[currentPlayer + 1] == controlGameState.handCount[currentPlayer + 1]){
            printf("\nPassed: Other player's handcount did not change");
        }

        else {
            printf("\nFailed: Other player's handcount changed");
        }

        if (testGameState.deckCount[currentPlayer + 1] == controlGameState.deckCount[currentPlayer + 1]){
            printf("\nPassed: Other player's deckCount did not change ");
        }

        else {
            printf("\nFailed: Other player's deckCount changed");
        }


        //int i;
        int pickedCardCountChanged = 0;
        for (i = 1; i < 27; i++) {
            if (testGameState.supplyCount[i] != controlGameState.supplyCount[i]) {
                if (i == choice2) {
                    //printf("\n%i != %i", testGameState.supplyCount[i], controlGameState.supplyCount[i]);
                    pickedCardCountChanged++;
                }
            }
        }
        if (pickedCardCountChanged) {
            printf("\nPassed: Picked card pile changed\n");
        }

        else {
            printf("\nFailed: Picked Card pile has remained unchanged\n");
        }
    }

    printf("self trash error %i times\n", selftrash);
    //getchar();

    return 0;
}

