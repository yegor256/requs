#!/bin/bash
#
# @version $Id$
#

PHP=`which php`
DIR=`dirname "$0"`

$PHP $DIR/trac-hook.php < /dev/stdin
exit 0

