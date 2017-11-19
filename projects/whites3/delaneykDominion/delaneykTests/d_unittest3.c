/*
 * unittest3.c
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


int testUpdateCoins() {
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};

  printf("----------------- Testing updateCoins ----------------\n");

  printf("\nTEST 1: Player has 1 copper, 1 silver, 1 gold, 2 duchies (no bonus) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  // give player 1 copper, 1 silver, 1 gold, 2 duchies
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = silver;
  G.hand[thisPlayer][2] = gold;
  G.hand[thisPlayer][3] = duchy;
  G.hand[thisPlayer][4] = duchy;
  G.handCount[thisPlayer] = 5;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, 0);

  myassert("Coins == 6", testG.coins, 6);


  printf("\nTEST 2: Player has 2 copper, 3 silver, 4 gold (no bonus) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  // give player 2 copper, 3 silver, 4 gold
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = silver;
  G.hand[thisPlayer][3] = silver;
  G.hand[thisPlayer][4] = silver;
  G.hand[thisPlayer][5] = gold;
  G.hand[thisPlayer][6] = gold;
  G.hand[thisPlayer][7] = gold;

  G.handCount[thisPlayer] = 8;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, 0);

  myassert("Coins == 17", testG.coins, 17);

  printf("\nTEST 3: Player has 2 copper, 3 silver, 4 gold ( +3  bonus) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  // give player 2 copper, 3 silver, 4 gold
  G.hand[thisPlayer][0] = copper;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = silver;
  G.hand[thisPlayer][3] = silver;
  G.hand[thisPlayer][4] = silver;
  G.hand[thisPlayer][5] = gold;
  G.hand[thisPlayer][6] = gold;
  G.hand[thisPlayer][7] = gold;

  G.handCount[thisPlayer] = 8;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, 3);

  myassert("Coins == 20", testG.coins, 20);


  printf("\nTEST 4: Player has no cards ( +3  bonus) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  G.handCount[thisPlayer] = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, 3);

  myassert("Coins == 3", testG.coins, 3);

  printf("\nTEST 5: Player has no cards (no  bonus) \n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  G.handCount[thisPlayer] = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, 0);

  myassert("Coins == 0", testG.coins,  0);


  return 0;
}

int main() {
  testUpdateCoins(); 
 return 0;
}
