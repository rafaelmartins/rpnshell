/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <dlfcn.h>
#include <string.h>
#include <rpn_stack.h>
#include <plugins.h>
#include <plugin.h>


plugin_l* init_plugin_l(void){
    plugin_l *l = (plugin_l*) malloc(sizeof(plugin_l));
    l->size = 0;
    l->array = NULL;
    return l;
}

void free_plugin_l(plugin_l **l){
    free((*l)->array);
    free(*l);
    l = NULL;
}

char* plugin_identifier(char* path){
    for(int i=strlen(path)-1; i>=0; i--){
        if(path[i] == '/'){
            return &(path[i+1]);
        }
    }
    return NULL;
}

void append_plugin_l(plugin_l **l, plugin_t* p){
    int found = 0;
    for(int i=0; i<(*l)->size; i++){
        if(strcmp(p->identifier, (*l)->array[i].identifier) == 0){
            found = 1;
        }
    }
    if(found == 0){
        (*l)->array = realloc((*l)->array, ((*l)->size + 1) * sizeof(plugin_t));
        memcpy(&(*l)->array[(*l)->size++], p, sizeof(plugin_t));
    }
}

void* load_object_from_plugin(plugin_t *p, const char* name){
    dlerror();
    void *rv = dlsym(p->handler, name);
    char* error;
    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    return rv;
}

void load_plugins_from_path(plugin_l **pl, const char* path){
    glob_t buf;
    plugin_t *p;
    char* pt = (char*) malloc((strlen(path) + 6) * sizeof(char));
    sprintf(pt, "%s/*.so", path);
    if(glob(pt, 0, NULL, &buf) != 0){
        return; //ignore
    }
    for(int i=0; i<buf.gl_pathc; i++){
        plugin_t *p = (plugin_t*) malloc(sizeof(plugin_t));
        p->filepath = (char*) malloc((strlen(buf.gl_pathv[i]) + 1) * sizeof(char));
        strcpy(p->filepath, buf.gl_pathv[i]);
        p->handler = dlopen(p->filepath, RTLD_LAZY);
        //p->identifier = *((char**) load_object_from_plugin(p, "identifier"));
        p->identifier = plugin_identifier(p->filepath);
        append_plugin_l(pl, p);
    }
    free(pt);
    globfree(&buf);
}


void plugin_lookup(plugin_l **pl, int argc, char** argv){
    for(int i=1; i<argc; i++){
        load_plugins_from_path(pl, argv[i]);
    }
    load_plugins_from_path(pl, "plugins/" LT_OBJDIR);
    load_plugins_from_path(pl, PKGLIBDIR);
    if((*pl)->size == 0){
        fprintf(stderr, "No plugin found!\n");
        exit(EXIT_FAILURE);
    }
}

void print_loaded_plugins(plugin_l *pl){
    char* name;
    for(int i=0; i<pl->size; i++){
        name = ((plugin*)load_object_from_plugin(&(pl->array[i]), "metadata"))->name;
        if(i < (pl->size -1)){
            printf("%s, ", name);
        }
        else{
            printf("%s.\n", name);
        }
    }
}


/*char* load_path(void){
    
    void* handle = dlopen("rpnshell/rpnshell_core.so", RTLD_LAZY);
    if(!handle){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    plugin *inf = dlsym(handle, "foo");
    char* error;
    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    printf ("%s\n%s\n\n", inf->nome, inf->path);
    dlclose(handle);
}
*/
