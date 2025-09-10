# Controlled Natural Language for Requirements Specifications

[![EO principles respected here](https://www.elegantobjects.org/badge.svg)](https://www.elegantobjects.org)
[![DevOps By Rultor.com](https://www.rultor.com/b/yegor256/requs)](https://www.rultor.com/p/yegor256/requs)
[![We recommend IntelliJ IDEA](https://www.elegantobjects.org/intellij-idea.svg)](https://www.jetbrains.com/idea/)

[![mvn](https://github.com/yegor256/requs/actions/workflows/mvn.yml/badge.svg)](https://github.com/yegor256/requs/actions/workflows/mvn.yml)
[![codecov](https://codecov.io/gh/yegor256/requs/branch/master/graph/badge.svg)](https://codecov.io/gh/yegor256/requs)
[![PDD status](https://www.0pdd.com/svg?name=yegor256/requs)](https://www.0pdd.com/p?name=yegor256/requs)
[![Maven Central](https://maven-badges.herokuapp.com/maven-central/org.requs/requs/badge.svg)](https://maven-badges.herokuapp.com/maven-central/org.requs/requs)
[![Hits-of-Code](https://hitsofcode.com/github/yegor256/requs)](https://hitsofcode.com/view/github/yegor256/requs)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

REQUS is a controlled natural language (CNL) for requirements specifications.
It is explained in detail in [this paper][pdf],
which was published in the
[ACM SIGPLAN International Workshop on Beyond Code: No Code (BCNC)][workshop].
More details about REQUS syntax you can find at
[www.requs.org](https://www.requs.org/).

In order to use it in a Java project, just add this plugin to your `pom.xml`:

```xml
<reporting>
  <plugins>
    <plugin>
      <groupId>org.requs</groupId>
      <artifactId>requs-maven-plugin</artifactId>
      <version>1.17.0</version>
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

```bash
mvn clean install -Pqulice
```

To render the site and edit its pages:

```bash
cd jekyll
bundle install
bundle exec jekyll serve --drafts
```

[pdf]: https://www.yegor256.com/pdf/2021/requs.pdf
[workshop]: https://dl.acm.org/doi/abs/10.1145/3486949.3486963
