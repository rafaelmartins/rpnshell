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
#include <sys/stat.h>
#include "plugins.h"


const char* plugin_path(void){
    struct stat st;
    if(stat("./plugins/" LT_OBJDIR, &st) == 0){
        if(S_ISDIR(st.st_mode)){
            return "./plugins/" LT_OBJDIR;
        }
    }
    if(stat(PKGLIBDIR, &st) == 0){
        if(S_ISDIR(st.st_mode)){
            return PKGLIBDIR;
        }
    }
    fprintf(stderr, "Error: Unable to find the plugins directory!\n");
    exit(EXIT_FAILURE);
}


plugin_list* plugin_lookup(const char* plugin_path){
    glob_t buf;
    char* path = (char*) malloc((strlen(plugin_path) + 6) * sizeof(char));
    sprintf(path, "%s/*.so", plugin_path);
    if(glob(path, 0, NULL, &buf) != 0){
        fprintf(stderr, "Error: Failed to find plugins!\n");
        exit(EXIT_FAILURE);
    }
    plugin_list* list = (plugin_list*) malloc(sizeof(plugin_list));
    list->pluginc = 0;
    list->pluginv = NULL;
    for(list->pluginc=0; list->pluginc<buf.gl_pathc; list->pluginc++){
        list->pluginv = realloc(list->pluginv, (list->pluginc + 1) * sizeof(plugin));
        list->pluginv[list->pluginc].filepath = (char*) malloc(
            (strlen(buf.gl_pathv[list->pluginc]) + 1) * sizeof(char));
        strcpy(list->pluginv[list->pluginc].filepath,
            buf.gl_pathv[list->pluginc]);
        list->pluginv[list->pluginc].handler = dlopen(
            list->pluginv[list->pluginc].filepath, RTLD_LAZY);
        if(!list->pluginv[list->pluginc].handler){
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }
    globfree(&buf);
    return list;
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
