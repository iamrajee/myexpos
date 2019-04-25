all:	sim

lex.yy.c: data.h instr.h decode.lex
	flex -i decode.lex

sim:	simulator.c lex.yy.c
	gcc -o sim simulator.c

clean:
	rm lex.yy.c sim
