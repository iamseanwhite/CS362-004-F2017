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

int testVillage() {
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

  printf("----------------- Testing Card: Village ----------------\n");

  printf("\n--TEST 1: Player has cards in deck, 1 action \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = village;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has smae # cards in hand (+1 new, -village)", testG.handCount[thisPlayer], G.handCount[thisPlayer] );
  myassert("# actions increased by 2 ", testG.numActions, G.numActions + 2);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is village", testG.playedCards[testG.playedCardCount - 1], village);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 2: Player has cards in deck, 2 actions\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  G.numActions = 2;;

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = village;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has same # cards in hand (+1 new, -village)", testG.handCount[thisPlayer], G.handCount[thisPlayer] );
  myassert("# actions increased by 2 ", testG.numActions, G.numActions + 2);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is village", testG.playedCards[testG.playedCardCount - 1], village);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 3: Player has cards no cards in deck, 1 action \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  G.numActions = 1;

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }
  G.hand[thisPlayer][handpos] = village;

  G.deckCount[thisPlayer] = 0;

  // add some cards to discard pile
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has same # cards in hand (+1 new, -village)", testG.handCount[thisPlayer], G.handCount[thisPlayer] );
  myassert("# actions increased by 2 )", testG.numActions, G.numActions + 2);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is village", testG.playedCards[testG.playedCardCount - 1], village);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  return 0;
}

int main() {
  testVillage();
  return 0;
}
