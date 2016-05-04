# compiladores-trabalho

1)
No item 'a' diz:
"Todos os identificadores devem ter sido declarados, seja como variável, vetor ou como função. Os símbolos definidos como identificadores na tabela de símbolos devem ter seu tipo trocado para um desses tipos conforme a declaração"

Significa que o campo 'type' deve ser alterado, de SYMBOL_IDENTIFIER (definido em hash.h) para TREE_DECL_SINGLE, TREE_DECL_FUNC ou TREE_DECL_VECT (definidos em tree.h)? Me parece fortemente ser isso, mas não sei se é para reaproveitar os defines da tree.h ou criar novos na hash.h, ou tanto faz.

Por ora, reaproveito os defines da tree.h. E adicionei o dataType (conforme pede o item 'c'), preenchendo-o com o tipo do identificador (se int, char, bool ou real)

2)
char v : 0;
int v : 1;

Por ora, considero redeclaração (erro semântico). Esta interpretação está certa?

