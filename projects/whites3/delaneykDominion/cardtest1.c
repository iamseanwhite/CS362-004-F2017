/* -----------------------------------------------------------------------
 * cardtest1.c - for smithy()
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//int handCard(int handPos, struct gameState *state) {
//  int currentPlayer = whoseTurn(state);
//  return state->hand[currentPlayer][handPos];
//}


int main(){
    
    //game setup
    struct gameState controlGameState, testGameState;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handPos = 4;
    int bonus = 0;
      
    
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 41;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    int currentPlayer = 0;
    controlGameState = testGameState;
    
    testGameState.hand[currentPlayer][handPos] = 13; //put smithy in hand
    
    printf("\n-------Testing Smithy------------\n");
    
         // printf("estates before cardeffect: %i\n", testGameState.supplyCount[estate]);
            printf("amount in deck before cardeffect: %i\n", testGameState.deckCount[currentPlayer]);
    
    cardEffect(smithy, choice1, choice2, choice3, &testGameState, handPos, &bonus);
    
            printf("amount in deck after cardeffect: %i\n", testGameState.deckCount[currentPlayer]);    
        //  printf("estates right after cardeffect: %i", testGameState.supplyCount[estate]);
    
    //mock smithy functionality
    controlGameState.handCount[currentPlayer] += 2; //3 cards minus 1 discard
    controlGameState.deckCount[currentPlayer] -= 3;
    
    if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer]) {
        printf("\nPassed: Net handcount increased by 2");
    }
    
    else {
        printf("\nFailed: Net handcount not increased by 2");
    }
    
    if (testGameState.deckCount[currentPlayer] == controlGameState.deckCount[currentPlayer]){
        printf("\nPassed: Net deckCount decreased by 3");
    }
    
    else {
        printf("\nFailed: Net deckCount not decreased by 3");
    }
    
    if (testGameState.handCount[currentPlayer + 1] == controlGameState.handCount[currentPlayer + 1]){
        printf("\nPassed: Other player's handcount did not change");
    }
    
    else {
        printf("\nFailed: Other player's handcount changed");
    }
    
    if (testGameState.deckCount[currentPlayer + 1] == controlGameState.deckCount[currentPlayer + 1]){
        printf("\nPassed: Other player's deckCount did not change");
    }
    
    else {
        printf("\nFailed: Other player's deckCount changed");
    }
    
    int i;
    int supplyCountChanged = 0;
    for (i = 1; i < 4; i++) {
        if (testGameState.supplyCount[i] != controlGameState.supplyCount[i]) {
            printf("\n%i != %i", testGameState.supplyCount[i], controlGameState.supplyCount[i]);
            supplyCountChanged++;
        }
    }
    if (!supplyCountChanged) {
        printf("\nPassed: Victory piles remain unchanged");
    }
    
    else {
        printf("\nFailed: Victory piles have changed");
    }
    
    supplyCountChanged = 0;
    for (i = 0; i < 10; i++) {
        if (testGameState.supplyCount[kingdomCards[i]] != controlGameState.supplyCount[kingdomCards[i]]) {
            printf("\n%i != %i", testGameState.supplyCount[kingdomCards[i]], controlGameState.supplyCount[kingdomCards[i]]);
            supplyCountChanged++;
        }
    }
    if (!supplyCountChanged) {
        printf("\nPassed: Kingdom piles remain unchanged\n");
    }
    
    else {
        printf("\nFailed: Kingdom piles have changed\n");
    }
 return 0;   
}
    