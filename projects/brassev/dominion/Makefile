CFLAGS= -Wall -fpic -coverage -lm -std=c99 -g
.PHONY=unittestresults
# Unit Tests:
unit%: tests/unittest%.c dominion.c rngs.c
	gcc -o $@ $^ $(CFLAGS)

unit%.out: unit%
	$^ >> $@
	gcov -b dominion.c >> $@
#	cat dominion.c.gcov >> $@

card%: tests/cardtest%.c dominion.c rngs.c
	gcc -o $@ $^ $(CFLAGS)

card%.out: card%
	$^ >> $@
	gcov -b dominion.c >> $@
#	cat dominion.c.gcov >> $@

unittestresults: unit1.out unit2.out unit3.out unit4.out card1.out card2.out card3.out card4.out
	cat unit1.out >> unittestresults.out
	cat unit2.out >> unittestresults.out
	cat unit3.out >> unittestresults.out
	cat unit4.out >> unittestresults.out

	cat card1.out >> unittestresults.out
	cat card2.out >> unittestresults.out
	cat card3.out >> unittestresults.out
	cat card4.out >> unittestresults.out
#	@$(foreach unit, $^, cat $(unit) >> unittestresults.out)


# Random Tests:
randomtestcard%: tests/randomtestcard%.c dominion.c rngs.c tests/common.c
	gcc -o $@ $^ $(CFLAGS)

randomtestcard%.out: randomtestcard%
	$^ >> $@
	gcov -b dominion.c >> $@


# Normal:
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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unit* card* random*
