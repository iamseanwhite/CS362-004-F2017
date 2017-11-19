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


int testMine(int testSeed) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed, minSeed = 1, maxSeed = 1000000;
  int thisPlayer;
  struct gameState G, testG;
  int totalCardsTest, totalCardsControl, numTreasureHandBefore, numTreasureHandAfter;
  int numCopperBefore, numSilverBefore, numGoldBefore, numCopperAfter, numSilverAfter, numGoldAfter;
  int testPassed = 1;
  int print = 0;
  int divisor;
  int result;
  printf("----------------- Testing Card: Mine----------------\n");

  if (testSeed > 0) {
    minSeed = testSeed;
    maxSeed = testSeed + 1;
  };

  for (seed = minSeed; seed < maxSeed; seed++) {    
  
    randomizeGame(seed, &G, &thisPlayer);

    // place mine at random handpos
    if (G.handCount[thisPlayer] == 0) {
      G.handCount[thisPlayer] = 0;
      handpos = 0;
    }  else
      handpos = rand() %  G.handCount[thisPlayer];
    G.hand[thisPlayer][handpos] = mine;

  
    // random choice1 and choice2
    if (G.handCount[thisPlayer] > 0)
      choice1 = rand() % G.handCount[thisPlayer]; 
    else
      choice1 = 0;
    choice2 = rand() % (treasure_map + 3) - 1;     

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // play card
    result = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

    // count total cards
    totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] +
testG.playedCardCount;
    totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

    // count treasure 
    numCopperBefore = numSilverBefore = numGoldBefore = numTreasureHandBefore = 0;;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
      if (G.hand[thisPlayer][i] == copper) {
        numCopperBefore++;
	numTreasureHandBefore++;
      } else if (G.hand[thisPlayer][i] == silver) {
        numSilverBefore++;
	numTreasureHandBefore++;
      } else if (G.hand[thisPlayer][i] == gold) {
        numGoldBefore++;
	numTreasureHandBefore++;
      }
    }
    numCopperAfter = numSilverAfter = numGoldAfter = numTreasureHandAfter = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
      if (testG.hand[thisPlayer][i] == copper) {
        numCopperAfter++;
	numTreasureHandAfter++;
      } else if (testG.hand[thisPlayer][i] == silver) {
        numSilverAfter++;
	numTreasureHandAfter++;
      } else if (testG.hand[thisPlayer][i] == gold) {
        numGoldAfter++;
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
    testPassed *= assertEqual("Player has same # cards in hand", 
                              testG.handCount[thisPlayer], G.handCount[thisPlayer], print);
    testPassed *= assertEqual("Player has same # treasure cards in hand",
		               numTreasureHandAfter, numTreasureHandBefore, print);
    if (G.hand[thisPlayer][choice1] == copper && choice2 == silver) {
      testPassed *= assertEqual("Player has -1 copper", numCopperAfter, numCopperBefore - 1, print);
      testPassed *= assertEqual("Player has +1 silver", numSilverAfter, numSilverBefore + 1, print);
      testPassed *= assertEqual("Player has same gold", numGoldAfter, numGoldBefore, print);
    } else if (G.hand[thisPlayer][choice1] == silver && choice2 == gold) {
      testPassed *= assertEqual("Player has same copper", numCopperAfter, numCopperBefore, print);
      testPassed *= assertEqual("Player has -1 silver", numSilverAfter, numSilverBefore - 1, print);
      testPassed *= assertEqual("Player has +1 gold", numGoldAfter, numGoldBefore + 1, print);
    } else {
continue;
      testPassed *= assertEqual("cardEffect returned -1", result, -1, print);
      testPassed *= assertEqual("Player has same copper", numCopperAfter, numCopperBefore - 1, print);
      testPassed *= assertEqual("Player has same silver", numSilverAfter, numSilverBefore + 1, print);
      testPassed *= assertEqual("Player has same gold", numGoldAfter, numGoldBefore, print);
    }
    if ((choice2 != copper) && (choice2 != silver) && (choice2 != gold)) {
      testPassed *= assertEqual("Invalid choice2 returns -1", result, -1, print);
    }
    if (G.supplyCount[choice2] <= 0) {
      testPassed *= assertEqual("Choice2 out of supply returns -1", result, -1, print);
    }
    // next three assertions always fail, comment out to find other bugs
    testPassed *= assertEqual("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1, print);
    testPassed *= assertEqual("Last played card is mine", 
                             testG.playedCards[testG.playedCardCount - 1], mine, print);
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
      printf("choice 1: %d choice1 card %d  choice2 -> %d\n", choice2, G.hand[thisPlayer][choice1],  choice2);
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
  testMine(seed);
  return 0;
}
