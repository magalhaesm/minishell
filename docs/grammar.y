%token  WORD
%token  AND  OR
%token  LESS  GREAT  DLESS  DGREAT
%token  PIPE  LPAREN  RPAREN

/* -------------------------------------------------------
   The Grammar
   -------------------------------------------------------
*/
%start list
%%
              list : pipeline conditional
       conditional : AND pipeline conditional
                   | OR pipeline conditional
                   | empty
          pipeline : command pipeline_null
           command : simple_cmd
                   | subshell subshell_redir
     pipeline_null : PIPE pipeline
                   | empty
          subshell : LBRACE list RBRACE
    subshell_redir : redirect_list
                   | empty
        simple_cmd : WORD word_null
                   | cmd_prefix fcmd_prefix
         word_null : cmd_suffix
                   | empty
       fcmd_prefix : WORD word_null
                   | empty
        cmd_prefix : io_redirect cmd_prefix_null
   cmd_prefix_null : io_redirect cmd_prefix_null
                   | empty
        cmd_suffix : io_redirect cmd_suffix_null
                   | WORD cmd_suffix_null
   cmd_suffix_null : io_redirect cmd_suffix_null
                   | WORD cmd_suffix_null
                   | empty
     redirect_list : io_redirect redirect_list_null
redirect_list_null : io_redirect redirect_list_null
                   | empty
       io_redirect : io_file
                   | io_here
           io_file : LESS WORD
                   | GREAT WORD
                   | DGREAT WORD
           io_here : DLESS WORD
%%
