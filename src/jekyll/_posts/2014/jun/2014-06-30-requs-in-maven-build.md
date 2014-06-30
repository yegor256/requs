---
layout: default
title: "Requirements Compilation in Maven Build"
date: 2014-06-30
description:
  Requs can be used in Maven build for automated
  requirements compilation
categories: blog
---

Add this plugin to your Maven build
(get their versions from [Maven Central](http://search.maven.org/)):

{% highlight xml %}
<build>
  <plugins>
    <plugin>
      <groupId>org.requs</groupId>
      <artifactId>requs-maven-plugin</artifactId>
      <executions>
        <execution>
          <goals>
            <goal>compile</goal>
          </goals>
        </execution>
      </executions>
    </plugin>
    <plugin>
      <artifactId>maven-site-plugin</artifactId>
      <configuration>
        <reportPlugins combine.self="append">
          <plugin>
            <groupId>org.requs</groupId>
            <artifactId>requs-maven-plugin</artifactId>
            <reportSets>
              <reportSet>
                <reports>
                  <report>default</report>
                </reports>
              </reportSet>
            </reportSets>
          </plugin>
        </reportPlugins>
      </configuration>
    </plugin>
  </plugins>
</build>
{% endhighlight %}

On every run of `compile` phase Requs compiler will
generate its output files in `target/requs`.

On every run of `site` phase you will get the same files
in `target/site/requs` directory.

Keep your source files in `src/requs` with `.req` extension. All
of them will be picked up by Requs compiler, recursively searching
in all sub-directories.

## Extra Configuration

You can add extra configuration parameters to be passed
into Requs compiler, using `options` element:

{% highlight xml %}
<build>
  <plugins>
    <plugin>
      <groupId>org.requs</groupId>
      <artifactId>requs-maven-plugin</artifactId>
      <configuration>
        <options>
          <test.option>hello, world!</test.option>
        </options>
      </configuration>
    </plugin>
  </plugins>
</build>
{% endhighlight %}

All options are passed to the
[`Compiler`](/requs-core/apidoc-1.13/org/requs/Compiler.html)
class as a map of strings.
