/**
 *  main.c
 *
 *  Copyright (c) 2010, Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <histedit.h>
#include "rpn_stack.h"
#include "rpn_operators.h"


char* prompt(EditLine *e) {
    return PACKAGE_NAME "> ";
}

int main(int argc, char* argv[]){
    
    // Initialize RPN stack
    rpn_stack *stack = NULL;
    
    // Initialize libedit variables
    EditLine *el;
    History *hist;
    HistEvent ev;
    Tokenizer *tok;
    
    // initialize common variables
    float temp;
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
    
    // main loop
    tok = tok_init(NULL);
    while(1){
        line = el_gets(el, NULL);
        
        // ^D
        if(line == NULL){
            printf("\n");
            break;
        }
        
        // token parsing
        tok_str(tok, line, &tok_argc, &tok_argv);
        
        // empty line
        if(tok_argc == 0 && stack != NULL){
            temp = stack_pop(&stack);
            stack_push(&stack, temp);
            stack_push(&stack, temp);
        }
        
        // evaluating tokens
        for(int i=0; i<tok_argc; i++){
            temp = strtof(tok_argv[i], &err);
            
            // operator
            if(temp == 0 && strcmp(tok_argv[i], err) == 0){
                rpn_operation(&stack, err);
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
        
        // print stack
        stack_print(stack);
        
        // add line to history
        history(hist, &ev, H_ENTER, line);
        
        // reinitialize token
        tok_reset(tok);
    }
    
    // freeing allocated memory
    history_end(hist);
    tok_end(tok);
    el_end(el);
    
    return 0;
}
