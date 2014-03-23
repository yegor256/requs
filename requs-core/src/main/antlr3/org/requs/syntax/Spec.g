/**
 * Copyright (c) 2009-2014, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
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
    package org.requs.syntax;
    import org.requs.ontology.Flow;
    import org.requs.ontology.Method;
    import org.requs.ontology.Ontology;
    import org.requs.ontology.Slot;
    import org.requs.ontology.Step;
    import org.requs.ontology.Type;
    import java.util.Collection;
    import java.util.LinkedList;
    import org.apache.commons.lang3.StringUtils;
}

@lexer::header {
    package org.requs.syntax;
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
    self=class_name
    { Type type = this.onto.type($self.ret); }
    { type.mention(input.LT(1).getLine()); }
    'is' ( 'a' | 'an' )
    (
        INFORMAL
        { type.explain($INFORMAL.text); }
        |
        parent=class_name
        { type.parent($parent.text); }
    )
    ;

class_construction
    :
    class_name
    { Type type = this.onto.type($class_name.ret); }
    ( 'includes' | 'needs' | 'contains' | 'requires' )
    ':'
    slots[type]
    ;

slots [Type type]
    :
    head=slot[type]
    (
        ( ';' | ',' )
        ( 'and' )?
        tail=slot[type]
    )*
    ;

slot [Type type]
    :
    variable
    { Slot slot = type.slot($variable.ret); }
    { slot.mention(input.LT(1).getLine()); }
    (
        '-'
        (
            's'
            { slot.arity(Slot.Arity.MANY); }
            |
            's?'
            { slot.arity(Slot.Arity.ANY); }
            |
            '?'
            { slot.arity(Slot.Arity.OPT); }
        )
    )?
    (
        'as'
        class_name
        { slot.assign($class_name.text); }
    )?
    ;

method_declaration
    :
    UC_ID
    'where'
    self=class_name
    { Type type = this.onto.type($self.text); }
    { Method method = type.method($UC_ID.text); }
    { method.mention(input.LT(1).getLine()); }
    (
        slf=binding
        { method.variable(Flow.Kind.SELF, $slf.ret, $self.ret); }
    )?
    msig=signature
    { method.signature($msig.ret); }
    (
        rslt=class_name
        (
            res=binding
            { method.variable(Flow.Kind.SELF, $res.ret, $rslt.ret); }
        )?
    )?
    (
        'using'
        hclass=class_name
        hbind=binding?
        {
            final String hname;
            if ($hbind.ret == null) {
                hname = "__arg0";
            } else {
                hname = $hbind.ret;
            }
            method.variable(Flow.Kind.INPUT, hname, $hclass.ret);
            int idx = 1;
        }
        (
            'and'
            tclass=class_name
            tbind=binding?
            {
                final String tname;
                if ($tbind.ret == null) {
                    tname = "__arg" + idx;
                } else {
                    tname = $tbind.ret;
                }
                method.variable(Flow.Kind.INPUT, tname, $tclass.ret);
                ++idx;
            }
        )?
    )?
    ':'
    steps[method]
    ;

signature returns [String ret]
    :
    { Collection<String> words = new LinkedList<String>(); }
    (
        WORD
        { words.add($WORD.text); }
    )+
    { $ret = StringUtils.join(words, " "); }
    |
    INFORMAL
    { $ret = '"' + $INFORMAL.text + '"'; }
    ;

binding returns [String ret]
    :
    '('
    ( 'a' | 'an' )
    variable
    ')'
    { $ret = $variable.ret; }
    ;

subject [Flow flow, Flow.Kind kind] returns [String ret]
    :
    class_name
    binding
    { $ret = $binding.ret; }
    { flow.variable(kind, $binding.ret, $class_name.ret); }
    |
    'the'
    variable
    { $ret = $variable.ret; }
    ;

alternative_flow_declaration
    :
    UC_ID
    '/'
    FLOW_ID
    'when'
    INFORMAL
    ':'
    { Method method = this.onto.method($UC_ID.text); }
    { Flow flow = method.step(Integer.parseInt($FLOW_ID.text)).exception($INFORMAL.text); }
    steps[flow]
    ;

steps [Flow flow]
    :
    INFORMAL
    { flow.explain($INFORMAL.text); }
    |
    step[flow]
    (
        ';'
        step[flow]
    )*
    ;

step [Flow flow]
    :
    FLOW_ID
    '.'
    { Step step = flow.step(Integer.parseInt($FLOW_ID.text)); }
    { step.mention(input.LT(1).getLine()); }
    (
        'The'
        variable
        { step.object($variable.ret); }
        step_sig=signature
        { step.signature($step_sig.ret); }
        (
            result=subject[flow, Flow.Kind.RESULT]
            { step.result($result.ret); }
        )?
        using[flow, step]?
        |
        'Fail'
        'since'
        ex_informal=INFORMAL
        { step.explain($ex_informal.text); }
        |
        step_informal=INFORMAL
        { step.explain($step_informal.text); }
    )
    ;

using [Flow flow, Step step]
    @init{ Collection<String> args = new LinkedList<String>(); }
    :
    ( 'using' | 'with' )
    head=subject[flow, Flow.Kind.LOCAL]
    { args.add($head.ret); }
    (
        'and'
        tail=subject[flow, Flow.Kind.LOCAL]
        { args.add($tail.ret); }
    )?
    { step.arguments(args); }
    ;

class_name returns [String ret]
    :
    CAMEL
    { $ret = $CAMEL.text; }
    ;

variable returns [String ret]
    :
    WORD
    { $ret = $WORD.text; }
    ;

UC_ID: 'UC' ( '0' .. '9' | '.' )+;
FLOW_ID: ( '0' .. '9' )+;
CAMEL: ( 'A' .. 'Z' ( 'a' .. 'z' )+ )+;
WORD: ( 'a' .. 'z' | 'A' .. 'Z' | '0' .. '9' )+;
INFORMAL:
    '"' ('\\"' | ~'"')* '"'
    { this.setText(this.getText().substring(1, this.getText().length() - 1).replace("\\\"", "\"")); }
    ;
SPACE
    :
    ( ' ' | '\t' | '\n' | '\r' )+
    { skip(); }
    ;
