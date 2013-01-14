/**
 * Copyright (c) 2009-2013, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
grammar SRS;

@header {
    package com.rqdql.syntax;
}

@lexer::header {
    package com.rqdql.syntax;
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

clauses returns [List<Clause> ret]
    @init { $ret = new LinkedList<Clause>(); }
    :
    (
        clause
        { $ret.add(clause.ret); }
        '.'
    )*
    EOF
    ;

clause returns [Clause ret]
    :
    desriptor
    |
    constructor
    |
    operation
    ;

descriptor returns [Clause ret]
    :
    object
    'is'
    ( 'a' | 'an' )
    ( INFORMAL | object )
    ;

constructor returns [Clause ret]
    :
    object
    ( 'includes?' | 'needs?' | 'contains?' | 'requires?' )
    ':'
    slots
    { $ret = new Clause(); }
    ;

slots returns [List<Slot> ret]
    @init { $ret = new LinkedList<Slot>(); }
    :
    first
    { $ret.add(first.ret); }
    (
        ( ';' | ',' )
        ( 'and' )?
        slot
        { $ret.add(slot.ret); }
    )*
    ;

slot returns [Slot ret]
    :
    variable
    ':'
    ( INFORMAL | object )
    ;

operation returns [Clause ret]
    :
    signature
    ':'
    ( INFORMAL | flows )
    { $ret = new Clause(); }
    ;

flows returns [List<Flow> ret]
    @init { $ret = new LinkedList<Flow>(); }
    :
    first
    { $ret.add(first.ret); }
    (
        ';'
        flow
        { $ret.add(flow.ret); }
    )+
    ;

flow returns [Flow ret]
    :
    ( '0' .. '9' )+
    signature
    ;

signature returns [Signature ret]
    :
    object
    verb
    ( 'the' variable | object '(' 'a' variable ')' )
    ( 'using' /* ? */ )?
    ;

variable returns [Variable ret]
    :
    ;

NAME: ( 'a' .. 'z' | 'A' .. 'Z' )*;
SPACE
    :
    ( ' ' | '\t' | '\n' | '\r' )+
    { skip(); }
    ;
