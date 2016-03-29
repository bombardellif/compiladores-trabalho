--
Pergunta: Uma chamada de função não deveria ser também um comando simples??
Segundo a especificação não se pode simplesmente chamar uma função fora de
atribuições.

--

Resposta do Johann: sim, não se pode simplesmente chamar uma função fora de atribuições.

Não pode haver declarações do tipo char a:'8'; nem bool b:'FALSE'; Só são permitidos inteiros, mesmo que o tipo seja diferente.

Funcionalidade C não será mais cobrada nesta etapa.

Corrigidos bugs e corrigindo outros.

Main.c fora do parser.y (Johann disse que isso não é obrigatório, mas preferível; vou deixar para o final, portanto)
