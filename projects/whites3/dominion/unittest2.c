/* -----------------------------------------------------------------------
 * unittest1.c - for fullDeckCount()
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

    
int main(){

    //parameters of fullDeckCount
    int player = 1;
    int card = 0;
    struct gameState testGameState;
    
    
    //rest of game setup
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 95;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    
    
	printf("\n----Testing fullDeckCount()----\n");
    
    
    //peconditions
	for (testGameState.deckCount[player] = 0; testGameState.deckCount[player] < 3; (testGameState.deckCount[player])++) 
	{
    	for (testGameState.handCount[player] = 0; testGameState.handCount[player] < 3; (testGameState.handCount[player])++)
    	{
    	    
    	    for (testGameState.discardCount[player] = 0; testGameState.discardCount[player] < 3; (testGameState.discardCount[player])++) 
    	    {
                
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
                else
                    printf("\n*Failed*: Control count != Test count: (%i != %i)", controlCount, testCount);
                    
                if (controlGameState.deckCount[player] == testGameState.deckCount[player])
                    printf("\nPassed: fullDeckCount() did not change player deckCount");
                else
                    printf("\n*Failed*: fullDeckCount() changed player deckCount");
                    
                if (controlGameState.handCount[player] == testGameState.handCount[player])
                    printf("\nPassed: fullDeckCount() did not change player handCount");
                else
                    printf("\n*Failed*: fullDeckCount() changed player handCount");
                
                if (controlGameState.discardCount[player] == testGameState.discardCount[player])
                    printf("\nPassed: fullDeckCount() did not change player discardCount");
                else
                    printf("\n*Failed*: fullDeckCount() changed player discardCount");    
                    
               	printf("\n     deckCount: %i\n", testGameState.deckCount[player]);
               	printf("     handCount: %i\n", testGameState.handCount[player]); 
               	printf("     discardCount: %i\n", testGameState.discardCount[player]); 
               	
    	    }
    	}
	}
	
        
    return 0;  
    
}