/* -----------------------------------------------------------------------
 * cardtest4.c - for cutpurse()
 *
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//int cutpurse_card(int currentPlayer, struct gameState* state, int handPos){

int main(){

    //game setup
    struct gameState testGameState;
    struct gameState controlGameState;
    int choice1 = 0, choice2 = 0, choice3 = 0;   // N/A
    int handPos = 4;
    int bonus = 0;
    int currentPlayer = 0;

    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, cutpurse};
    int randomSeed = 86;

    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);

    testGameState.hand[currentPlayer][handPos] = 21; //put cutpurse in hand
    testGameState.coins--; //because 21 is replacing a 4

    //adding cards to opponent's hand because initialization only sets up first player's hand
    testGameState.handCount[currentPlayer + 1] = 5;
    testGameState.hand[currentPlayer + 1][0] = 4;
    testGameState.hand[currentPlayer + 1][1] = 4;
    testGameState.hand[currentPlayer + 1][2] = 1;
    testGameState.hand[currentPlayer + 1][3] = 1;
    testGameState.hand[currentPlayer + 1][4] = 4;


    controlGameState = testGameState;

    int returnValue = cardEffect(cutpurse, choice1, choice2, choice3, &testGameState, handPos, &bonus);

    printf("\n----Testing Cutpurse()---------\n");

    printf("\nhand before: ");
    int i;
    int coins = 0;
    for (i = 0; i < controlGameState.handCount[currentPlayer]; i++) {
        if (controlGameState.hand[currentPlayer][i] == 4)
            coins ++;
        printf("%i, ", controlGameState.hand[currentPlayer][i]);
    }
    printf("\nhand after: ");
    for (i = 0; i < testGameState.handCount[currentPlayer]; i++) {
       // if (testGameState.hand[currentPlayer][i] == 4)
          //  coins ++;
        printf("%i, ", testGameState.hand[currentPlayer][i]);
    }
    //printf("\ncontrol coins: %i, \n", coins);
    //updateCoins(currentPlayer, &controlGameState, 2);
    //printf("\ncontrolgamestate.coins: %i, \n", controlGameState.coins);


    if (testGameState.coins == (controlGameState.coins) + 2) {
        printf("\nPassed: Buying power increased by two");
    }
    else {
        for (i = 0; i < testGameState.handCount[currentPlayer]; i++) {
            printf("%i, ", testGameState.hand[currentPlayer][i]);

        }
        printf("\nFailed: Buying power not increased by two. \n");
         //printf("teststate coins: %i", testGameState.coins);
    }

    if (returnValue == 0) {
        printf("\nPassed: function returns 0\n");

    }
    else
        printf("Failed: function does not return 0\n");

    if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] - 1) {
        printf("Passed: Hand count decreased by 1\n");

    }
    else
        printf("Failed: Handcount did not decrease by 1\n");

    if (testGameState.discardCount[currentPlayer] == controlGameState.discardCount[currentPlayer] + 1) {
        printf("Passed: DiscardCount increased by 1\n");

    }
    else
        printf("Failed: DiscardCount did not increase by 1\n");

    if (testGameState.handCount[currentPlayer + 1] == controlGameState.handCount[currentPlayer + 1]) {
        printf("Failed: Other player's handcount remained unchanged\n");

    }
    else
        printf("Passed: Other player's handcount changed\n");


    if (testGameState.discardCount[currentPlayer + 1] == controlGameState.discardCount[currentPlayer + 1]) {
        printf("Failed: Other player's discard count remained unchanged\n");

    }
    else
        printf("Passed: Other player's discard count changed\n");


    //getchar();
    return 0;
}
