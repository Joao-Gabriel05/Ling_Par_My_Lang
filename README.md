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

expression       = term { ("+" | "-" | "*" | "/" | ">" | "<" | "==" | "!=" | ">=" | "<=") term } ;

identifier       = letter { letter | "_" | digit } ;
number           = digit { digit } ;
digit            = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
letter           = "a"| "b" |"c"| letter = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
       | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" ;



