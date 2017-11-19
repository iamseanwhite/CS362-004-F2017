/*
 * cardtest2.c
 *
 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "test_helpers.c"

int testAdventurer(int testSeed) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed, minSeed = 1, maxSeed = 1000000;
  int numPlayers;
  int thisPlayer;
  struct gameState G, testG;
  int totalCardsTest, totalCardsControl, numTreasureHandBefore, numTreasureDeckBefore, numTreasureDiscardBefore, numTreasureHandAfter;
  int testPassed = 1;
  int print = 0;

  printf("----------------- Testing Card: Adventurer----------------\n");

  if (testSeed > 0) {
    minSeed = testSeed;
    maxSeed = testSeed + 1;
  };

  for (seed = minSeed; seed < maxSeed; seed++) {    
    randomizeGame(seed, &G, &thisPlayer);
  
    // place adventurer at random handpos
    if (G.handCount[thisPlayer] == 0) {
      G.handCount[thisPlayer] = 0;
      handpos = 0;
    }  else
      handpos = rand() %  G.handCount[thisPlayer];
    G.hand[thisPlayer][handpos] = adventurer;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // play card
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // count total cards
    totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer];
    totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

    // count treasure 
    numTreasureHandBefore = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
      if ( G.hand[thisPlayer][i] == copper ||  G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold) {
	numTreasureHandBefore++;
      }
    }
    numTreasureDeckBefore = 0;
    for (i = 0; i < G.deckCount[thisPlayer]; i++) {
      if ( G.deck[thisPlayer][i] == copper ||  G.deck[thisPlayer][i] == silver|| G.deck[thisPlayer][i] == gold) {
	numTreasureDeckBefore++;
      }
    }
    numTreasureDiscardBefore = 0;
    for (i = 0; i < G.discardCount[thisPlayer]; i++) {
      if ( G.discard[thisPlayer][i] == copper ||  G.discard[thisPlayer][i] == silver|| G.discard[thisPlayer][i] == gold) {
	numTreasureDiscardBefore++;
      }
    }
    numTreasureHandAfter = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
      if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver|| testG.hand[thisPlayer][i] ==
gold) {
	numTreasureHandAfter++;
      }
    }
 
    // if running single test case, print assertion details
    if (testSeed > 0)
       print = 1; 
    else
       print = 0; 

    // test assertions
    testPassed = 1;
    testPassed *= assertEqual("Player has correct # extra treasure cards in hand",
		               numTreasureHandAfter, numTreasureHandBefore + MIN(2, numTreasureDeckBefore + numTreasureDiscardBefore), print);
    //  next 3 conditions fail for every test case; comment out to find other bugs
    testPassed *= assertEqual("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1, print);
    testPassed *= assertEqual("Last played card is adventurer", 
                              testG.playedCards[testG.playedCardCount - 1], adventurer, print);
    testPassed *= assertEqual("Player's total cards remained the same", totalCardsTest, totalCardsControl, print); 
    testPassed *= assertEqual("Player has same # actions", testG.numActions, G.numActions, print);
    testPassed *= assertEqual("Player has same # buys", testG.numBuys, G.numBuys, print);
 
    // if test failed, print initial parameters 
    if (!testPassed) {
      printf("TEST FAILED: Seed=%d numActions=%d numBuys=%d handCount=%d deckCount=%d discardCount=%d playedCardCount=%d numTreasure=%d\n", 
             seed, G.numActions, G.numBuys, G.handCount[thisPlayer], G.deckCount[thisPlayer],
             G.discardCount[thisPlayer], G.playedCardCount, numTreasureHandBefore);
    }

    // if running single test, print hand details
    if (testSeed > 0) {
      printf("Hand Before:\n");
      printHand(thisPlayer, &G);
      printf("Hand After\n");
      printHand(thisPlayer, &testG);
    }

  }
}

int main(int argc, char *argv[]) {
  int seed = 0;
  if (argc > 1) {
    seed = atoi(argv[1]);
  }
  testAdventurer(seed);
  return 0;
}
