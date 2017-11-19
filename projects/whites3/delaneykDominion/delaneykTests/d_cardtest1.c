/*
 * cardtest1.c
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

int testSmithy() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};
  int totalCardsTest, totalCardsControl;

  printf("----------------- Testing Card: Smithy ----------------\n");

  printf("--TEST 1: More than 3 cards in deck:\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has more than 3 cards
  while (G.deckCount[thisPlayer] <= 3) {
    G.deck[thisPlayer][G.deckCount[thisPlayer]++] = duchy;
  }

  // add some cards to discard pile
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }

  // place smithy at handpos
  G.hand[thisPlayer][handpos] = smithy;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  printf("%d\n", testG.playedCardCount);
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  printf("%d\n", testG.playedCardCount);

  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer]+ testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has 2 more cards in hand (+3 new, -smithy)", testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
  myassert("Player has 3 less cards in deck", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]-3);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is smithy", testG.playedCards[testG.playedCardCount - 1], smithy);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 



  printf("\n--TEST 2: Exactly 3 cards in deck\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has exactly 3 cards
  while (G.deckCount[thisPlayer] < 3) {
    G.deck[thisPlayer][G.deckCount[thisPlayer]++] = duchy;
  }
  G.deckCount[thisPlayer] = 3; // if deck had more than 3, set deck count to 3
 
  // add some cards to discard pile
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }


  // place smith at handpos
  G.hand[thisPlayer][handpos] = smithy;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has 2 more cards in hand (+3 new, -smithy)", 
         testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
  myassert("Player has 3 less cards in deck", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]-3);
  myassert("Played cards increased by 1", 
         testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is smithy", testG.playedCards[testG.playedCardCount - 1], smithy);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 3: Less than 3 cards in deck\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has exactly 2 cards
  while (G.deckCount[thisPlayer] <= 2) {
    G.deck[thisPlayer][G.deckCount[thisPlayer]++] = duchy;
  }
  G.deckCount[thisPlayer] = 2;

  // add some cards to discard pile
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }

  // place smithy at handpos
  G.hand[thisPlayer][handpos] = smithy;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;

  myassert("Player has 2 more cards in hand (+3 new, -smithy)", 
         testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
  myassert("Played cards increased by 1", 
         testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is smithy", testG.playedCards[testG.playedCardCount - 1], smithy);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  return 0;
}

int main() {
  testSmithy();
  return 0;
}
