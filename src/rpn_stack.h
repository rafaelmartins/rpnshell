/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifndef RPN_STACK_H
#define RPN_STACK_H

typedef struct _stack {
    long double value;
    struct _stack *next;
} rpn_stack;

void stack_push(rpn_stack **stack, long double value);
void stack_repush(rpn_stack **stack);
long double stack_pop(rpn_stack **stack);
long double* stack_multipop(rpn_stack **stack, int size);
int stack_count(rpn_stack *stack);
void stack_print(rpn_stack *stack);
void stack_free(rpn_stack **stack);

#endif /* RPN_STACK_H */
