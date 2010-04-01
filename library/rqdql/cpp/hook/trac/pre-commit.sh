#!/bin/bash
#
# @version $Id$
#

if [ -f "/usr/local/bin/php" ]; then
    PHP="/usr/local/bin/php"
else
    if [ -f "/usr/bin/php" ]; then
        PHP="/usr/bin/php"
    fi
fi

DIR=`dirname "$0"`

$PHP $DIR/pre-commit.php $* < /dev/stdin
exit 0

