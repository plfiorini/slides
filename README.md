# Slides

These are my slides for various events.

Please install jinja2 and markdown for Python, for example
on Fedora systems:

```sh
yum install python-jinja2 python-markdown
```

Slides are written with Markdown, run the following command
in each subdirectory to generate HTML files:

```sh
python2 render.py
```

Structure:

- io-2012-slides - A git submodule that contains the origin Google I/O 2012 template.
- templates - HTML and CSS templates.
- tools - Various tools to work on slides.
- slides - Actual slides.
