#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_PLAYED 6
#define MAX_ACTIONS 10
#define MAX_BUYS 10
#define NUM_TOTAL_CARDS 16

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int assertEqual(char* description, int actual, int expected, int print) {
  if (actual == expected) {
//    if (print)  printf("PASS: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 1;
  } else {
    if (print) printf("  FAIL: %s\n  actual == %d, expected == %d\n", description, actual, expected);
    return 0;
  }
}

/* Arrange the N elements of ARRAY in random order.
   From https://stackoverflow.com/a/6127606 */
void shuffleArray(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void randomizeGame(int seed, struct gameState *G, int *thisPlayer) {
  int i;
  int numPlayers;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy, council_room};
  int allCards[NUM_TOTAL_CARDS] = {adventurer, embargo, village, minion, mine, cutpurse,
                      sea_hag, tribute, smithy, council_room, duchy, estate,
                      province, copper, silver, gold};
  int maxDiscard;
  int divisor;
  srand(seed);

  // randomize parameters for initializeG->me
  shuffleArray(k, 10);
  do {
    numPlayers = rand() % MAX_PLAYERS;
  } while (numPlayers < 2);
  *thisPlayer = rand() % numPlayers;

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, G);
  G->whoseTurn = *thisPlayer;

  // random deck
  G->deckCount[*thisPlayer] = rand() % MAX_HAND;
  for (i = 0; i < G->deckCount[*thisPlayer]; i++) {
    G->deck[*thisPlayer][i] = allCards[rand() % NUM_TOTAL_CARDS];
  }

  // random hand
  divisor = MAX_HAND - G->deckCount[*thisPlayer];
  if (divisor)
    G->handCount[*thisPlayer] = rand() % divisor;
  else
    G->handCount[*thisPlayer] = 0;
  for (i = 0; i < G->handCount[*thisPlayer]; i++) {
    G->hand[*thisPlayer][i] = allCards[rand() % NUM_TOTAL_CARDS];
  }

  // random discard pile
  maxDiscard = MAX_HAND - G->deckCount[*thisPlayer] - G->handCount[*thisPlayer];
  G->discardCount[*thisPlayer] = rand() % maxDiscard;
  for (i = 0; i < G->discardCount[*thisPlayer]; i++) {
    G->discard[*thisPlayer][i] = allCards[rand() % NUM_TOTAL_CARDS];
  }
  // random played card pile
  G->playedCardCount = rand() % MAX_PLAYED;
  for (i = 0; i < G->playedCardCount; i++) {
    G->playedCards[i] = k[rand() % 10];
  }

  // random numActions and numBuys
  G->numBuys = rand() % MAX_BUYS;
  G->numActions = rand() % MAX_ACTIONS;
}








































