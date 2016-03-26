Não entendi ainda o uso da yylval.symbol. Segundo a definição, o nodo (da hash table) deve ser associado ao token retornado por ela. Um nodo da hash já tem o token associado como um de seus membros. Talvez esteja por aí o motivo de programas muito simples não serem detectados como corretos (como, por exemplo, 'int a : 5;'). Aparentemente, os tokens não são reconhecidos pelo parser.


