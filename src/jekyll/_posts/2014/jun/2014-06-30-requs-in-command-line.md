---
layout: default
title: "Requirements Compilation in Command Line"
date: 2014-06-30
description:
  Requs can be used in command line for automated
  requirements compilation
categories: blog
---

First, download the latest `requs-exec.jar` from
[Maven Central](http://search.maven.org/#search%7Cga%7C1%7Ca%3A%22requs-exec%22).

Then, run it like this:

{% highlight bash %}
$ java -jar requs-exec.jar -i <input> -o <output>
{% endhighlight %}

`input` is an absolute path of directory with `.req` files.

`output` is a directory path where result files will be stored.

That's it.
