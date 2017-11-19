/*
 * unittest1.c
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

int testGainCard() {
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffledCards = 0;

  int i, j, m;
  int supplyPos= 0, toFlag = 0;
  int remove1, remove2;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("----------------Testing gainCard----------------\n");


  printf("\nTEST 1 - Add card to player's deck\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  toFlag = 1;
  supplyPos = 0;
  gainCard(supplyPos, &testG, toFlag, thisPlayer);

  myassert("Player's deck count increases by 1", 
	 testG.deckCount[thisPlayer], (G.deckCount[thisPlayer] + 1));
  myassert("Card in last deck position is correct card", 
	 testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1], supplyPos);
  myassert("Player's hand  count remains the same", 
	 testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  myassert("Player's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Opponent's hand count remains the same", 
	 testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  myassert("Opponent's deck count remains the same", 
	 testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  myassert("Opponent's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Supply of added card is reduced by 1", 
	 testG.supplyCount[supplyPos], (G.supplyCount[supplyPos] - 1));

  printf("\nTEST 2 - Add card to player's hand\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  toFlag = 2;
  supplyPos = 0;
  gainCard(supplyPos, &testG, toFlag, thisPlayer);

  myassert("Player's hand count increases by 1", 
	 testG.handCount[thisPlayer], (G.handCount[thisPlayer] + 1));
  myassert("Card in last hand position is correct card", 
	 testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], supplyPos);
  myassert("Player's deck count remains the same", 
	 testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  myassert("Player's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Opponent's hand count remains the same", 
	 testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  myassert("Opponent's deck count remains the same", 
	 testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  myassert("Opponent's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Supply of added card is reduced by 1", 
	 testG.supplyCount[supplyPos], (G.supplyCount[supplyPos] - 1));

  printf("\nTEST 3 - Add card to player's discard pile\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  toFlag = 0;
  supplyPos = 0;
  gainCard(supplyPos, &testG, toFlag, thisPlayer);

  myassert("Player's discard count increases by 1", 
	 testG.discardCount[thisPlayer], (G.discardCount[thisPlayer] + 1));
  myassert("Card in last discard position is correct card", 
	 testG.discard[thisPlayer][testG.deckCount[thisPlayer] - 1], supplyPos);
  myassert("Player's hand  count remains the same", 
	 testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count remains the same", 
	 testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Opponent's hand count remains the same", 
	 testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  myassert("Opponent's deck count remains the same", 
	 testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  myassert("Opponent's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Supply of added card is reduced by 1", 
	 testG.supplyCount[supplyPos], (G.supplyCount[supplyPos] - 1));

  printf("\nTEST 4 - Try card with no supply left\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  toFlag = 1;
  supplyPos = 0;
  testG.supplyCount[0] = 0;
  gainCard(supplyPos, &testG, toFlag, thisPlayer);

  myassert("Player's hand count remains the same", 
	 testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  myassert("Player's deck count remains the same", 
	 testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  myassert("Player's discard count remains the same", 
	 testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  myassert("Opponent's hand count remains the same", 
	 testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  myassert("Opponent's deck count remains the same", 
	 testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  myassert("Opponent's discard count remains the same", 
	 testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  myassert("Supply of added card is still 0", 
	 testG.supplyCount[supplyPos], 0);

  return 0;
}

int main() {
  testGainCard(); 
 return 0;
}
