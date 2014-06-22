---
layout: default
title: "Types"
date: 2014-05-20
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
---

Type in Requs is a creature similar to a class in
{{{http://en.wikipedia.org/wiki/Object-oriented_programming}object-oriented programming}}.
Type has slots and parent types:

+--
Image is File.
Image has:
width as "pixels",
height as "pixels", and
format as "PNG, GIF, JPEG, etc".
+--

Type names are in {{{http://en.wikipedia.org/wiki/CamelCase}CamelCase Notation}}.
For example, these words are valid type names:
`Image`, `ImageFile`, `ImageInCustomFormat`,
`GIFImage`, `PNG`.

* Slots

A type may have a number of slots. A slot is something similar
to a private property of a Java class, for example. The syntax is simple,
in {{{http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form}BNF}}:

+--
<type> ::= <camel> ( "has" | "needs" | "requires" | "includes" ) ":" <slots> "."
<slots> ::= <slot> (  ( "," | ";" | "and" ) <slot> )*
<slot> ::= <name> ( "as" <informal> )?
+--
