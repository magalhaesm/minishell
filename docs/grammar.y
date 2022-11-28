%token  WORD
%token  AND  OR
%token  LESS  GREAT  DLESS  DGREAT
%token  PIPE  LPAREN  RPAREN

/* -------------------------------------------------------
   The Grammar
   -------------------------------------------------------
*/
%start commandline
%%

commandline : list
list : pipeline conditional
conditional : AND pipeline conditional | OR pipeline conditional | ε
pipeline : command fcommand
command : simple_cmd | subshell fsubshell
fcommand :  ε | PIPE pipeline
subshell : LBRACE list RBRACE
fsubshell : ε | redirect_list
simple_cmd : WORD fword | cmd_prefix fcmd_prefix
fword : ε | cmd_suffix
fcmd_prefix : ε | WORD fword
cmd_prefix : io_redirect cmd_prefix1
cmd_prefix1 : io_redirect cmd_prefix1 | ε
cmd_suffix : io_redirect cmd_suffix1 | WORD cmd_suffix1
cmd_suffix1 : io_redirect cmd_suffix1 | WORD cmd_suffix1 | ε
redirect_list : io_redirect redirect_list1
redirect_list1 : io_redirect redirect_list1 | ε
io_redirect : io_file | io_here
io_file : LESS WORD | GREAT WORD | DGREAT WORD
io_here : DLESS WORD

%%
