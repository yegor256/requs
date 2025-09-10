---
layout: default
title: "Non-Functional Requirements"
date: 2014-05-15
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
categories: blog
---

Any method (use case) may have an unlimited number of non-functional
requirements (NFRs). They are sometimes called "qualities of service". Wikipedia
has [a list of possible NFRs](http://en.wikipedia.org/wiki/Non-functional_requirement).

Requs allows NFRs be related only to methods (functional requirements).
In other words, you can't say that your entire product should be "scalable".
Or that it has to be multi-language. Or that its mean time between failure
is more than 24 hours.

You should always relate such non-functional attributes to specific
functionalities. There is a reason behind this restriction - we want
NFRs to be testable. If they are testable - there is a tester. If there
is a tester - there is some functionality. If there is a functionality -
it has to be documented as a method (use case).

The syntax is simple:

{% highlight requs %}
UC3.2/MTBF must "be 5 minutes on a standard equipment".
UC7/PERF must "be less than 500 msec per request".
UC8/UI must "speak English and Spanish".
UC9.5.5/PERF must be "less than 100 milliseconds per HTTP request".
{% endhighlight %}

In the future versions of Requs we may have more formal
syntax for NFRs.
