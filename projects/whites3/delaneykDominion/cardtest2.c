/* -----------------------------------------------------------------------
 * cardtest2.c - for advenurer()
 *
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
    int choice1 = 0, choice2 = 0, choice3 = 0;   // N/A
    int handPos = 4;
    int bonus = 0;
    
        
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 38;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    int currentPlayer = 0;
    
    
    int i;
    int numOfCopper = 0;
    int numOfSilver = 0;
    int numOfGold = 0;
    int numOfTreasure;
    
    testGameState.hand[currentPlayer][handPos] = 7; //put advenurer in hand
    
    controlGameState = testGameState;
    printf("\n-------Testing Adventurer-----------\n");
    
    cardEffect(adventurer, choice1, choice2, choice3, &testGameState, handPos, &bonus);
    
     for(i = 0; i < controlGameState.deckCount[currentPlayer]; i++) {
        if (controlGameState.deck[currentPlayer][i] == copper)
            numOfCopper++;
        if (controlGameState.deck[currentPlayer][i] == silver)
            numOfSilver++;
        if (controlGameState.deck[currentPlayer][i] == gold)
            numOfGold++;
        printf("deck: %i, \n", controlGameState.deck[currentPlayer][i]);
    }
   
   
    numOfTreasure = numOfCopper + numOfGold + numOfSilver;
    
    printf("\nTotal control treasure in deck before cardeffect: %i\n", numOfTreasure);
    
    
    for(i = 0; i < controlGameState.handCount[currentPlayer]; i++) {

        printf("hand card: %i, \n", controlGameState.hand[currentPlayer][i]);
    }
    
    
    printf("\nafter cardeffect\n");
    
    if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] + 1) //control hand has two treasures
        printf("Passed: Hand count was increased by exactly 1");
    else
        printf("Failed: Hand count was not increased by exactly 1");
        
        
    if (testGameState.hand[currentPlayer][4] == 4 && testGameState.hand[currentPlayer][5] == 4 ) //control hand has two treasures
        printf("\nPassed: Two new cards are coppers");
    else
        printf("\nFailed: Two new cards are not coppers");
     
     
    if (testGameState.handCount[currentPlayer + 1] == controlGameState.handCount[currentPlayer + 1]){
        printf("\nPassed: Other player's handcount did not change");
    }
    else {
        printf("\nFailed: Other player's handcount changed");
    }
    
    
    if (testGameState.deckCount[currentPlayer + 1] == controlGameState.deckCount[currentPlayer + 1]){
        printf("\nPassed: Other player's deckCount did not change\n");
    }
    else {
        printf("\nFailed: Other player's deckCount changed\n");
    }
    
    numOfTreasure = 0;
    numOfSilver = 0;
    numOfCopper = 0;
    numOfGold = 0;
    
    for(i = 0; i < testGameState.deckCount[currentPlayer]; i++) {
        if (testGameState.deck[currentPlayer][i] == copper)
            numOfCopper++;
        if (testGameState.deck[currentPlayer][i] == silver)
            numOfSilver++;
        if (testGameState.deck[currentPlayer][i] == gold)
            numOfGold++;
        printf("%i, ", testGameState.deck[currentPlayer][i]);
        //printf("hi");
    }
    
    numOfTreasure = numOfCopper + numOfGold + numOfSilver;
    
    printf("\nTotal treasure: %i\n", numOfTreasure);
    
    for(i = 0; i < testGameState.handCount[currentPlayer]; i++) {

        printf("hard card: %i, \n", testGameState.hand[currentPlayer][i]);
    }
    
    
    //check card piles----------------------------------------------------------------------------
    
    
    //int i;
    int supplyCountChanged = 0;
    for (i = 1; i < 4; i++) {
        if (testGameState.supplyCount[estate] != controlGameState.supplyCount[estate]) {
            printf("\n%i != %i", testGameState.supplyCount[estate], controlGameState.supplyCount[estate]);
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
    