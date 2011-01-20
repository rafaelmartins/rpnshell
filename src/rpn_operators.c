/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
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
