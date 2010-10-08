/**
 *  rpn_stack.c
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

#include <stdio.h>
#include <stdlib.h>
#include "rpn_stack.h"

void stack_push(rpn_stack **stack, float value){
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

float stack_pop(rpn_stack **stack){
    if(*stack == NULL){
        fprintf(stderr, "Error: stack underflow.\n");
        abort();
    }
    else{
        rpn_stack *top = *stack;
        float value = top->value;
        *stack = top->next;
        free(top);
        return value;
    }
}

float* stack_multipop(rpn_stack **stack, int size){
    if(stack_count(*stack) < size){
        return NULL;
    }
    float *rv = (float *) malloc(sizeof(float) * size);
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
    free(aux);
    return count;
}

void stack_print(rpn_stack *stack){
    rpn_stack *aux1 = stack, *aux2 = NULL;
    int count = stack_count(stack);
    while(aux1 != NULL){
        stack_push(&aux2, aux1->value);
        aux1 = aux1->next;
    }
    free(aux1);
    while(aux2 != NULL){
        printf("%i: %f\n", count, aux2->value);
        aux2 = aux2->next;
        count--;
    }
    free(aux2);
}
