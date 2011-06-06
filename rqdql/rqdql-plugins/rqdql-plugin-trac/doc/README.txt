===========
RqdqlPlugin
===========

Install in development mode:

python setup.py develop -md /path/to/trac_project/plugins

Config
------

[rqdql]
pre_commit_hook = /home/astoon/src/RqdqlPlugin/sample/sample (default is None)
pre_render_hook = /home/astoon/src/RqdqlPlugin/sample/sample (default is None)
check_all = false (default if true)
content_type = application/xhtml+xml (default means not modified)

Admin UI
--------

http://project_url/admin/general/plugin

Open RqdqlPlugin.validation, enable needed components explicity.

Default values
--------------

Default values are defined in: RqdqlPlugin/config.py
