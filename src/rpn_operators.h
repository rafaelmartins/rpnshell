/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

typedef struct{
    char* id;
    int num_args;
    void (*function)(rpn_stack** stack, long double* args);
} operator;

enum {
    OP_SUM,
    OP_SUB,
    OP_MULT,
    OP_DIV,
    OP_SQRT,
    OP_POW,
    CMD_QUIT,
    CMD_DEL,
    __LAST, // workaround to get the enum size
};

void rpn_operation(rpn_stack** stack, const char* op);
void op_sum(rpn_stack** stack, long double* args);
void op_sub(rpn_stack** stack, long double* args);
void op_mult(rpn_stack** stack, long double* args);
void op_div(rpn_stack** stack, long double* args);
void op_sqrt(rpn_stack** stack, long double* args);
void op_pow(rpn_stack** stack, long double* args);
void cmd_quit(rpn_stack** stack, long double* args);
void cmd_del(rpn_stack** stack, long double* args);

static const operator const operators_registry[] = {
    [OP_SUM] = {
        id: "+",
        num_args: 2,
        function: op_sum,
    },
    [OP_SUB] = {
        id: "-",
        num_args: 2,
        function: op_sub,
    },
    [OP_MULT] = {
        id: "*",
        num_args: 2,
        function: op_mult,
    },
    [OP_DIV] = {
        id: "/",
        num_args: 2,
        function: op_div,
    },
    [OP_SQRT] = {
        id: "sqrt",
        num_args: 1,
        function: op_sqrt,
    },
    [OP_POW] = {
        id: "^",
        num_args: 2,
        function: op_pow,
    },
    [CMD_QUIT] = {
        id: "q",
        num_args: 0,
        function: cmd_quit,
    },
    [CMD_DEL] = {
        id: "d",
        num_args: 0,
        function: cmd_del,
    }
};
