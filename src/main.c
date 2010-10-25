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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef HAVE_LIBREADLINE
#   if defined(HAVE_READLINE_READLINE_H)
#       include <readline/readline.h>
#   elif defined(HAVE_READLINE_H)
#       include <readline.h>
#   else
extern char* readline();
#   endif
#endif

#ifdef HAVE_READLINE_HISTORY
#   if defined(HAVE_READLINE_HISTORY_H)
#       include <readline/history.h>
#   elif defined(HAVE_HISTORY_H)
#       include <history.h>
#   else
extern void add_history();
#   endif
#endif

#include "rpn_stack.h"
#include "rpn_operators.h"


int main(int argc, char* argv){
    rpn_stack *stack = NULL;
    char *value, *piece, *err;
    float temp;
    while(1){
        value = readline(PACKAGE "> ");
        if(value == NULL){
            printf("^D\n");
            break;
        }
#ifdef HAVE_READLINE_HISTORY
        add_history(value);
#endif
        if(value[0] == '\0' && stack != NULL){
            float temp2 = stack_pop(&stack);
            stack_push(&stack, temp2);
            stack_push(&stack, temp2);
        }
        else{
            piece = strtok(value, " ");
            while(piece != NULL){
                temp = strtof(piece, &err);
                if(temp == 0 && strcmp(piece, err) == 0){
                    rpn_operation(&stack, piece);
                }
                else if(err[0] == '\0'){
                    stack_push(&stack, temp);
                }
                else{
                    fprintf(stderr, "Error: Invalid operand '%s'.\n\n", piece);
                }
                piece = strtok(NULL, " ");
            }
        }
        stack_print(stack);
    }
    return 0;
}
