etapa6: lex.yy.c y.tab.c hash.o tree.o semantics.o tac.o code-gen.o
	gcc -o etapa6 lex.yy.c y.tab.c hash.o tree.o semantics.o tac.o code-gen.o

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

y.tab.c: parser.y
	bison -d -y parser.y

hash.o: hash.c
	gcc -c hash.c

tree.o: tree.c
	gcc -c tree.c

semantics.o: semantics.c
	gcc -c semantics.c

tac.o: tac.c
	gcc -c tac.c

code-gen.o: code-gen.c
	gcc -c code-gen.c

clean:
	rm -f lex.yy.* y.tab.* *.o etapa6
