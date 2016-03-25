etapa2: y.tab.c lex.yy.c
	cc -o etapa2 lex.yy.c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y
	
hash.o: hash.c
	gcc -c hash.c
		
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
	
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

utils.o: utils.c
	gcc -c utils.c
	
clean:
	rm lex.yy.* y.tab.* y.output hash.o etapa2
