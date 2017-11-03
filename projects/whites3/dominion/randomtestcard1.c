/* -----------------------------------------------------------------------
 * randomtestcard1.c - for discardCard()
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard1.out: randomtestcard1 
 *	./randomtestcard1 &> randomtestcard1.out
 *	gcov -f -b dominion.c >> randomtestcard1.out
 *	cat dominion.c.gcov >> randomtestcard1.out
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
    
    //parameters of discardCard()
    struct gameState testGameState;
    int handPos;
    int currentPlayer = 0;
    int trashFlag;
	int test1 = 0;
	int test2 = 0;
    
    //rest of game setup
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 97;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
	struct gameState controlGameState;
	//struct gameState staticHandState;
	
	
	printf("\n----Testing discardCard()----\n");

	
    
    int r;
    for (r = 0; r < 10000; r++ ) {
    
        srand(r);
        
		testGameState.handCount[currentPlayer] = (rand() % (MAX_HAND));
		if  (testGameState.handCount[currentPlayer] == 0) testGameState.handCount[currentPlayer]++;
		
        //printf("\nThe handCount is -> %i\n", testGameState.handCount[currentPlayer]);
      
        handPos = (rand() % (testGameState.handCount[currentPlayer]));
 
        trashFlag = floor(rand() % (3) ) - 1;
    
        int h;
    	for(h = 0; h < testGameState.handCount[testGameState.whoseTurn]; h++) {
    	    testGameState.hand[testGameState.whoseTurn][h] = rand() % (27) + 1;
    	}

        controlGameState = testGameState;
        
        printf("\n----Test----\n");
		
		printf("     HandCount: %i\n", testGameState.handCount[currentPlayer]);
        printf("     handPos: %i\n", handPos);
        printf("     trashFlag: %i\n", trashFlag);
		
		
		discardCard(handPos, currentPlayer, &testGameState, trashFlag);
        	    
  
            	if (testGameState.handCount[currentPlayer] == controlGameState.handCount[currentPlayer] - 1) 
            	{
            		printf("Passed: Handcount decremented successfully.\n");
            	    //undo the decrement for next test (no other test depends on this value)
            	    //(testGameState.handCount[currentPlayer])++;
            	}
            	else { 
            		printf("*Failed*: Handcount not decremented successfully.\n");
					test1++;
				}
            	
            	
            	
            	
            	//if card is last or only card
            	if (controlGameState.handCount[currentPlayer] == 1 || handPos == (controlGameState.handCount[currentPlayer] - 1))
                {	
                	if (testGameState.hand[currentPlayer][handPos] == -1) 
                		printf("Passed: Card value was made -1\n");
                	
                	else {
                		printf("**Failed**: Card value was not made -1\n");
                		printf("(Control card value is %i, test card value is %i)\n", 
                			   controlGameState.hand[currentPlayer][handPos], testGameState.hand[currentPlayer][handPos]);
						test2++;
					}
                }
                //card is among others and not last
                else 
                {
                    if(testGameState.hand[currentPlayer][handPos] != -1)
                        printf("Passed: Card value was not made -1 because card was not last card\n");
                    else {
                        printf("**Failed**: Card value was made -1 even though not last or only\n");
						test2++;
					}
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
            		
            		
            		   
    	}
		
		if (test1 != 0) printf("test1: %i", test1);
		if (test2 != 0) printf("test2: %i", test2);
		
        //break;
    
    
    
    return 0;
    
}