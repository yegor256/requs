/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
grammar Spec;

@header {
    import org.requs.facet.syntax.ontology.Acronym;
    import org.requs.facet.syntax.ontology.Flow;
    import org.requs.facet.syntax.ontology.Method;
    import org.requs.facet.syntax.ontology.Ontology;
    import org.requs.facet.syntax.ontology.Page;
    import org.requs.facet.syntax.ontology.Slot;
    import org.requs.facet.syntax.ontology.Step;
    import org.requs.facet.syntax.ontology.Type;
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
    |
    nfr_declaration
    |
    page_declaration
    |
    acronym_declaration
    ;

class_declaration
    :
    self=class_name
    { Type type = this.onto.type($self.ret); }
    { type.mention(_input.LT(1).getLine()); }
    IS
    A?
    (
        ACTOR
        { type.actor(true); }
        |
        (
            INFORMAL
            { type.explain($INFORMAL.text); }
        )+
        |
        parent=class_name
        { type.parent($parent.text); }
        (
            INFORMAL
            { type.explain($INFORMAL.text); }
        )*
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
    { if ($variable.ret == null) throw new SyntaxException("invalid slot"); }
    { Slot slot = type.slot($variable.ret); }
    { slot.mention(_input.LT(1).getLine()); }
    { slot.arity(Slot.Arity.ONE); }
    { slot.composition(true); }
    (
        '-'
        (
            's'
            { slot.arity(Slot.Arity.MANY); }
            |
            's?'
            { slot.arity(Slot.Arity.ANY); }
        )
    )?
    (
        AS
        (
            class_name
            { if ($class_name.ret == null) throw new SyntaxException("invalid class name"); }
            { slot.assign($class_name.text); }
            { slot.composition(false); }
            (
                '!'
                { slot.composition(true); }
            )?
            |
            INFORMAL
            { slot.explain($INFORMAL.text); }
        )
        (
            INFORMAL
            { slot.explain($INFORMAL.text); }
        )*
    )?
    ;

method_declaration
    :
    UC_ID
    { Method method = this.onto.method($UC_ID.text); }
    { method.mention(_input.LT(1).getLine()); }
    WHERE
    self=class_name
    { if ($self.ret == null) throw new SyntaxException("invalid method"); }
    { Type type = this.onto.type($self.text); }
    { type.mention(_input.LT(1).getLine()); }
    slf=binding?
    {
        final String self;
        if ($slf.ctx == null) {
            self = Flow.SELF;
        } else {
            self = $slf.ret;
            method.binding(Flow.SELF, $self.ret);
        }
        method.binding(self, $self.ret);
        method.object(self);
    }
    msig=signature
    { if ($msig.ret == null) throw new SyntaxException("invalid signature"); }
    { method.sign($msig.ret); }
    (
        rslt=class_name
        { if ($rslt.ret == null) throw new SyntaxException("invalid result"); }
        res=binding?
        {
            final String rname;
            if ($res.ctx == null) {
                rname = "_result";
            } else {
                rname = $res.ret;
            }
            { if (rname == null) throw new SyntaxException("invalid result"); }
            { method.binding(rname, $rslt.ret); }
            { method.result(rname); }
        }
    )?
    (
        USING
        hclass=class_name
        { if ($hclass.ret == null) throw new SyntaxException("invalid subject"); }
        hbind=binding?
        {
            final String hname;
            if ($hbind.ctx == null) {
                hname = "_arg0";
            } else {
                hname = $hbind.ret;
            }
            { if (hname == null) throw new SyntaxException("broken subject"); }
            method.binding(hname, $hclass.ret);
            method.input(hname);
            int idx = 1;
        }
        (
            AND
            tclass=class_name
            { if ($tclass.ret == null) throw new SyntaxException("invalid list of subjects"); }
            tbind=binding?
            {
                final String tname;
                if ($tbind.ctx == null) {
                    tname = "_arg" + idx;
                } else {
                    tname = $tbind.ret;
                }
                { if (tname == null) throw new SyntaxException("broken subject"); }
                method.binding(tname, $tclass.ret);
                method.input(tname);
                ++idx;
            }
        )?
    )?
    INFORMAL*
    COLON
    INFORMAL*
    steps[method]
    ;

signature returns [String ret]
    :
    { Collection<String> words = new LinkedList<String>(); }
    (
        word
        { words.add($word.text); }
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
    { if ($variable.ret == null) throw new SyntaxException("invalid variable"); }
    ')'
    { $ret = $variable.ret; }
    ;

subject [Flow flow] returns [String ret]
    :
    class_name
    { if ($class_name.ret == null) throw new SyntaxException("invalid class name"); }
    binding
    { if ($binding.ret == null) throw new SyntaxException("invalid binding"); }
    { $ret = $binding.ret; }
    { flow.binding($binding.ret, $class_name.ret); }
    |
    THE
    variable
    { if ($variable.ret == null) throw new SyntaxException("invalid variable"); }
    { $ret = $variable.ret; }
    ;

alternative_flow_declaration
    :
    UC_ID
    SLASH
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
        object=subject[flow]
        { if ($object.ret == null) throw new SyntaxException("invalid object"); }
        { step.object($object.ret); }
        (
            INFORMAL
            { step.explain($INFORMAL.text); }
        )*
        step_sig=signature
        { if ($step_sig.ret == null) throw new SyntaxException("invalid signature"); }
        { step.sign($step_sig.ret); }
        (
            result=subject[flow]
            { if ($result.ret == null) throw new SyntaxException("invalid result"); }
            { step.result($result.ret); }
        )?
        (
            INFORMAL
            { step.explain($INFORMAL.text); }
        )*
        using[flow, step]?
        |
        (
            FAIL
            AS
            cause=INFORMAL
            { if ($cause == null) throw new SyntaxException("invalid failure message"); }
            { step.object(Flow.SELF); }
            { step.sign("fail"); }
            { step.explain($cause.text); }
            (
                WHEN
                condition=INFORMAL
                { if ($condition == null) throw new SyntaxException("invalid condition message"); }
                { step.explain($condition.text); }
            )?
        )
        |
        step_informal=signature
        { if ($step_informal.ret == null) throw new SyntaxException("invalid signature"); }
        { step.object(Flow.SELF); }
        { step.sign($step_informal.ret); }
    )
    (
        INFORMAL
        { step.explain($INFORMAL.text); }
    )*
    ;

using [Flow flow, Step stp]
    :
    USING
    head=subject[flow]
    { if ($head.ret == null) throw new SyntaxException("invalid subject"); }
    { stp.input($head.ret); }
    (
        AND
        tail=subject[flow]
        { if ($tail.ret == null) throw new SyntaxException("invalid subject"); }
        { stp.input($tail.ret); }
    )?
    ;

class_name returns [String ret]
    :
    CAMEL
    { $ret = $CAMEL.text; }
    ;

variable returns [String ret]
    :
    word
    { $ret = $word.text; }
    ;

attribute_setting
    :
    SEAL?
    COLON
    UC_ID
    IS
    A?
    word
    {
        final String seal;
        if ($SEAL == null) {
            seal = StringUtils.EMPTY;
        } else {
            seal = $SEAL.text;
        }
        Method method = this.onto.method($UC_ID.text);
        method.attribute($word.text, seal);
        method.mention(_input.LT(1).getLine());
    }
    ;

nfr_declaration
    :
    UC_ID
    SLASH
    ACRONYM
    MUST
    INFORMAL
    {
        Method method = this.onto.method($UC_ID.text);
        method.nfr($ACRONYM.text).explain($INFORMAL.text);
        method.mention(_input.LT(1).getLine());
    }
    ;

page_declaration
    :
    CAMEL
    COLON
    INFORMAL
    {
        Page page = this.onto.page($CAMEL.text);
        page.explain($INFORMAL.text);
        page.mention(_input.LT(1).getLine());
    }
    ;

acronym_declaration
    :
    ACRONYM
    MEANS
    INFORMAL
    {
        Acronym acronym = this.onto.acronym($ACRONYM.text);
        acronym.explain($INFORMAL.text);
        acronym.mention(_input.LT(1).getLine());
    }
    ;

word
    :
    WORD
    |
    ACRONYM
    |
    MUST
    ;

SEAL: ('0'..'9' | 'a'..'f')
    ('0'..'9' | 'a'..'f')
    ('0'..'9' | 'a'..'f')
    ('0'..'9' | 'a'..'f')
    ('0'..'9' | 'a'..'f')
    ('0'..'9' | 'a'..'f');
UC_ID: 'UC' ( '0' .. '9' | '.' )+;
FLOW_ID: ( '0' .. '9' )+;
COLON: ':';
SLASH: '/';
SEMICOLON: ';';
DOT: '.';
COMMA: ',';
USING: ( 'using' | 'of' | 'with' );
A: ( 'a' | 'an' );
THE: ( 'the' | 'The' );
FAIL: ( 'Fail' | 'fail' );
ACTOR: 'actor';
AS: 'as';
IS: 'is';
MUST: 'must';
WHEN: 'when';
WHERE: 'where';
MEANS: 'means';
AND: 'and';
INCLUDES: ( 'includes' | 'needs' | 'contains' | 'requires' | 'has' );
ACRONYM: 'A' .. 'Z' ( 'A' .. 'Z' )+;
CAMEL: ( 'A' .. 'Z' ( 'a' .. 'z' | '0' .. '9' )* )+;
WORD: ( 'a' .. 'z' | 'A' .. 'Z' | '0' .. '9' )+;
INFORMAL:
    (
        '"' ('\\"' | ~'"')* '"'
        |
        '"""' .+? '"""'
    )
    { this.setText(StringUtils.strip(this.getText(), "\"")); }
    ;
SPACE
    :
    ( ' ' | '\t' | '\n' | '\r' )+
    { skip(); }
    ;
