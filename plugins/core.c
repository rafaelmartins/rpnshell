/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <math.h>
#include <plugin.h>


void op_sum(rpn_stack** stack, long double* args){
    stack_push(stack, args[1] + args[0]);
}

void op_sub(rpn_stack** stack, long double* args){
    stack_push(stack, args[1] - args[0]);
}

void op_mult(rpn_stack** stack, long double* args){
    stack_push(stack, args[1] * args[0]);
}

void op_div(rpn_stack** stack, long double* args){
    stack_push(stack, args[1] / args[0]);
}

void op_sqrt(rpn_stack** stack, long double* args){
    stack_push(stack, sqrtl(args[0]));
}

void op_pow(rpn_stack** stack, long double* args){
    stack_push(stack, powl(args[1], args[0]));
}

const plugin metadata = {
    name: "core",
    author: "Rafael G. Martins",
    license: "BSD",
    help: "Basic operators for rpnshell",
    size: 6,
    operators: {
        {
            id: "+",
            num_args: 2,
            help: "sum",
            function: op_sum,
        },
        {
            id: "-",
            num_args: 2,
            help: "subtraction",
            function: op_sub,
        },
        {
            id: "*",
            num_args: 2,
            help: "multiplication",
            function: op_mult,
        },
        {
            id: "/",
            num_args: 2,
            help: "division",
            function: op_div,
        },
        {
            id: "sqrt",
            num_args: 1,
            help: "square root",
            function: op_sqrt,
        },
        {
            id: "^",
            num_args: 2,
            help: "pow",
            function: op_pow,
        }
    }
};
