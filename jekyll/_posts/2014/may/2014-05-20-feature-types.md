---
layout: default
title: "Types"
date: 2014-05-20
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
categories: blog
---

Type in Requs is a creature similar to a class in
[object-oriented programming](http://en.wikipedia.org/wiki/Object-oriented_programming).
Type has slots and parent types:

{% highlight requs %}
Image is File.
Image has:
width as "pixels",
height as "pixels", and
format as "PNG, GIF, JPEG, etc".
{% endhighlight %}

Type names are in [CamelCase Notation](http://en.wikipedia.org/wiki/CamelCase).
For example, these words are valid type names:
`Image`, `ImageFile`, `ImageInCustomFormat`,
`GIFImage`, `PNG`.

## Slots

A type may have a number of slots. A slot is something similar
to a private property of a Java class, for example. The syntax is simple,
in [BNF](http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form):

{% highlight text %}
<type> ::= <camel> ( "has" | "needs" | "requires" | "includes" ) ":" <slots> "."
<slots> ::= <slot> (  ( "," | ";" | "and" ) <slot> )*
<slot> ::= <name> ( "as" <informal> )?
{% endhighlight %}

## Good and Bad Types

Very often we make mistakes when declaring a new type or
modifying an existing one. Read them carefully and try to avoid
in your SRS documents.
