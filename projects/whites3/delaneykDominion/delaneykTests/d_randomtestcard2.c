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

int testVillage(int testSeed) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed, minSeed = 1, maxSeed = 1000000;
  int numPlayers;
  int thisPlayer;
  struct gameState G, testG;
  int totalCardsTest, totalCardsControl;
  int testPassed = 1;
  int print = 0;
  int result;
  printf("----------------- Testing Card: Village ----------------\n");

  if (testSeed > 0) {
    minSeed = testSeed;
    maxSeed = testSeed + 1;
  };

  for (seed = minSeed; seed < maxSeed; seed++) {    

    randomizeGame(seed, &G, &thisPlayer);
  
    // place village at random handpos
    if (G.handCount[thisPlayer] == 0) {
      G.handCount[thisPlayer] = 1;
      handpos = 0;
    }  else
      handpos = rand() %  G.handCount[thisPlayer];
    G.hand[thisPlayer][handpos] = village;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // play card
    result = cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

    // count total cards
    totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
    totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

    // if running single test case, print assertion details
    if (testSeed > 0)
       print = 1; 
    else
       print = 0; 

    // test assertions
    testPassed = 1;
    if (G.deckCount[thisPlayer] > 0 || G.discardCount[thisPlayer] > 0)
      testPassed *= assertEqual("Player has same # cards in hand (-1 village, +1 new)", 
                              testG.handCount[thisPlayer], G.handCount[thisPlayer], print);
    testPassed *= assertEqual("Num ac†ions increased by 2", testG.numActions, G.numActions + 2, print);
    testPassed *= assertEqual("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1, print);
    testPassed *= assertEqual("Last played card is village", 
                             testG.playedCards[testG.playedCardCount - 1], village, print);
    testPassed *= assertEqual("Player's total cards remained the same", totalCardsTest, totalCardsControl, print); 
    testPassed *= assertEqual("Player has +2 actions", testG.numActions, G.numActions + 2, print);
    testPassed *= assertEqual("Player has same # buys", testG.numBuys, G.numBuys, print);
 
    // if test failed, print initial parameters 
    if (!testPassed) {
      printf("TEST FAILED: Seed=%d numActions=%d numBuys=%d handCount=%d deckCount=%d discardCount=%d playedCardCount=%d \n", 
             seed, G.numActions, G.numBuys, G.handCount[thisPlayer], G.deckCount[thisPlayer],
             G.discardCount[thisPlayer], G.playedCardCount);
    }

    // if running single test, print hand details
    /*
    if (testSeed > 0) {
      printf("Hand Before:\n");
      printHand(thisPlayer, &G);
      printf("Hand After\n");
      printHand(thisPlayer, &testG);
    }
    */
  }
}

int main(int argc, char *argv[]) {
  int seed = 0;
  if (argc > 1) {
    seed = atoi(argv[1]);
  }
  testVillage(seed);
  return 0;
}
