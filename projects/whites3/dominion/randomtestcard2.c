/* -----------------------------------------------------------------------
 * randomtestcard1.c - for fullDeckCount()
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard2.out: randomtestcard2 
 *	./randomtestcard2 &> randomtestcard2.out
 *	gcov -f -b dominion.c >> randomtestcard2.out
 *	cat dominion.c.gcov >> randomtestcard2.out
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

    
int main(){

    //parameters of fullDeckCount
    int player;
    int card;
    struct gameState testGameState;
    int failedTests = 0;
    
    
    //rest of game setup
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 95;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    
    
	printf("\n----Testing fullDeckCount()----\n");
    
    int r;
    for (r = 0; r < 10000; r++ ) {

        //PutSeed((long)-3234);
        srand(r);   
    
    //peconditions
    	        
    	testGameState.whoseTurn = floor(Random() * 2);
    	player = testGameState.whoseTurn;
    	card = floor(rand() % (27) + 1);
    	testGameState.deckCount[testGameState.whoseTurn] = floor(rand() % (MAX_DECK));
    	testGameState.discardCount[testGameState.whoseTurn] = floor(rand() % (MAX_DECK));
    	testGameState.handCount[testGameState.whoseTurn] = floor(rand() % (MAX_HAND));
    	
    	int h;
    	for(h = 0; h < testGameState.handCount[testGameState.whoseTurn]; h++) {
    	    testGameState.hand[testGameState.whoseTurn][h] = rand() % (27) + 1;
    	}
    	for(h = 0; h < testGameState.deckCount[testGameState.whoseTurn]; h++) {
    	    testGameState.deck[testGameState.whoseTurn][h] = rand() % (27) + 1;
    	}
    	for(h = 0; h < testGameState.discardCount[testGameState.whoseTurn]; h++) {
    	    testGameState.discard[testGameState.whoseTurn][h] = rand() % (27) + 1;
    	}
                
                struct gameState controlGameState = testGameState;
                int testCount = fullDeckCount(player, card, &testGameState);
                int controlCount = 0;
                int i;
                
                for (i = 0; i < testGameState.deckCount[player]; i++)
                {
                    if (testGameState.deck[player][i] == card) controlCount++;
                }
                
                for (i = 0; i < testGameState.handCount[player]; i++)
                {
                    if (testGameState.hand[player][i] == card) controlCount++;
                }
                
                for (i = 0; i < testGameState.discardCount[player]; i++)
                {
                    if (testGameState.discard[player][i] == card) controlCount++;
                }
                
                if (controlCount == testCount)
                    printf("\nPassed: Control count == Test count  (%i == %i)", controlCount, testCount);
                else {
                    printf("\n*Failed*: Control count != Test count: (%i != %i)", controlCount, testCount);
                    failedTests++;
                }
                if (controlGameState.deckCount[player] == testGameState.deckCount[player])
                    printf("\nPassed: fullDeckCount() did not change player deckCount");
                else {
                    printf("\n*Failed*: fullDeckCount() changed player deckCount");
                    failedTests++;
                }
                if (controlGameState.handCount[player] == testGameState.handCount[player])
                    printf("\nPassed: fullDeckCount() did not change player handCount");
                else {
                    printf("\n*Failed*: fullDeckCount() changed player handCount");
                    failedTests++;
                }
                if (controlGameState.discardCount[player] == testGameState.discardCount[player])
                    printf("\nPassed: fullDeckCount() did not change player discardCount");
                else {
                    printf("\n*Failed*: fullDeckCount() changed player discardCount");    
                    failedTests++;
                }
               	printf("\n     deckCount: %i\n", testGameState.deckCount[player]);
               	printf("     handCount: %i\n", testGameState.handCount[player]); 
               	printf("     discardCount: %i\n", testGameState.discardCount[player]);
               	printf("     card: %i\n", card);
               	printf("     player: %i\n", player);
               	
               	
	
    }
    printf("\n     -------Failed tests: %i\n", failedTests);
    return 0;  
    
}