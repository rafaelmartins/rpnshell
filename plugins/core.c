#include <math.h>
#include <rpn_stack.h>
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

plugin metadata = {
    name: "core",
    author: "Rafael G. Martins",
    license: "BSD",
    help: "Basic operators for rpnshell",
    size: 6,
    operators: {
        {
            id: "+",
            num_args: 2,
            function: op_sum,
        },
        {
            id: "-",
            num_args: 2,
            function: op_sub,
        },
        {
            id: "*",
            num_args: 2,
            function: op_mult,
        },
        {
            id: "/",
            num_args: 2,
            function: op_div,
        },
        {
            id: "sqrt",
            num_args: 1,
            function: op_sqrt,
        },
        {
            id: "^",
            num_args: 2,
            function: op_pow,
        }
    }
};
