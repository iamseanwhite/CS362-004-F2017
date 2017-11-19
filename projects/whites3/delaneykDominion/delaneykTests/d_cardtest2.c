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

int testAdventurer() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int i;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};
  int totalCardsTest, totalCardsControl;

  printf("----------------- Testing Card: Adventurer----------------\n");

  printf("--TEST 1: Player has two treasure in deck:\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has at least 2 treasure
  while (G.deckCount[thisPlayer] <= 3) {
    G.deck[thisPlayer][G.deckCount[thisPlayer]++] = copper;
  }

  // add some cards to discard pile
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }
  
  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }

  // place adventurer at handpos
  G.hand[thisPlayer][handpos] = adventurer;


  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  int numCoins = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCoins++;
    }
  }

  myassert("Player has 2 extra copper in hand", numCoins, 2);
  myassert("Player has 1 more card in hand (+2 treasure, -adventurer)", testG.handCount[thisPlayer], G.handCount[thisPlayer]+1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is adventurer", testG.playedCards[testG.playedCardCount - 1], adventurer);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 



  printf("\n--TEST 2: Only 1 treasure in deck, at least 1 in discard\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has exactly 1 copper
  for (i = 0; i < 5; i++) {
    G.deck[thisPlayer][i] = duchy;
  }
  G.deck[thisPlayer][5] = copper;
  G.deckCount[thisPlayer] = 6;

  // make sure discard  pile has exactly 1 copper
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = duchy;
  }
  G.discard[thisPlayer][G.discardCount[thisPlayer]++] = copper;  

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }

  // place adventurer at handpos
  G.hand[thisPlayer][handpos] = adventurer;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  // count copper in hand
  numCoins = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCoins++;
    }
  }

  myassert("Player has 2 extra copper in hand", numCoins, 2);
  myassert("Player has 1 more card in hand (+2 treasure, -adventurer)", testG.handCount[thisPlayer], G.handCount[thisPlayer]+1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is adventurer", testG.playedCards[testG.playedCardCount - 1], adventurer);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 



  printf("\n--TEST 3: 0 treasure in deck, at least 2 in discard\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has 0 treasure
  for (i = 0; i < 5; i++) {
    G.deck[thisPlayer][i] = duchy;
  }
  G.deckCount[thisPlayer] = 5;

  // make sure discard  pile has at least 2 copper
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][G.discardCount[thisPlayer]++] = copper;
  }

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }

  // place adventurer at handpos
  G.hand[thisPlayer][handpos] = adventurer;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  // count copper in hand
  numCoins = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCoins++;
    }
  }

  myassert("Player has 2 extra copper in hand", numCoins, 2);
  myassert("Player has 1 more card in hand (+2 treasure, -adventurer)", testG.handCount[thisPlayer], G.handCount[thisPlayer]+1);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is adventurer", testG.playedCards[testG.playedCardCount - 1], adventurer);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  printf("\n--TEST 4: 0 treasure in deck, 1 in discard\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // make sure deck has 0 treasure
  for (i = 0; i < 5; i++) {
    G.deck[thisPlayer][i] = duchy;
  }
  G.deckCount[thisPlayer] = 5;

  // make sure discard  pile has only 1 copper 
  for (i = 0; i < 5; i++) {
    G.discard[thisPlayer][i] = duchy;
  }
  G.discard[thisPlayer][0] = copper; 
  G.discardCount[thisPlayer] = 5;

  // set player's hand
  for (i = 0; i < 5; i++) {
     G.hand[thisPlayer][i] = duchy;
  }

  // place adventurer at handpos
  G.hand[thisPlayer][handpos] = adventurer;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
  totalCardsTest = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.playedCardCount;
  totalCardsControl = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  // count copper in hand
  numCoins = 0;
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ( testG.hand[thisPlayer][i] == copper) {
      numCoins++;
    }
  }

  myassert("Player has only 1 extra copper in hand", numCoins, 1);
  myassert("Player has same # of cards in hand (+1 treasure, -adventurer)", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Played cards increased by 1", testG.playedCardCount, G.playedCardCount + 1);
  myassert("Last played card is adventurer", testG.playedCards[testG.playedCardCount - 1], adventurer);
  myassert("Player's total cards remained the same", totalCardsTest, totalCardsControl); 


  return 0;
}

int main() {
  testAdventurer();
  return 0;
}
