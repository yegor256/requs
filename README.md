<img src="http://img.requs.org/requs.png" width="214px" height="61px" />

More details are here: [www.requs.org](http://www.requs.org/)

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
            <groupId>com.requs</groupId>
            <artifactId>requs-maven-plugin</artifactId>
            <version>1.1</version>
          </plugin>
        </reportPlugins>
      </configuration>
    </plugin>
  </plugins>
</build>
```

Then add requs files to `src/main/requs` and name them as `main.requs`, etc.

Then just run `mvn clean site` and you will see a report at `target/site/requs`.

## Questions?

If you have any questions about the framework, or something doesn't work as expected,
please [submit an issue here](https://github.com/tpc2/requs/issues/new).
If you want to discuss, please use our [Google Group](https://groups.google.com/forum/#!forum/requs).

## How to contribute?

Fork the repository, make changes, submit a pull request.
We promise to review your changes same day and apply to
the `master` branch, if they look correct.

Please run Maven build before submitting a pull request:

```
$ mvn clean install -Pqulice
```
