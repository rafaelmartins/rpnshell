/**
 * rpnshell: A RPN-based calculator to the command-line interface.
 * Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

typedef struct{
    char* filepath;
    void* handler;
} plugin;

typedef struct{
    int pluginc;
    plugin* pluginv;
} plugin_list;

const char* plugin_path(void);
plugin_list* plugin_lookup(const char* plugin_path);
