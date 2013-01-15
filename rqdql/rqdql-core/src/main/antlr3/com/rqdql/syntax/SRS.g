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
    import java.util.LinkedList;
    import java.util.List;
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
        { $ret.add($clause.ret); }
        '.'
    )*
    EOF
    ;

clause returns [Clause ret]
    :
    class_declaration
    |
    class_construction
    |
    method_declaration
    |
    alternative_flow_declaration
    ;

class_declaration returns [Clause ret]
    :
    class_name
    'is'
    ( 'a' | 'an' )
    ( INFORMAL | class_name )
    { $ret = new Clause() {}; }
    ;

class_construction returns [Clause ret]
    :
    class_name
    ( 'includes' | 'needs' | 'contains' | 'requires' )
    ':'
    slots
    { $ret = new Clause() {}; }
    ;

slots returns [List<Slot> ret]
    @init { $ret = new LinkedList<Slot>(); }
    :
    head=slot
    { $ret.add($head.ret); }
    (
        ( ';' | ',' )
        ( 'and' )?
        tail=slot
        { $ret.add($tail.ret); }
    )*
    ;

slot returns [Slot ret]
    :
    variable
    (
        'as'
        class_name
    )?
    { $ret = new Slot() {}; }
    ;

method_declaration returns [Clause ret]
    :
    UC_ID
    'where'
    signature
    ':'
    ( INFORMAL | flows )
    { $ret = new Clause() {}; }
    ;

signature returns [Signature ret]
    :
    class_name
    WORD+
    subject?
    using?
    ;

subject
    :
    class_name
    binding
    |
    'the'
    variable
    ;

binding
    :
    '('
    'a'
    variable
    ')'
    ;

using
    :
    'using'
    subject
    (
        'and'
        subject
    )*
    ;

flows returns [List<Flow> ret]
    @init { $ret = new LinkedList<Flow>(); }
    :
    head=flow
    { $ret.add($head.ret); }
    (
        ';'
        tail=flow
        { $ret.add($tail.ret); }
    )+
    ;

flow returns [Flow ret]
    :
    FLOW_ID
    '.'
    (
        signature
        |
        'Fail' 'since' INFORMAL
    )
    ;

alternative_flow_declaration returns [Clause ret]
    :
    UC_ID
    '/'
    FLOW_ID
    'when'
    INFORMAL
    ':'
    flows
    { $ret = new Clause() {}; }
    ;

class_name
    :
    CAPITAL_WORD
    ;

variable
    :
    WORD
    ;

UC_ID: 'UC' ( '0' .. '9' )+;
FLOW_ID: ( '0' .. '9' )+;
CAPITAL_WORD: 'A' .. 'Z' ( 'a' .. 'z' | 'A' .. 'Z' )+;
WORD: ( 'a' .. 'z' )+;
INFORMAL:
    '"' ('\\"' | ~'"')* '"'
    { this.setText(this.getText().substring(1, this.getText().length() - 1).replace("\\\"", "\"")); }
    ;
SPACE
    :
    ( ' ' | '\t' | '\n' | '\r' )+
    { skip(); }
    ;
