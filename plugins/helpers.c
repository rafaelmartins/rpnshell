/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <plugin.h>


void cmd_quit(rpn_stack** stack, long double* args){
    exit(0);
}

void cmd_del(rpn_stack** stack, long double* args){
    if(stack_count(*stack) > 0){
        stack_pop(stack);
    }
}

const plugin metadata = {
    name: "helpers",
    author: "Rafael G. Martins",
    license: "BSD",
    help: "Basic helpers (quit, delete) for rpnshell",
    operators: {
        {
            id: "q",
            num_args: 0,
            help: "quit",
            function: cmd_quit,
        },
        {
            id: "d",
            num_args: 0,
            help: "delete last value",
            function: cmd_del,
        },
        {NULL, 0, NULL, NULL},
    }
};
