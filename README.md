# Ling_Par_My_Lang

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


