<img src="logo.svg" width="192" />

[![EO principles respected here](https://www.elegantobjects.org/badge.svg)](https://www.elegantobjects.org)
[![Managed by Zerocracy](https://www.0crat.com/badge/CAZPZR9FS.svg)](https://www.0crat.com/p/CAZPZR9FS)
[![DevOps By Rultor.com](http://www.rultor.com/b/yegor256/requs)](http://www.rultor.com/p/yegor256/requs)
[![We recommend IntelliJ IDEA](https://www.elegantobjects.org/intellij-idea.svg)](https://www.jetbrains.com/idea/)

[![mvn](https://github.com/yegor256/requs/actions/workflows/mvn.yml/badge.svg)](https://github.com/yegor256/requs/actions/workflows/mvn.yml)
[![codecov](https://codecov.io/gh/yegor256/requs/branch/master/graph/badge.svg)](https://codecov.io/gh/yegor256/requs)
[![PDD status](http://www.0pdd.com/svg?name=yegor256/requs)](http://www.0pdd.com/p?name=yegor256/requs)
[![Maven Central](https://maven-badges.herokuapp.com/maven-central/org.requs/requs/badge.svg)](https://maven-badges.herokuapp.com/maven-central/org.requs/requs)
[![Hits-of-Code](https://hitsofcode.com/github/yegor256/requs)](https://hitsofcode.com/view/github/yegor256/requs)
![Lines of code](https://img.shields.io/tokei/lines/github/yegor256/requs)

REQUS is a controlled natural language (CNL) for requirements specifications.
It is explained in details in [this paper](https://www.yegor256.com/pdf/2021/requs.pdf),
which was published in the
[Proceedings of the 1st ACM SIGPLAN International Workshop on Beyond Code: No Code (BCNC)](https://dl.acm.org/doi/abs/10.1145/3486949.3486963).
More details about REQUS syntax you can find at [www.requs.org](http://www.requs.org/).

In order to use it in a Java project, just add this plugin to your `pom.xml`
(get the latest version [from here](https://github.com/yegor256/requs/releases)):

```xml
<reporting>
  <plugins>
    <plugin>
      <groupId>org.requs</groupId>
      <artifactId>requs-maven-plugin</artifactId>
      <version>...</version>
    </plugin>
  </plugins>
</reporting>
```

Then, add REQUS files to `src/main/requs` and name them as `main.req`, etc.

Then, run `mvn clean site` and you will see a report at `target/site/requs`.

## How to contribute?

Fork the repository, make changes, submit a pull request.
We promise to review your changes same day and apply to
the `master` branch, if they look correct.

Please run Maven build before submitting a pull request:

```
$ mvn clean install -Pqulice
```

To render the site and edit its pages:

```
$ cd jekyll
$ bundle install
$ bundle exec jekyll serve --drafts
```
