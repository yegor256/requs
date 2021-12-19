<img src="https://www.polystat.org/logo.svg" height="92px"/>

[![make](https://github.com/polystat/polystat/actions/workflows/latexmk.yml/badge.svg)](https://github.com/polystat/polystat/actions/workflows/latexmk.yml)

The PDF is here: [wp.pdf](https://www.polystat.org/wp.pdf).

To build it you need to have LaTeX, GNU aspell,
[texqc](https://github.com/yegor256/texqc),
and
[texsc](https://github.com/yegor256/texsc) installed. 
Then, just do this:

```bash
$ latexmk -pdf
```

Everything will be built just fine and you will get the `.pdf` file.
