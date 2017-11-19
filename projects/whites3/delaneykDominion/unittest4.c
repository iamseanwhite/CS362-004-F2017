/* -----------------------------------------------------------------------
 * unittest3.c - for handCard()
 *
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){
    
    //game setup
    struct gameState controlGameState, testGameState;
    int handPos;
      
    
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 70;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    int currentPlayer;
    controlGameState = testGameState;
    
    printf("\n----Testing handCard()----\n");
    
    for(handPos = 0; handPos <= 5; handPos++)
    {
        for(testGameState.whoseTurn = 0; testGameState.whoseTurn <= 1; testGameState.whoseTurn++)
        {   
            currentPlayer = testGameState.whoseTurn;
            
            int returnHand = handCard(handPos, &testGameState);
            
            if(controlGameState.hand[currentPlayer][handPos] == returnHand)
            
                printf("\nPassed: Hand is the same as control\n");
            else {
                printf("\nFailed: Hand is not the same as control (%i != %i)\n", controlGameState.hand[currentPlayer][handPos], returnHand );
            }
            
            if(controlGameState.handCount[currentPlayer] == testGameState.handCount[currentPlayer])
            
                printf("\nPassed: Handcount remained unchanged\n");
            else {
                printf("\nFailed: Handcount was changed.\n");
        
            }
            
            if(controlGameState.handCount[currentPlayer + 1] == testGameState.handCount[currentPlayer + 1])
            
                printf("\nPassed: Other player's handcount remained unchanged\n");
            else {
                printf("\nFailed: Other player's handcount was changed.\n");
        
            }
            
            if(controlGameState.hand[currentPlayer + 1][handPos] == testGameState.hand[currentPlayer + 1][handPos])
            
                printf("\nPassed: Other player's hand remained unchanged\n");
            else {
                printf("\nFailed: Other player's hand was changed.\n");
        
            }
            printf("\n     Current Player: %i", currentPlayer);
            printf("\n     handPos: %i\n", handPos);
            
          
            
        }
    }
    
    
    return 0;
}