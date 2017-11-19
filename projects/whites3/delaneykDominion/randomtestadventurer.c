/* -----------------------------------------------------------------------
 * randomtestadventurer.c - for advenurer()
 *
 * Include the following lines in your makefile:
 *
 * randomtestadventurer.out: randomtestadventurer 
 *	./randomtestadventurer &> randomtestadventurer.out
 *	gcov -f -b dominion.c >> randomtestadventurer.out
 *	cat dominion.c.gcov >> randomtestadventurer.out
 *	
 *	rm -f dominion.gcda
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>


//int adventurer_card(int drawntreasure, int currentPlayer, struct gameState* state, int* temphand) {


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
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 38;      
    
    //SelectStream(5);
    int r;
    for (r = 0; r < 10000; r++ ) {

        //PutSeed((long)-3234);
        srand(r);   
        
        initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
        
        //testGameState.whoseTurn = floor(rand() % 2);
        testGameState.whoseTurn = currentPlayer;
        //currentPlayer = testGameState.whoseTurn;
    	testGameState.deckCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);
    	testGameState.discardCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);
    	testGameState.handCount[testGameState.whoseTurn] = floor(rand() % (10) + 1);
    	
    	int h;
    	for(h = 0; h < testGameState.handCount[testGameState.whoseTurn]; h++) {
    	    //testGameState.hand[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}
    	for(h = 0; h < testGameState.deckCount[testGameState.whoseTurn]; h++) {
    	    testGameState.deck[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}
    	for(h = 0; h < testGameState.discardCount[testGameState.whoseTurn]; h++) {
    	    testGameState.discard[testGameState.whoseTurn][h] = rand() % (26) + 1;
    	}
    	
        
        
        
        int i;
        int numOfCopper = 0;
        int numOfSilver = 0;
        int numOfGold = 0;
        int numOfTreasure;
        
        testGameState.hand[currentPlayer][handPos] = 7; //put advenurer in hand

        controlGameState = testGameState;

        printf("\n-------Testing Adventurer-----------\n");
        
        printf("deckCount: %i \n", controlGameState.deckCount[currentPlayer]);
        printf("discardCount: %i \n", controlGameState.discardCount[currentPlayer]);
        printf("handCount: %i \n\n", controlGameState.handCount[currentPlayer]);

        cardEffect(adventurer, choice1, choice2, choice3, &testGameState, handPos, &bonus);

        // printf("control deck: \n");
         for(i = 0; i < controlGameState.deckCount[currentPlayer]; i++) {
            if (controlGameState.deck[currentPlayer][i] == copper)
                numOfCopper++;
            if (controlGameState.deck[currentPlayer][i] == silver)
                numOfSilver++;
            if (controlGameState.deck[currentPlayer][i] == gold)
                numOfGold++;
        //    printf("deck: %i, \n", controlGameState.deck[currentPlayer][i]);
        }
        
        for(i = 0; i < controlGameState.discardCount[currentPlayer]; i++) {
            if (controlGameState.discard[currentPlayer][i] == copper)
                numOfCopper++;
            if (controlGameState.discard[currentPlayer][i] == silver)
                numOfSilver++;
            if (controlGameState.discard[currentPlayer][i] == gold)
                numOfGold++;
        //    printf("deck: %i, \n", controlGameState.deck[currentPlayer][i]);
        }
       
       
        numOfTreasure = numOfCopper + numOfGold + numOfSilver;
        if (numOfTreasure > 2) numOfTreasure = 2;
        
        //printf("\nTotal control treasure in deck before cardeffect: %i\n", numOfTreasure);
        
      //  printf("control hand: \n");
        for(i = 0; i < controlGameState.handCount[currentPlayer]; i++) {
    
         //   printf("hand card: %i, \n", controlGameState.hand[currentPlayer][i]);
        }
        
        
      //  printf("\nafter cardeffect\n");
        //int x;
        
        
        
        if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] + numOfTreasure) //gain number of treasures
            printf("Passed: Hand count was  changed correctly.  (control = %i, test = %i, numOfTreasure = %i)", controlGameState.handCount[currentPlayer], testGameState.handCount[currentPlayer], numOfTreasure);
        else
            printf("Failed: Hand count was not changed correctly.  (control = %i, test = %i, numOfTreasure = %i)", controlGameState.handCount[currentPlayer], testGameState.handCount[currentPlayer], numOfTreasure);
            
            
        if (numOfTreasure == 1) {
            int card = testGameState.hand[currentPlayer][controlGameState.handCount[currentPlayer]];
            
            if (card == 4 || card == 5 || card == 6) //control hand has two treasures
                printf("\nPassed: New card is treasure");
            else
                printf("\nFailed: New card is not treasure");
        }
        
        else if (numOfTreasure == 2) {
            int card = testGameState.hand[currentPlayer][controlGameState.handCount[currentPlayer]];
            int card2 =testGameState.hand[currentPlayer][controlGameState.handCount[currentPlayer]+1];
            
            if ((card == 4 || card == 5 || card == 6) && (card2 == 4 || card2 == 5 || card2 == 6))  //control hand has two treasures
                printf("\nPassed: New cards are treasure");
            else
                printf("\nFailed: New cards are not treasure");
        }
        
        else if (numOfTreasure == 0) {
            int somethingChanged = 0;
            for(i = 0; i < controlGameState.deckCount[currentPlayer]; i++) { 
                if (testGameState.hand[currentPlayer][i] != controlGameState.hand[currentPlayer][i]) {
                    somethingChanged++;
                }
            }
             if (!somethingChanged)  //control hand has two treasures
                printf("\nPassed: Hand remained the same");
            else
                printf("\nFailed: The hand was altered");
        }
         
         
        if (currentPlayer == 0) {
            if (testGameState.handCount[currentPlayer + 1] == controlGameState.handCount[currentPlayer + 1]){
                printf("\nPassed: Other player's handcount did not change");
            }
            else {
                printf("\nFailed: Other player's handcount changed");
            }
        }
        
        else {
              if (testGameState.handCount[currentPlayer - 1] == controlGameState.handCount[currentPlayer - 1]){
                printf("\nPassed: Other player's handcount did not change");
            }
            else {
                printf("\nFailed: Other player's handcount changed");
            }
        }
        
        if (testGameState.deckCount[currentPlayer + 1] == controlGameState.deckCount[currentPlayer + 1]){
            printf("\nPassed: Other player's deckCount did not change");
        }
        else {
            printf("\nFailed: Other player's deckCount changed");
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
            printf("\nPassed: Kingdom piles remain unchanged\n\n");
        }
        
        else {
            printf("\nFailed: Kingdom piles have changed\n\n");
        }
    }
 
    return 0;   
}
    