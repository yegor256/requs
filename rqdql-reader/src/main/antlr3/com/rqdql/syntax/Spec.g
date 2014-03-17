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
grammar Spec;

@header {
    package com.rqdql.syntax;
    import com.rqdql.ontology.Ontology;
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
    private Ontology onto;
    public void setOntology(Ontology ont) {
        this.onto = ont;
    }
    @Override
    public void emitErrorMessage(String msg) {
        throw new IllegalArgumentException(msg);
    }
}

clauses
    :
    (
        clause
        '.'
    )*
    EOF
    ;

clause
    :
    class_declaration
    |
    class_construction
    |
    method_declaration
    |
    alternative_flow_declaration
    ;

class_declaration
    :
    class_name
    'is'
    ( 'a' | 'an' )
    ( INFORMAL | class_name )
    { ; }
    ;

class_construction
    :
    class_name
    ( 'includes' | 'needs' | 'contains' | 'requires' )
    ':'
    slots
    { ; }
    ;

slots
    :
    head=slot
    { ; }
    (
        ( ';' | ',' )
        ( 'and' )?
        tail=slot
        { ; }
    )*
    ;

slot
    :
    variable
    (
        'as'
        class_name
    )?
    { ; }
    ;

method_declaration
    :
    UC_ID
    'where'
    class_name
    signature
    ':'
    ( INFORMAL | flows )
    { ; }
    ;

signature
    :
    (
        WORD+
        |
        INFORMAL
    )
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

flows
    :
    head=flow
    { ; }
    (
        ';'
        tail=flow
        { ; }
    )*
    ;

flow
    :
    FLOW_ID
    '.'
    (
        'The'
        variable
        signature
        |
        'Fail' 'since' INFORMAL
    )
    ;

alternative_flow_declaration
    :
    UC_ID
    '/'
    FLOW_ID
    'when'
    INFORMAL
    ':'
    flows
    { ; }
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
