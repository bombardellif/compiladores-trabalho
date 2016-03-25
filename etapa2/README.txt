0. Só esboço das coisas. Nada funcional ainda (a não ser em tese reconhecer programas tipo 'a : 5' ou 'int main()'.

1. Arquivo tokens.h é desnecessário, diz a definição.

2. Compilar com o yacc: yacc -d -v parser.y
	Isso gera dois arquivos: y.tab.c e y.tab.h. O último contém pelo que entendi o que seria o conteúdo de tokens.h
	
3. Então, no makefile (professor não soltou [pelo menos ainda, espero] template do Makefile para etapa2), compila-se primeiro o parser e depois o scanner? Isso não faz sentido para mim. Montei um que primeiro usa o scanner.l e depois o parser.y, mas como esperava, ocorrem erros de coisas não declaradas.
