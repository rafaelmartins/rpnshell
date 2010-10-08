#!/bin/bash

export WANT_AUTOCONF_2_5="yes"
export WANT_AUTOMAKE_1_10="yes"
export WANT_AUTOCONF="2.5"
export WANT_AUTOMAKE="1.10"

touch ChangeLog
libtoolize --force

aclocal -I m4
autoconf --force
autoheader --force
automake --add-missing --force-missing
