/*
 * unittest4.c
 *
 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int myassert(char* description, int actual, int expected) {
  if (actual == expected) {
    printf("PASS: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 1;
  } else {
    printf("FAIL: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 0;
  }
}

int testBuyCard() {
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};


  printf("----------------- Testing buyCard ----------------\n");

  printf("TEST 1: Player has 4 tokens and 1 buy; buys cutpurse (4 tokens)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // Give player 4 copper
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;
  G.coins = 4;
  G.outpostPlayed = 0;
  G.phase = 0;
  G.numBuys = 1;
  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  buyCard(cutpurse, &testG);
  
  myassert("Player's buy count is 0", testG.numBuys, 0);
  myassert("Player's discard count is +1", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
  myassert("Final card in player's discard pile is cutpurse",
          testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1], cutpurse);
  myassert("Player's hand count is the same", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count is the same", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Coins, 0", testG.coins, 0);
  myassert("Phase is now 1", testG.phase, 1);
  myassert("Cutpurse supply reduced by 1", testG.supplyCount[cutpurse], G.supplyCount[cutpurse] - 1);


  printf("\nTEST 2: Player has 4 tokens and 2 buys; buys village (3 tokens)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // Give player 4 copper
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;
  G.coins = 4;
  G.outpostPlayed = 0;
  G.phase = 0;
  G.numBuys = 2;
  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  buyCard(village, &testG);
  
  myassert("Player's buy count is 1", testG.numBuys, 1);
  myassert("Player's discard count is +1", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
  myassert("Final card in player's discard pile is village",
          testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1], village);
  myassert("Player's hand count is the same", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count is the same", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Coins, 1", testG.coins, 1);
  myassert("Phase is now 1", testG.phase, 1);
  myassert("Village supply reduced by 1", testG.supplyCount[village], G.supplyCount[village] - 1);


  printf("\nTEST 3: Player has 4 tokens and 1 buy; tries to buy mine (5 tokens)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // Give player 4 copper
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;
  G.coins = 4;
  G.outpostPlayed = 0;
  G.phase = 0;
  G.numBuys = 1;
  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  int returnVal = buyCard(mine, &testG);
  
  myassert("Function return value is -1", returnVal, -1);
  myassert("Player's buy count is still 1", testG.numBuys, 1);
  myassert("Player's discard count is the same", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  myassert("Player's hand count is the same", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count is the same", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Coins still equal 4", testG.coins, 4);
  myassert("Mine supply unchanged", testG.supplyCount[mine], G.supplyCount[mine]);


  printf("\nTEST 4: Player has 4 tokens and 0 buys; tries to buy cutpurse (4 tokens)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // Give player 4 copper
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;
  G.coins = 4;
  G.outpostPlayed = 0;
  G.phase = 0;
  G.numBuys = 0;
  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  buyCard(cutpurse, &testG);

  myassert("Function return value is -1", returnVal, -1);
  myassert("Player's buy count is still 0", testG.numBuys, 0);
  myassert("Player's discard count is the same", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  myassert("Player's hand count is the same", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count is the same", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Coins still equal 4", testG.coins, 4);
  myassert("Cutpurse supply unchanged", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);


  printf("\nTEST 5: Player has 4 tokens and 1 buy; tries to buy cutpurse (out of supply)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // Give player 4 copper
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;
  G.coins = 4;
  G.outpostPlayed = 0;
  G.phase = 0;
  G.numBuys = 1;
  G.playedCardCount = 0;
  G.supplyCount[cutpurse] = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  buyCard(cutpurse, &testG);

  myassert("Function return value is -1", returnVal, -1);
  myassert("Player's buy count is still 1", testG.numBuys, 1);
  myassert("Player's discard count is the same", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  myassert("Player's hand count is the same", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count is the same", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Coins still equal 4", testG.coins, 4);
  myassert("Cutpurse supply unchanged", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);



  return 0;
}

int main() {
  testBuyCard(); 
 return 0;
}
