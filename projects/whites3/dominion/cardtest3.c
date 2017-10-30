/* -----------------------------------------------------------------------
 * cardtest3.c - for remodel()
 *
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
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
        
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 38;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);

    testGameState.hand[currentPlayer][handPos] = 12; //put remondel in hand
    
    printf("\n-----------Testing Remodel------------\n");
    
    
    //choice 1 = 4  //card position to burn choice 2 = 3 --------------------------
    
    controlGameState = testGameState;
    
    int x;
    for(x = 0; x < controlGameState.handCount[currentPlayer]; x++) {
        
        printf("hand: %i, \n", controlGameState.hand[currentPlayer][x]);
    }
    
    printf("\n");
    
    int returnValue = cardEffect(remodel, choice1, choice2, choice3, &testGameState, handPos, &bonus);
    
    printf("cost after cardeffect: %i\n", getCost(controlGameState.hand[currentPlayer][choice1]));
    printf("cost after cardeffect: %i\n", getCost(choice2));
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
    }
    
    int i;
    int provinceFound = 0;
    for (i = 0; i < testGameState.discardCount[currentPlayer]; i++) {
        
        if (testGameState.discard[currentPlayer][i] == 3) {
            provinceFound = 1;
        }
    }
    if (provinceFound) {
        printf("\nPassed: Province now in discard pile.");
    }
    else {
        printf("\nFailed: Province not in discard pile.");
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
    int supplyCountChanged = 0;
    for (i = 1; i < 4; i++) {
        if (testGameState.supplyCount[i] != controlGameState.supplyCount[i]) {
            //printf("\n%i != %i", testGameState.supplyCount[i], controlGameState.supplyCount[i]);
            supplyCountChanged++;
        }
    }
    if (supplyCountChanged) {
        printf("\nPassed: Victory piles changed\n");
    }
    
    else {
        printf("\nFailed: Victory piles have remained unchanged\n");
    }

    return 0;
}