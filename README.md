# Ling_Par_My_Lang
Minha linguagem tem foco em ser fácil de usar e intuitiva, para criar varíavel por exemplo, o comando é :
remember var as 4;
que é a mesma coisa que fazer:
var = 4;
apesar de precisar de mais linhas de código optei por tentar fazer uma linguagem intuitiva de usar, outra funcionalidade legal é o debug:
remember x as 4; 
$ if( x>1){
  x+=4
  }$

o debug imprime no terminal o que está acontecendo em cada linha, começando no primeiro uso do termo $ até o segundo uso do termo $, neste exemplo imprimiria:
" condicao satisfeita, x = 4/ 4>1/ linha 2"
" x=4/ x+=1/ 4+1/ x=5/ linha 3 "


# EBNF
(* Programa principal: zero ou mais statements, seguido de 'end;' *)
<program>         ::= { <statement> } "end" ";" ;

(* Qualquer statement válido na linguagem *)
<statement>       ::= <create_variable>
                    | <delete_variable>
                    | <if_statement>
                    | <while_loop>
                    | <repeat_loop>
                    | <print_statement>
                    | <debug_block>
                    ;

(* Criação e deleção de variáveis *)
<create_variable> ::= "remember" <identifier> "as" <expression> ";" ;
<delete_variable> ::= "forget" <identifier> ";" ;

(* Condicional com suporte a else-if e else simples *)
<if_statement>    ::=
                      "if" "(" <expression> ")" <block>
                      { "else if" "(" <expression> ")" <block> }
                      [ "else" <block> ]
                    ;

(* Loop padrão while *)
<while_loop>      ::= "while" "(" <expression> ")" "repeat" <block> ;

(* Repetição fixa de N vezes *)
<repeat_loop>     ::= "run" "(" <number> ")" <block> ;

(* Impressão de valores *)
<print_statement> ::= "show" "(" <expression> ")" ";" ;

(* Bloco de debug que ativa saída linha a linha *)
<debug_block>     ::= "$" { <statement> } "$" ;

(* Bloco genérico delimitado por chaves *)
<block>           ::= "{" { <statement> } "}" ;

(* Expressões aritméticas e lógicas com precedência básica *)
<expression>      ::= <relational> ;
<relational>      ::= <additive> { ( "==" | "!=" | "<" | ">" | "<=" | ">=" ) <additive> } ;
<additive>        ::= <multiplicative> { ( "+" | "-" ) <multiplicative> } ;
<multiplicative>  ::= <primary> { ( "*" | "/" ) <primary> } ;
<primary>         ::= <number>
                    | <identifier>
                    | "(" <expression> ")"
                    ;

(* Identificadores e números *)
<identifier>      ::= <letter> { <letter> | <digit> | "_" } ;
<number>          ::= <digit> { <digit> } ;

<digit>           ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
<letter>          ::= "a" … "z" | "A" … "Z" ;

## Análise Léxica

Definição dos tokens, suas expressões regulares e descrições:

| Token         | Expressão Regular      | Descrição                                             |
| ------------- | ---------------------- | ----------------------------------------------------- |
| `KW_REMEMBER` | `remember`             | Palavra‑reservada `remember`                          |
| `KW_AS`       | `as`                   | Palavra‑reservada `as`                                |
| `KW_FORGET`   | `forget`               | Palavra‑reservada `forget`                            |
| `KW_IF`       | `if`                   | Palavra‑reservada `if`                                |
| `KW_ELSE`     | `else`                 | Palavra‑reservada `else`                              |
| `KW_WHILE`    | `while`                | Palavra‑reservada `while`                             |
| `KW_REPEAT`   | `repeat`               | Palavra‑reservada `repeat`                            |
| `KW_RUN`      | `run`                  | Palavra‑reservada `run`                               |
| `KW_SHOW`     | `show`                 | Palavra‑reservada `show`                              |
| `KW_END`      | `end`                  | Palavra‑reservada `end`                               |
| `OP_EQ`       | `==`                   | Operador de igualdade                                 |
| `OP_NEQ`      | `!=`                   | Operador de desigualdade                              |
| `OP_GTE`      | `>=`                   | Operador “maior ou igual”                             |
| `OP_LTE`      | `<=`                   | Operador “menor ou igual”                             |
| `OP_GT`       | `>`                    | Operador “maior que”                                  |
| `OP_LT`       | `<`                    | Operador “menor que”                                  |
| `OP_PLUS`     | `\+`                   | Operador de soma                                      |
| `OP_MINUS`    | `-`                    | Operador de subtração                                 |
| `OP_MUL`      | `\*`                   | Operador de multiplicação                             |
| `OP_DIV`      | `/`                    | Operador de divisão                                   |
| `LPAREN`      | `\(`                   | Parêntese esquerdo                                    |
| `RPAREN`      | `\)`                   | Parêntese direito                                     |
| `LBRACE`      | `{`                    | Chave abre                                            |
| `RBRACE`      | `}`                    | Chave fecha                                           |
| `SEMICOLON`   | `;`                    | Ponto‑e‑vírgula                                       |
| `DOLLAR`      | `\$`                   | Símbolo `$` (início/fim de bloco de debug)            |
| `IDENTIFIER`  | `[A-Za-z][A-Za-z0-9_]*`| Nome de variável (letra seguida de letras/dígitos/_)  |
| `NUMBER`      | `[0-9]+`               | Sequência de dígitos (inteiro)                        |
| `WHITESPACE`  | `[ \t\r\n]+`           | Espaços em branco, tabs e quebras de linha (ignorar) |


# Análise Sintatica
A sintaxe da minha linguagem foi organizada de modo a permitir um parser LL(1). Para cada construtor de comando (remember, forget, if, while, run, show, bloco de debug $…$ ou ponto‑e‑vírgula isolado), existe um token inicial distinto, de forma que não há ambiguidades de previsão.

As expressões aritmético‑lógicas foram estruturadas em dois níveis:

term, que reconhece o átomo (identificador, literal inteiro ou sub‑expressão entre parênteses),

expression, que repete a aplicação de operadores binários sobre esses termos.

Dessa forma, eliminamos recursão à esquerda direta e garantimos associatividade à esquerda com precedência única para todos os operadores.
