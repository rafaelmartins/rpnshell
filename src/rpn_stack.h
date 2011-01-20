/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */


typedef struct _stack {
    float value;
    struct _stack *next;
} rpn_stack;

void stack_push(rpn_stack **stack, float value);
float stack_pop(rpn_stack **stack);
float* stack_multipop(rpn_stack **stack, int size);
int stack_count(rpn_stack *stack);
void stack_print(rpn_stack *stack);
