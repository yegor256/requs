---
layout: default
title: "Requirements Specifications Automated"
date: 2014-06-22
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
---

IEEE 830-1998 says: "SRS (software requirements specification) should be
correct, unambiguous, complete, consistent, ranked for importance and/or stability,
verifiable, modifiable, traceable".

As a controlled natural language (CNL) Requs enables the creation
of such documents in plain text format. Requs resembles English
but has a very strict syntax and semantic.

Try online demo: [demo.requs.org](http://demo.requs.org/).

## Recent Articles

<ul>
{% for post in site.categories.blog %}
  <li><a href="{{ post.url }}">{{ post.title }}</a></li>
{% endfor %}
</ul>

## Blog Posts

Check also this blog post:
[Incremental Requirements With Requs](https://www.yegor256.com/2014/04/26/incremental-requirements-with-requs.html).
It explains how Requs is used in [XDSD](https://www.xdsd.org) projects by
[Zerocracy](https://www.zerocracy.co).
