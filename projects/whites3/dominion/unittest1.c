/* -----------------------------------------------------------------------
 * unittest1.c - for discardCard()
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){
    
    //parameters of discardCard()
    struct gameState testGameState;
    int handPos;
    int currentPlayer = 0;
    int trashFlag;
    
    //rest of game setup
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 97;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
	struct gameState controlGameState;
	struct gameState staticHandState;
	
	
	printf("\n----Testing discardCard()----\n");
	
	printf("%i", testGameState.handCount[currentPlayer]);
	
	int x;
	for (x = 0; x < testGameState.handCount[currentPlayer]; x++) {
	    staticHandState.hand[currentPlayer][x] = testGameState.hand[currentPlayer][x];
	}
	
    
    for (testGameState.handCount[currentPlayer] = 1; testGameState.handCount[currentPlayer] < 3; (testGameState.handCount[currentPlayer])++)
    {
    	
    	for (handPos = 0; handPos < (testGameState.handCount[currentPlayer]); handPos++ ) 
    	{
    	    
    	    for (trashFlag = -1; trashFlag < 2; trashFlag++) 
    	    {
        	    //make sure to have the same hand every iteration, instead of each iteration changing the hand
        	    for (x = 0; x < testGameState.handCount[currentPlayer]; x++) {
            	    testGameState.hand[currentPlayer][x] = staticHandState.hand[currentPlayer][x];
            	}
        	    controlGameState = testGameState;
        	    discardCard(handPos, currentPlayer, &testGameState, trashFlag);
        	    printf("\n----Test----\n");
        	    
    		
    		
            	if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] - 1) 
            	{
            		printf("Passed: Handcount decremented successfully.\n");
            	    //undo the decrement for next test (no other test depends on this value)
            	    (testGameState.handCount[currentPlayer])++;
            	}
            	else 
            		printf("*Failed*: Handcount not decremented successfully.\n");
            	
            	
            	
            	
            	//if card is last or only card
            	if (controlGameState.handCount[currentPlayer] == 1 || handPos == (controlGameState.handCount[currentPlayer] - 1))
                {	
                	if (testGameState.hand[currentPlayer][handPos] == -1) 
                		printf("Passed: Card value was made -1\n");
                	
                	else {
                		printf("**Failed**: Card value was not made -1\n");
                		printf("(Control card value is %i, test card value is %i)\n", 
                			   controlGameState.hand[currentPlayer][handPos], testGameState.hand[currentPlayer][handPos]);
                	}
                }
                //card is among others and not last
                else 
                {
                    if(testGameState.hand[currentPlayer][handPos] != -1)
                        printf("Passed: Card value was not made -1 because card was not last card\n");
                    else
                        printf("**Failed**: Card value was made -1 even though not last or only\n");
                }
            	
            	
            	
            		
            	//if not trashed
            	if (trashFlag < 1)
            	{
            	    if (testGameState.discardCount[currentPlayer] == controlGameState.discardCount[currentPlayer] + 1)
            	    	printf("Passed: DiscardCount was incremented because card was not trashed.\n");
            	    else 
            		    printf("**Failed**: DiscardCount did not increment even though card was not trashed.\n");	
            	}
            	else
            	    if (testGameState.discardCount[currentPlayer] == controlGameState.discardCount[currentPlayer])
            	        printf("Passed: DiscardCount did not change because card was trashed\n");
            	    else 
            		    printf("**Failed**: DiscardCount changed even though card was trashed.\n");	
            		
            		
            		
            		
            	printf("     HandCount: %i\n", testGameState.handCount[currentPlayer]);
            	printf("     handPos: %i\n", handPos);
            	printf("     trashFlag: %i\n", trashFlag);
            
    	    }
    	   
    	}
        //break;
    }
    
    
    return 0;
    
}