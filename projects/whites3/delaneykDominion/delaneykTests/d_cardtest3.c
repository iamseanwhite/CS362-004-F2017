/*
 * cardtest2.c
 *
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int myassert(char* description, int actual, int expected) {
  if (actual == expected) {
    printf("PASS: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 1;
  } else {
    printf("FAIL: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 0;
  }
}


int testMine() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int numCopper = 0, numSilver = 0, numGold = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};
  int totalCardsTest, totalCardsControl;

  printf("----------------- Testing Card: Mine ----------------\n");

  printf("\n--TEST 1: Replace copper with silver\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set player's hand
  handpos = 0;
  choice1 = 1;
  choice2 = silver;
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = mine;
  G.hand[thisPlayer][choice1] = copper;
 

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  // count treasure in hand
  numCopper = numSilver = numGold = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCopper++;
    } else if (testG.hand[thisPlayer][i] == silver) {
      numSilver++;
    } else if (testG.hand[thisPlayer][i] == gold) {
      numGold++;
    }
  }

  myassert("Player has 1 silver", numSilver, 1);
  myassert("Player has 0 copper", numCopper, 0);
  myassert("Player has -1 cards in hand", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is mine", testG.playedCards[testG.playedCardCount - 1], mine);
  myassert("Player's total cards remained the same (+1 silver, -1 copper)", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 2: Replace silver with gold\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set player's hand
  handpos = 0;
  choice1 = 1;
  choice2 = gold;
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = mine;
  G.hand[thisPlayer][choice1] = silver;
 

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  // count treasure in hand
  numCopper = numSilver = numGold = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCopper++;
    } else if (testG.hand[thisPlayer][i] == silver) {
      numSilver++;
    } else if (testG.hand[thisPlayer][i] == gold) {
      numGold++;
    }
  }

  myassert("Player has 1 gold", numGold, 1);
  myassert("Player has 0 silver", numSilver, 0);
  myassert("Player has -1 cards in hand", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is mine", testG.playedCards[testG.playedCardCount - 1], mine);
  myassert("Player's total cards remained the same (+1 gold, -1 silver)", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 3: Replace copper with silver (more than 1 copper in hand) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set player's hand
  handpos = 0;
  choice1 = 1;
  choice2 = silver;
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = mine;
  G.hand[thisPlayer][choice1] = copper;
  G.hand[thisPlayer][2] = copper;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  // count treasure in hand
  numCopper = numSilver = numGold = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCopper++;
    } else if (testG.hand[thisPlayer][i] == silver) {
      numSilver++;
    } else if (testG.hand[thisPlayer][i] == gold) {
      numGold++;
    }
  }

  myassert("Player has 1 silver", numSilver, 1);
  myassert("Player has 1 copper", numCopper, 1);
  myassert("Player has -1 cards in hand", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is mine", testG.playedCards[testG.playedCardCount - 1], mine);
  myassert("Player's total cards remained the same (+1 silver, -1 copper)", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 4: Try to replace copper with gold) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set player's hand
  handpos = 0;
  choice1 = 1;
  choice2 = gold;
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = mine;
  G.hand[thisPlayer][choice1] = copper;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  // count treasure in hand
  numCopper = numSilver = numGold = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCopper++;
    } else if (testG.hand[thisPlayer][i] == silver) {
      numSilver++;
    } else if (testG.hand[thisPlayer][i] == gold) {
      numGold++;
    }
  }

  myassert("Player has 0 silver", numSilver, 0);
  myassert("Player still has 1 copper", numCopper, 1);
  myassert("Player still has 0 gold", numGold, 0);
  myassert("Player has same # cards in hand", testG.handCount[thisPlayer], G.handCount[thisPlayer] );
  myassert("Played cards stayed the same", testG.playedCardCount, G.playedCardCount );
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 



  return 0;
}

int main() {
  testMine();
  return 0;
}
