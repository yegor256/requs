---
layout: default
title: "Typical Mistakes to Avoid"
date: 2014-06-22
description:
  This article contains a list of most common mistakes
  made during SRS document development; try to avoid them
categories: blog
---

Here is a list of most common mistakes made in SRS
documents. Let's try to avoid them.

## Interface is not a Type

This is **not** correct:

{% highlight requs %}
System contains:
  loginPage "where user can log in",
  API "that allows users to retrieve data".
{% endhighlight %}

Neither login page nor API are slots of the system. They are not slots
at all. They are **interfaces**. Well, API is an interface and login page
is a property of some interface (probably a web UI).

In order to define interfaces you should use non-functional requirements:

{% highlight requs %}
UC1/UI must "contain a login page, where use can log in".
UC2/API must "be accessible through API that allows users to retrieve data".
{% endhighlight %}

Then, you can explain interfaces even further, forwarding a reader
to supplementary pages:

{% highlight requs %}
UC1/UI must "comply to WebUI".
WebUI: """
Long description of the web UI, with images and mock screens...
"""
{% endhighlight %}

It is totally OK to have long informal descriptions of interfaces.

## Avoid Comments and TODO

The first slot in this example is correct, while the second one is wrong:

{% highlight requs %}
Employee contains:
  name "first and last name or a nick name or maybe an empty field",
  email "an address (@todo check whether we should obey RFC 5322)".
{% endhighlight %}

It is totally correct to give unclear and ambiguous definitions
inside informal texts. That's exactly what they are for! Using this
specification a programmer will be able to implement the name of
employee, because it has all the information he needs. If this information
is not sufficient enough and he will need a more precise and correct
definition, he will submit a bug.

The second slot will make a programmer stuck &mdash; can I implement
it already or I should wait for someone doing this checking? Should
I submit a bug? Or it was already submitted?

Again, informal texts **are** todo-s. No need to define todo-s inside
todo-s.

## Avoid Over-Specifying

SRS document is not intended to become a complete description of
the system for programmers and architects. Instead, the SRS should
describe **as little as possible**. This use case is definitely
wrong:

{% highlight requs %}
UC5 where User (a user) logs in:
  1. The user "clicks LOGIN button";
  2. The user "enters email and password";
  3. The user "clicks SUBMIT button".
{% endhighlight %}

This use case restricts system implementers. It gives too many
details about the login flow, while none of these requirements were
actually provided by the product owner. The product owner doesn't
care about this specific flow. All he wants is to have an ability
for his users to log into the system. How exactly will it happen,
he doesn't really care.

Providing so many extra details in the SRS makes the document
less readable and much more vague.
