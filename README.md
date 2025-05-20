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


