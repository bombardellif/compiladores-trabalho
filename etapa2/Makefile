etapa2: y.tab.c lex.yy.c utils.o
	cc -o etapa2 lex.yy.c y.tab.c hash.c utils.o

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

y.tab.c: parser.y
	bison -d -y parser.y

utils.o: utils.c
	gcc -c utils.c
	
clean:
	rm lex.yy.* y.tab.* *.o etapa2
