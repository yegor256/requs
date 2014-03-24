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

@parser::members {
    private Ontology onto;
    public void setOntology(Ontology ont) {
        this.onto = ont;
    }
}

clauses
    :
    (
        clause
        DOT
    )*
    EOF
    ;

clause
    :
    INFORMAL
    |
    class_declaration
    |
    class_construction
    |
    method_declaration
    |
    alternative_flow_declaration
    |
    attribute_setting
    ;

class_declaration
    :
    self=class_name
    { Type type = this.onto.type($self.ret); }
    { type.mention(_input.LT(1).getLine()); }
    IS
    (
        INFORMAL
        { type.explain($INFORMAL.text); }
        |
        A
        parent=class_name
        { type.parent($parent.text); }
    )
    ;

class_construction
    :
    class_name
    { Type type = this.onto.type($class_name.ret); }
    { type.mention(_input.LT(1).getLine()); }
    INCLUDES
    COLON
    slots[type]
    ;

slots [Type type]
    :
    head=slot[type]
    (
        ( SEMICOLON AND? | COMMA AND? | AND )
        tail=slot[type]
    )*
    ;

slot [Type type]
    :
    variable
    { Slot slot = type.slot($variable.ret); }
    { slot.mention(_input.LT(1).getLine()); }
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
        AS
        (
            class_name
            { slot.assign($class_name.text); }
            |
            INFORMAL
            { slot.explain($INFORMAL.text); }
        )
    )?
    ;

method_declaration
    :
    UC_ID
    WHERE
    self=class_name
    { Type type = this.onto.type($self.text); }
    { type.mention(_input.LT(1).getLine()); }
    { Method method = type.method($UC_ID.text); }
    { method.mention(_input.LT(1).getLine()); }
    slf=binding?
    {
        final String self;
        if ($slf.ctx == null) {
            self = "_self";
        } else {
            self = $slf.ret;
        }
        method.binding(self, $self.ret);
        method.object(self);
    }
    msig=signature
    { method.sign($msig.ret); }
    (
        rslt=class_name
        (
            res=binding
            { method.binding($res.ret, $rslt.ret); }
            { method.result($res.ret); }
        )?
    )?
    (
        USING
        hclass=class_name
        hbind=binding?
        {
            final String hname;
            if ($hbind.ctx == null) {
                hname = "_arg0";
            } else {
                hname = $hbind.ret;
            }
            method.binding(hname, $hclass.ret);
            method.input(hname);
            int idx = 1;
        }
        (
            AND
            tclass=class_name
            tbind=binding?
            {
                final String tname;
                if ($tbind.ctx == null) {
                    tname = "_arg" + idx;
                } else {
                    tname = $tbind.ret;
                }
                method.binding(tname, $tclass.ret);
                method.input(tname);
                ++idx;
            }
        )?
    )?
    COLON
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
    A
    variable
    ')'
    { $ret = $variable.ret; }
    ;

subject [Flow flow] returns [String ret]
    :
    class_name
    binding
    { $ret = $binding.ret; }
    { flow.binding($binding.ret, $class_name.ret); }
    |
    THE
    variable
    { $ret = $variable.ret; }
    ;

alternative_flow_declaration
    :
    UC_ID
    '/'
    FLOW_ID
    WHEN
    INFORMAL
    COLON
    { Method method = this.onto.method($UC_ID.text); }
    { method.mention(_input.LT(1).getLine()); }
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
        SEMICOLON
        step[flow]
    )*
    ;

step [Flow flow]
    :
    FLOW_ID
    DOT
    { Step step = flow.step(Integer.parseInt($FLOW_ID.text)); }
    { step.mention(_input.LT(1).getLine()); }
    (
        (
            THE
            variable
            { step.object($variable.ret); }
            |
            SUD
            { step.object("SuD"); }
        )
        step_sig=signature
        { step.sign($step_sig.ret); }
        (
            result=subject[flow]
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

using [Flow flow, Step stp]
    :
    USING
    head=subject[flow]
    { stp.input($head.ret); }
    (
        AND
        tail=subject[flow]
        { stp.input($tail.ret); }
    )?
    ;

class_name returns [String ret]
    :
    CAMEL
    { $ret = $CAMEL.text; }
    |
    SUD
    { $ret = $SUD.text; }
    ;

variable returns [String ret]
    :
    WORD
    { $ret = $WORD.text; }
    ;

attribute_setting
    :
    COLON
    UC_ID
    IS
    A?
    WORD
    { this.onto.method($UC_ID.text).attribute($WORD.text); }
    ;

UC_ID: 'UC' ( '0' .. '9' | '.' )+;
FLOW_ID: ( '0' .. '9' )+;
COLON: ':';
SEMICOLON: ';';
DOT: '.';
COMMA: ',';
SUD: 'SuD' | 'We' | 'we';
USING: ( 'using' | 'of' | 'with' );
A: ( 'a' | 'an' );
THE: ( 'the' | 'The' );
AS: 'as';
IS: 'is';
WHEN: 'when';
WHERE: 'where';
AND: 'and';
INCLUDES: ( 'includes' | 'needs' | 'contains' | 'requires' | 'has' );
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
