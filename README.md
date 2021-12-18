<img src="logo.svg" width="192" />

[![EO principles respected here](https://www.elegantobjects.org/badge.svg)](https://www.elegantobjects.org)
[![Managed by Zerocracy](https://www.0crat.com/badge/CAZPZR9FS.svg)](https://www.0crat.com/p/CAZPZR9FS)
[![DevOps By Rultor.com](http://www.rultor.com/b/yegor256/requs)](http://www.rultor.com/p/yegor256/requs)
[![We recommend IntelliJ IDEA](https://www.elegantobjects.org/intellij-idea.svg)](https://www.jetbrains.com/idea/)

[![Build Status](https://travis-ci.org/yegor256/requs.svg?branch=master)](https://travis-ci.org/yegor256/requs)
[![PDD status](http://www.0pdd.com/svg?name=yegor256/requs)](http://www.0pdd.com/p?name=yegor256/requs)
[![Maven Central](https://maven-badges.herokuapp.com/maven-central/org.requs/requs/badge.svg)](https://maven-badges.herokuapp.com/maven-central/org.requs/requs)

Requs is a controlled natural language (CNL) for requirements specifications.
It explained in details in [this paper](https://www.yegor256.com/pdf/2021/requs.pdf).
More details about its syntax you can find at [www.requs.org](http://www.requs.org/).

In order to use it in a Java project, just add this plugin to your `pom.xml`:

```xml
[...]
<build>
  [...]
  <plugins>
    [...]
    <plugin>
      <artifactId>maven-site-plugin</artifactId>
      <configuration>
        <reportPlugins combine.children="append">
          <plugin>
            <groupId>org.requs</groupId>
            <artifactId>requs-maven-plugin</artifactId>
          </plugin>
        </reportPlugins>
      </configuration>
    </plugin>
  </plugins>
</build>
```

Then, add Requs files to `src/main/requs` and name them as `main.req`, etc.

Then, run `mvn clean site` and you will see a report at `target/site/requs`.

## How to contribute?

Fork the repository, make changes, submit a pull request.
We promise to review your changes same day and apply to
the `master` branch, if they look correct.

Please run Maven build before submitting a pull request:

```
$ mvn clean install -Pqulice
```

Want to edit website pages? Install and run Jekyll:

```
$ jekyll serve -w -D -s src/jekyll -d target/jekyll
```
