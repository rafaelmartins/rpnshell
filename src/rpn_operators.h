/**
 *  rpn_operators.h
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

typedef struct{
    char* id;
    int num_args;
    void (*function)(rpn_stack** stack, float* args);
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
void op_sum(rpn_stack** stack, float* args);
void op_sub(rpn_stack** stack, float* args);
void op_mult(rpn_stack** stack, float* args);
void op_div(rpn_stack** stack, float* args);
void op_sqrt(rpn_stack** stack, float* args);
void op_pow(rpn_stack** stack, float* args);
void cmd_quit(rpn_stack** stack, float* args);
void cmd_del(rpn_stack** stack, float* args);

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
