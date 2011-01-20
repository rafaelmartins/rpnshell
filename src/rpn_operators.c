/**
 *  rpn_operators.c
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpn_stack.h"
#include "rpn_operators.h"


void rpn_operation(rpn_stack** stack, const char* op){
    float *args;
    const operator *tmp_op = NULL;
    for(int i=0; i<__LAST; i++){
        if(strcmp(operators_registry[i].id, op) == 0){
            tmp_op = &(operators_registry[i]);
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
}


void op_sum(rpn_stack** stack, float* args){
    stack_push(stack, args[1] + args[0]);
}

void op_sub(rpn_stack** stack, float* args){
    stack_push(stack, args[1] - args[0]);
}

void op_mult(rpn_stack** stack, float* args){
    stack_push(stack, args[1] * args[0]);
}

void op_div(rpn_stack** stack, float* args){
    stack_push(stack, args[1] / args[0]);
}

void op_sqrt(rpn_stack** stack, float* args){
    stack_push(stack, sqrtf(args[0]));
}

void op_pow(rpn_stack** stack, float* args){
    stack_push(stack, pow(args[1], args[0]));
}

void cmd_quit(rpn_stack** stack, float* args){
    exit(0);
}

void cmd_del(rpn_stack** stack, float* args){
    if(stack_count(*stack) > 0){
        stack_pop(stack);
    }
}
