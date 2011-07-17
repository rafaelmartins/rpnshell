/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifndef PLUGINS_H
#define PLUGINS_H

typedef struct{
    char* filepath;
    char* identifier;
    void* handler;
} plugin_t;

typedef struct{
    size_t size;
    plugin_t* array;
} plugin_l;


plugin_l* init_plugin_l(void);
void free_plugin_l(plugin_l **l);
char* plugin_identifier(char* path);
void append_plugin_l(plugin_l **l, plugin_t* p);
void* load_object_from_plugin(plugin_t *p, const char* name);
void load_plugins_from_path(plugin_l **pl, const char* path);
void plugin_lookup(plugin_l **pl, int argc, char** argv);
void print_loaded_plugins(plugin_l *pl);

#endif /* PLUGINS_H */
