/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <histedit.h>
#include <rpn_stack.h>
#include <plugins.h>
#include <plugin.h>


char* prompt(EditLine *e) {
    return PACKAGE_NAME "> ";
}

void rpn_operation(rpn_stack** stack, plugin_l* list, const char* op){
    long double *args;
    plugin *metadata = NULL;
    const operator_t *tmp_op = NULL;
    for(int i=0; i<list->size; i++){
        metadata = (plugin*) load_object_from_plugin(&(list->array[i]), "metadata");
        for(int j=0; j<metadata->size; j++){
            if(strcmp(metadata->operators[j].id, op) == 0){
                tmp_op = &(metadata->operators[j]);
                break;
            }
        }
        if(tmp_op != NULL){
            break;
        }
    }
    if(tmp_op == NULL){
        fprintf(stderr, "Error: Invalid operator '%s'.\n\n", op);
        return;
    }
    args = stack_multipop(stack, tmp_op->num_args);
    if(args == NULL){
        fprintf(stderr, "Error: Invalid number of arguments. "
            "'%s' requires %i arguments.\n\n", op, tmp_op->num_args);
        return;
    }
    tmp_op->function(stack, args);
    free(args);
}

int main(int argc, char* argv[]){
    
    // Initialize RPN stack
    rpn_stack *stack = NULL;
    bool print_stack;
    
    // Initialize plugin stuff
    plugin *metadata = NULL;
    plugin_l *pl = init_plugin_l();
    plugin_lookup(&pl, argc, argv);
    
    // Initialize libedit variables
    EditLine *el;
    History *hist;
    HistEvent ev;
    Tokenizer *tok;
    
    // initialize common variables
    long double temp;
    int tok_argc;
    const char *line, **tok_argv;
    char *err;
    
    // initialize libedit
    el = el_init(argv[0], stdin, stdout, stderr);
    el_set(el, EL_PROMPT, &prompt);
    el_set(el, EL_EDITOR, "emacs");
    
    // initialize history
    hist = history_init();
    if(hist == 0){
        fprintf(stderr, "Failed to initialize command line history\n");
        return 1;
    }
    history(hist, &ev, H_SETSIZE, 500);
    el_set(el, EL_HIST, history, hist);
    
    // banner
    printf(FULL_STRING "\tCopyright (C) 2010-2011 Rafael G. Martins\n");
    printf("Loaded plugins: ");
    print_loaded_plugins(pl);
    printf("\n");
    
    // main loop
    tok = tok_init(NULL);
    while(1){
        print_stack = true;
        line = el_gets(el, NULL);
        
        // ^D
        if(line == NULL){
            printf("\n");
            break;
        }
        
        // token parsing
        tok_str(tok, line, &tok_argc, &tok_argv);
        
        // empty line
        if(tok_argc == 0){
            stack_repush(&stack);
        }
        
        // evaluating tokens
        for(int i=0; i<tok_argc; i++){
            temp = strtold(tok_argv[i], &err);
            
            // operator
            if(temp == 0 && strcmp(tok_argv[i], err) == 0){
                
                // help
                if(strcmp("help", err) == 0){
                    printf("Available plugins:\n\n");
                    for(int j=0; j<pl->size; j++){
                        metadata = (plugin*) load_object_from_plugin(&(pl->array[j]),
                            "metadata");
                        printf("%s: %s\n", metadata->name, metadata->help);
                        printf("    Author: %s\n", metadata->author);
                        printf("    License: %s\n", metadata->license);
                        printf("    Operators:\n");
                        for(int k=0; k<metadata->size; k++){
                            printf("        %s (%s - %i argument%s)\n",
                                metadata->operators[k].id,
                                metadata->operators[k].help,
                                metadata->operators[k].num_args,
                                metadata->operators[k].num_args > 1 ? "s": "");
                        }
                        printf("\n");
                    }
                    print_stack = false;
                }
                
                // rpn operation
                else{
                    rpn_operation(&stack, pl, err);
                }
            }
            
            // valid number
            else if(err[0] == '\0'){
                stack_push(&stack, temp);
            }
            
            // invalid value
            else{
                fprintf(stderr, "Error: Invalid operand '%s'.\n\n", tok_argv[i]);
            }
        }
        
        if(print_stack){
            // print stack
            stack_print(stack);
        }
        
        // add line to history
        history(hist, &ev, H_ENTER, line);
        
        // reinitialize token
        tok_reset(tok);
    }
    
    // freeing allocated memory
    history_end(hist);
    tok_end(tok);
    el_end(el);
    
    // freeing stack
    stack_free(&stack);
    
    // freeing plugin list
    free_plugin_l(&pl);
    
    return 0;
}
