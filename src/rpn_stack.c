/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#include <rpn_stack.h>

void stack_push(rpn_stack **stack, long double value){
    rpn_stack *node = malloc(sizeof(rpn_stack)); 
    if(node == NULL){
        fprintf(stderr, "Error: stack overflow.\n");
        abort();
    }
    else{
        node->value = value;
        node->next = *stack;
        *stack = node;
    }
}

void stack_repush(rpn_stack **stack){
    if(*stack == NULL){
        return;
    }
    stack_push(stack, (*stack)->value);
}

long double stack_pop(rpn_stack **stack){
    if(*stack == NULL){
        fprintf(stderr, "Error: stack underflow.\n");
        abort();
    }
    else{
        rpn_stack *top = *stack;
        long double value = top->value;
        *stack = top->next;
        free(top);
        return value;
    }
}

long double* stack_multipop(rpn_stack **stack, int size){
    if(stack_count(*stack) < size){
        return NULL;
    }
    long double *rv = (long double *) malloc(sizeof(long double) * size);
    for(int i=0; i<size; i++){
        rv[i] = stack_pop(stack);
    }
    return rv;
}

int stack_count(rpn_stack *stack){
    rpn_stack *aux = stack;
    int count = 0;
    while(aux != NULL){
        aux = aux->next;
        count++;
    }
    stack_free(&aux);
    return count;
}

void stack_print(rpn_stack *stack){
    rpn_stack *aux1 = stack, *aux2 = NULL;
    int count = stack_count(stack);
    while(aux1 != NULL){
        stack_push(&aux2, aux1->value);
        aux1 = aux1->next;
    }
    stack_free(&aux1);
    while(aux2 != NULL){
        printf("%i: %Lf\n", count, aux2->value);
        aux2 = aux2->next;
        count--;
    }
    stack_free(&aux2);
}

void stack_free(rpn_stack **stack){
    while(*stack != NULL){
        stack_pop(stack);
    }
    stack = NULL;
}
