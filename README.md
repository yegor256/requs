<img src="http://img.requs.org/logo-384x128.png" width="192" height="64" />

[![Build Status](https://travis-ci.org/tpc2/requs.svg?branch=master)](https://travis-ci.org/tpc2/requs)

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
            <version>1.3</version>
          </plugin>
        </reportPlugins>
      </configuration>
    </plugin>
  </plugins>
</build>
```

Then, add Requs files to `src/main/requs` and name them as `main.req`, etc.

Then, run `mvn clean site` and you will see a report at `target/site/requs`.

Requg syntax is explained [here](http://www.requs.org/syntax.html).

## Questions?

If you have any questions about the framework, or something doesn't work as expected,
please [submit an issue here](https://github.com/tpc2/requs/issues/new).

## How to contribute?

Fork the repository, make changes, submit a pull request.
We promise to review your changes same day and apply to
the `master` branch, if they look correct.

Please run Maven build before submitting a pull request:

```
$ mvn clean install -Pqulice
```
