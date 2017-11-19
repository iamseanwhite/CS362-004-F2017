/*
 * unittest2.c
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

int testEndTurn() {
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing endTurn----------------\n");

  printf("TEST 1 - End of player 1's turn (no played cards)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;
  G.playedCardCount = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  endTurn(&testG);
  int totalCardsTestP1 = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer];
  int totalCardsControlP1 = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  int totalCardsTestP2 = testG.discardCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.handCount[otherPlayer];
  int totalCardsControlP2 = G.discardCount[otherPlayer] + G.deckCount[otherPlayer] + G.handCount[otherPlayer];

  myassert("Player 1's hand count is 5", 
	 testG.handCount[thisPlayer], 5);
  myassert("Player 1 has same number of total cards", 
         totalCardsTestP1, totalCardsControlP1);
  myassert("Player 2 is the new player up",
         testG.whoseTurn, otherPlayer);
  myassert("Player 2 has same number of total cards", 
         totalCardsTestP2, totalCardsControlP2);
  myassert("Player 2's hand count is 5", 
	 testG.handCount[otherPlayer], 5);
  myassert("Played card pile is empty", 
	 testG.playedCardCount, 0);


  printf("\nTEST 2 - End of player 1's turn after playing a card\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  otherPlayer = 1;
  G.whoseTurn = thisPlayer;

  // Move a card from player's hand to played card pile
  G.playedCards[0] = G.hand[thisPlayer][G.handCount[thisPlayer - 1]];
  G.playedCardCount++;
  G.handCount[thisPlayer]--;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  endTurn(&testG);
  totalCardsTestP1 = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer];
  totalCardsControlP1 = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  totalCardsTestP2 = testG.discardCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.handCount[otherPlayer];
  totalCardsControlP2 = G.discardCount[otherPlayer] + G.deckCount[otherPlayer] + G.handCount[otherPlayer];

  myassert("Player 1's hand count is 5", 
	 testG.handCount[thisPlayer], 5);
  myassert("Player 1 has same number of total cards", 
         totalCardsTestP1, totalCardsControlP1);
  myassert("Player 2 is the new player up",
         testG.whoseTurn, otherPlayer);
  myassert("Player 2 has same number of total cards", 
         totalCardsTestP2, totalCardsControlP2);
  myassert("Player 2's hand count is 5", 
	 testG.handCount[otherPlayer], 5);
  myassert("Played card pile is empty", 
	 testG.playedCardCount, 0);



  printf("\nTEST 3 - End of player 2's turn (no played cards)\n");

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 1;
  otherPlayer = 0;
  G.whoseTurn = thisPlayer;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  endTurn(&testG);
  totalCardsTestP1 = testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.handCount[thisPlayer];
  totalCardsControlP1 = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.playedCardCount;
  totalCardsTestP2 = testG.discardCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.handCount[otherPlayer];
  totalCardsControlP2 = G.discardCount[otherPlayer] + G.deckCount[otherPlayer] + G.handCount[otherPlayer];

  myassert("Player 1's hand count is 5", 
	 testG.handCount[thisPlayer], 5);
  myassert("Player 1 has same number of total cards", 
         totalCardsTestP1, totalCardsControlP1);
  myassert("Player 1 is the new player up",
         testG.whoseTurn, otherPlayer);
  myassert("Player 2 has same number of total cards", 
         totalCardsTestP2, totalCardsControlP2);
  myassert("Player 2's hand count is 5", 
	 testG.handCount[otherPlayer], 5);
  myassert("Played card pile is empty", 
	 testG.playedCardCount, 0);


  return 0;
}

int main() {
  testEndTurn(); 
 return 0;
}
