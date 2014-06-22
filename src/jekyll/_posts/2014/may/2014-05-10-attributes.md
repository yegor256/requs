---
layout: default
title: "Requirement Attributes and Seals"
date: 2014-05-10
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
---

Any use case may have attributes assigned to it. Attribute
is a small-caps English word, without spaces or numbers inside.
For example:

{% highlight requs lexer=rrr %}
:UC3.2 is a must.
:UC8 is delivered.
{% endhighlight %}

In this example, `must` is an attribute of `UC3.2` and
`delivered` is an attribute of `UC8`.

We recommend to use attributes for requirements prioritization,
according to [MoSCoW method](http://en.wikipedia.org/wiki/MoSCoW_method):

 * `must`

 * `should`

 * `could`

 * `would`

We also recommend to use attributes for
[requirements prioritization](http://en.wikipedia.org/wiki/Requirement_prioritization):

 * `specified`

 * `implemented`

 * `delivered`

 * `accepted`

* Seals

When attribute is specified, it is possible to "seal" it. A seal is
a 6-signs [hexadecimal](http://en.wikipedia.org/wiki/Hexadecimal)
number, calculated by Requs engine, as an
[MD5](http://en.wikipedia.org/wiki/MD5) hash function of the use
case content.

For example, these two use cases will have two different seals:

{% highlight requs %}
UC3 where nothing happens: "tbd".
UC3 where nothing really happens: "tbd".
{% endhighlight %}

Their signatures are different, that's why their seals are also different.

In order to calculate a seal for your use case, just add
a random seal (for example, `ffffff`)
and run `mvn requs:compile`:

{% highlight requs %}
ffffff:UC3 is a must.
{% endhighlight %}

You will get an error message, similar to this:

{% highlight text %}
[ERROR] 17:0 Seal "2edb8f" at the method UC3 doesn't match "ffffff" at the attribute "must"
{% endhighlight %}

The message means that Requs engine is expecting `2edb8f` as
a seal for all `UC3` attributes. We set it to `ffffff` --- this
breaks the build and makes our Requs specification in-compilable.

Now, we can change `ffffff` to `2edb8f` in the specification
and Requs won't complain any more.

When, in the future, someone changes the content of `UC3`, they will
break the build and will have to change the seal for all attributes.

## Baselined Attributes

This mechanism exists in Requs in order to be able to
[baseline](http://en.wikipedia.org/wiki/Baseline_%28configuration_management%29)
individual requirements in a continuously changing document.

Say, use case `UC3` is already implemented and delivered to
the product owner. It has an attribute `delivered` in the SRS,
and this attribute is sealed.

Then, someone is changing the description of `UC3`. The seal
doesn't work any more and Requs starts complaining. In order to
make the build clean again, the author of these changes has to
remove the seal from the document.

`UC3` doesn't have a seal any more. It is clear for the project
manager, that this use case needs to be implemented and delivered to the
product owner again.

Thus, being a system analyst working with the SRS, be aware that
if any seal doesn't match its expected value after your changes,
you should just remove the seal.

## Who Seals Use Cases?

Seals are supposed to be placed in the SRS by a project manager. Well,
not necessarily a PM, but a person who is responsible for changing
statuses or priorities of requirements.

Usually it happens on project milestones, when priorities are set and
requirements are baselined.

