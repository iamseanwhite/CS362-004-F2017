CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittest1result.out
	gcov -f -b dominion.c >> unittest1result.out
	cat dominion.c.gcov >> unittest1result.out
	
	rm -f dominion.gcda
	
	
	./unittest2 &> unittest2result.out
	gcov -f -b dominion.c >> unittest2result.out
	cat dominion.c.gcov >> unittest2result.out
	
	rm -f dominion.gcda
	
	 
	./unittest3 &> unittest3result.out 
	gcov -f -b dominion.c >> unittest3result.out
	cat dominion.c.gcov >> unittest3result.out
	
	rm -f dominion.gcda
	
	 
	./unittest4 &> unittest4result.out 
	gcov -f -b dominion.c >> unittest4result.out
	cat dominion.c.gcov >> unittest4result.out
	
	rm -f dominion.gcda
	
	 
	./cardtest1 &> cardtest1result.out 
	gcov -f -b dominion.c >> cardtest1result.out
	cat dominion.c.gcov >> cardtest1result.out
	
	rm -f dominion.gcda
	
	 
	./cardtest2 &> cardtest2result.out 
	gcov -f -b dominion.c >> cardtest2result.out
	cat dominion.c.gcov >> cardtest2result.out
	
	rm -f dominion.gcda
	
	 
	./cardtest3 &> cardtest3result.out 
	gcov -f -b dominion.c >> cardtest3result.out
	cat dominion.c.gcov >> cardtest3result.out
	
	rm -f dominion.gcda
	
	 
	./cardtest4 &> cardtest4result.out 
	gcov -f -b dominion.c >> cardtest4result.out
	cat dominion.c.gcov >> cardtest4result.out
	
	rm -f dominion.gcda
	
randomtestcard1.out: randomtestcard1 
	./randomtestcard1 &> randomtestcard1.out
	gcov -f -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	
	rm -f dominion.gcda
	
randomtestcard2.out: randomtestcard2 
	./randomtestcard2 &> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
	rm -f dominion.gcda
	
randomtestadventurer.out: randomtestadventurer 
	./randomtestadventurer &> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
	rm -f dominion.gcda
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

	
testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 
clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
