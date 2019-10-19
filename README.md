<img src="http://img.requs.org/logo.svg" width="192" />

[![EO principles respected here](https://www.elegantobjects.org/badge.svg)](https://www.elegantobjects.org)
[![Managed by Zerocracy](https://www.0crat.com/badge/CAZPZR9FS.svg)](https://www.0crat.com/p/CAZPZR9FS)
[![DevOps By Rultor.com](http://www.rultor.com/b/teamed/requs)](http://www.rultor.com/p/teamed/requs)
[![We recommend IntelliJ IDEA](https://www.elegantobjects.org/intellij-idea.svg)](https://www.jetbrains.com/idea/)

[![Build Status](https://travis-ci.org/teamed/requs.svg?branch=master)](https://travis-ci.org/teamed/requs)
[![PDD status](http://www.0pdd.com/svg?name=yegor256/requs)](http://www.0pdd.com/p?name=yegor256/requs)
[![Maven Central](https://maven-badges.herokuapp.com/maven-central/org.requs/requs/badge.svg)](https://maven-badges.herokuapp.com/maven-central/org.requs/requs)

More details are here: [www.requs.org](http://www.requs.org/)

Check this online demo: [demo.requs.org](http://demo.requs.org/)

You need to add this plugin to your `pom.xml`:

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

See [Requs syntax explained](http://www.requs.org/syntax.html).

## Questions?

If you have any questions about the framework, or something doesn't work as expected,
please [submit an issue here](https://github.com/teamed/requs/issues/new).

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
