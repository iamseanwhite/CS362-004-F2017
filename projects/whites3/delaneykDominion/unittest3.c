/* -----------------------------------------------------------------------
 * unittest3.c - for isGameOver()
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest1.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    struct gameState testGameState;
    
    int numberOfPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, treasure_map, gardens, mine,
							remodel, smithy, village, baron, great_hall};
    int randomSeed = 62;      
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    testGameState.supplyCount[province] = 0;
    
    //controlGameState = testGameState;
    
    
    printf("\n----Testing isGameOver()----\n");
    
    printf("\n--Testing Province Pile--\n");
    
    for (testGameState.supplyCount[province] = 2;  testGameState.supplyCount[province] > -1;  testGameState.supplyCount[province]--) {
        
        int testGameOver = isGameOver(&testGameState);
        
        if (!testGameOver) {
            if (testGameState.supplyCount[province] > 0)
                printf("Passed: Game not over yet.");
            else
                printf("*Failed*: Game should be over and is not.");
        }
        
        else {
            if (testGameState.supplyCount[province] == 0)
                printf("Passed: Game ended at correct time.");
            else
                printf("*Failed*: Game ended prematurely.");
        }
        
        printf("     testGameState SupplyCount: %i\n", testGameState.supplyCount[province]);
        
    }
    
    
    initializeGame(numberOfPlayers, kingdomCards, randomSeed, &testGameState);
    
    printf("\n--Testing Supply Piles--\n");
    
    //int controlNumberOfEmptyPiles = 0;
    //int testNumberOfEmptyPiles = 0;
    int c;
    int i;
    for (c = 0; c < 13; c++) {
        
    int controlNumberOfEmptyPiles = 0;
    //int testNumberOfEmptyPiles = 0;
        
        for (i = 0; i < 27; i++) {
            if (testGameState.supplyCount[i] == 0) {
                //testNumberOfEmptyPiles++;
                int x;
                for(x = 0; x < 10; x++) {
                    if (i == kingdomCards[x]) {
                        printf("\n%i = %i", i, kingdomCards[x]);
                        controlNumberOfEmptyPiles++;
                    }
                }
            }
        }
        
        printf("\n");
        int testGameOver = isGameOver(&testGameState);
        
        printf("%i\n", testGameState.supplyCount[7]);
        printf("%i\n", testGameState.supplyCount[8]);
        printf("%i\n", testGameState.supplyCount[26]);
        
        if (!testGameOver) {
            if (controlNumberOfEmptyPiles < 3)
                printf("Passed: Game should not be over yet.");
            else {
                printf("*Failed*: Game should be over and is not. (%i)", !testGameOver);
                //break;
            }
        }
        
        else {
            if (controlNumberOfEmptyPiles >= 3){
                 printf("Passed: Game is over at correct time.");
                // break;
            }
            else {
                printf("*Failed*: Game ended prematurely");
            }
            
        }
        
        printf("\n     adventurers: %i", testGameState.supplyCount[adventurer]);
        printf("\n     council rooms: %i", testGameState.supplyCount[council_room]);
        printf("\n     treasure_map: %i", testGameState.supplyCount[treasure_map]);
        printf("\n     controlNumberOfEmptyPiles: %i\n\n", controlNumberOfEmptyPiles);
        
        if (testGameState.supplyCount[adventurer] > 0)
            testGameState.supplyCount[adventurer]--;
        
        if (testGameState.supplyCount[council_room] > 0 && c > 0)
            testGameState.supplyCount[council_room]--;
        
        if (testGameState.supplyCount[treasure_map] > 0 && c > 1)
            testGameState.supplyCount[treasure_map]--;
       // printf("     testNumberOfEmptyPiles: %i\n\n", testNumberOfEmptyPiles);
        
        //if (testNumberOfEmptyPiles > 4 || controlNumberOfEmptyPiles > 4) break;
    }
    
    
        
        
    return 0;
    
}
    
    