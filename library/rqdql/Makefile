#
# FaZend.com, Fully Automated Zend Framework
# RQDQL.com, Requirements Definition and Query Language
#
# Redistribution and use in source and binary forms, with or 
# without modification, are PROHIBITED without prior written 
# permission from the author. This product may NOT be used 
# anywhere and on any computer except the server platform of 
# FaZend.com. located at www.fazend.com. If you received this 
# code occasionally and without intent to use it, please report 
# this incident to the author by email: team@rqdql.com
#
# @author Yegor Bugayenko <egor@tpc2.com>
# @copyright Copyright (c) rqdql.com, 2010
# @version $Id: Makefile 1465 2010-03-26 16:01:31Z yegor256@yahoo.com $

FILES = $(shell cd rqdql.com; find . -type f | grep -v ".svn")

# deploy the HTML to the target hosting platform
deploy:
	cd rqdql.com; ftp -u ftp://rqdql_deploy%40caybo.ru:uf8Klp7Y2Et4@rqdql.com/public/ $(FILES)
