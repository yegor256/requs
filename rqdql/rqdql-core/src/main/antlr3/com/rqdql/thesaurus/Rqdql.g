/**
 * @version $Id$
 *
 * @todo #6 It's just a stub for now
 */
grammar Rqdql;

@header {
    package com.rqdql.thesaurus;
}

@lexer::header {
    package com.rqdql.thesaurus;
}

@lexer::members {
    @Override
    public void emitErrorMessage(String msg) {
        throw new IllegalArgumentException(msg);
    }
}

@parser::members {
    @Override
    public void emitErrorMessage(String msg) {
        throw new IllegalArgumentException(msg);
    }
}

document returns [String context]
    :
    'test'
    ;

NAME: ( 'a' .. 'z' | 'A' .. 'Z' )*;
SPACE
    :
    ( ' ' | '\t' | '\n' | '\r' )+
    { skip(); }
    ;
