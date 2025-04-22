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
programa         = { statement } "end" ";" ;

statement        = create_variable
                 | delete_variable
                 | conditional
                 | loop
                 | repeat_n_times
                 | print
                 | debug_block
                 | ";" ;

create_variable  = "remember" identifier "as" expression ";" ;
delete_variable  = "forget" identifier ";" ;

conditional      = "if" "(" expression ")" block [ "else" "(" expression ")" block ] ;

loop             = "while" "(" expression ")" "repeat" block ;

repeat_n_times   = "run" "(" number ")" block ;

print            = "show" "(" expression ")" ";" ;

debug_block      = "$" { statement } "$" ;

block            = "{" { statement } "}" ;

expression       = term { ("+" | "-" | "*" | "/" 
                         | ">" | "<" | "==" | "!=" | ">=" | "<=") term } ;

term             = identifier
                 | number
                 | "(" expression ")" ;

identifier       = letter { letter | "_" | digit } ;
number           = digit { digit } ;
digit            = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
letter           = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i"
                 | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r"
                 | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
                 | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I"
                 | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R"
                 | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" ;
# Análise Léxica

Token | Regex | Descrição
KW_REMEMBER | remember | Palavra‑reservada “remember”
KW_AS | as | Palavra‑reservada “as”
KW_FORGET | forget | Palavra‑reservada “forget”
KW_IF | if | Palavra‑reservada “if”
KW_ELSE | else | Palavra‑reservada “else”
KW_WHILE | while | Palavra‑reservada “while”
KW_REPEAT | repeat | Palavra‑reservada “repeat”
KW_RUN | run | Palavra‑reservada “run”
KW_SHOW | show | Palavra‑reservada “show”
KW_END | end | Palavra‑reservada “end”
OP_EQ | == | Operador de igualdade
OP_NEQ | != | Operador de desigualdade
OP_GTE | >= | Operador “maior ou igual”
OP_LTE | <= | Operador “menor ou igual”
OP_GT | > | Operador “maior que”
OP_LT | < | Operador “menor que”
OP_PLUS | \+ | Operador soma
OP_MINUS | - | Operador subtração
OP_MUL | \* | Operador multiplicação
OP_DIV | / | Operador divisão
LPAREN | \( | Parêntese esquerdo
RPAREN | \) | Parêntese direito
LBRACE | { | Chave abre
RBRACE | } | Chave fecha
SEMICOLON | ; | Ponto‑e‑vírgula
DOLLAR | \$ | Símbolo $ (início/fim de bloco de debug)
IDENTIFIER | [A-Za-z][A-Za-z0-9_]* | Nome de variável (letra seguida de letras/dígitos/underscore)
NUMBER | [0-9]+ | Sequência de dígitos (inteiro)
WHITESPACE | [ \t\r\n]+ | Espaços em branco, tabs e quebras de linha (ignorar)

# Análise Sintatica
A sintaxe da minha linguagem foi organizada de modo a permitir um parser LL(1). Para cada construtor de comando (remember, forget, if, while, run, show, bloco de debug $…$ ou ponto‑e‑vírgula isolado), existe um token inicial distinto, de forma que não há ambiguidades de previsão.

As expressões aritmético‑lógicas foram estruturadas em dois níveis:

term, que reconhece o átomo (identificador, literal inteiro ou sub‑expressão entre parênteses),

expression, que repete a aplicação de operadores binários sobre esses termos.

Dessa forma, eliminamos recursão à esquerda direta e garantimos associatividade à esquerda com precedência única para todos os operadores.
