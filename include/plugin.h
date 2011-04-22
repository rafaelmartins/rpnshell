/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include "rpn_stack.h"

typedef struct{
    const char* id;
    int num_args;
    void (*function)(rpn_stack** stack, long double* args);
} operator_t;


typedef struct{
    const char* name;
    const char* author;
    const char* license;
    const char* help;
    int size;
    const operator_t const operators[];
} plugin;

#endif /* PLUGIN_H */
