# -*- coding: utf-8 -*-
from setuptools import setup, find_packages
setup(
    name = 'requs-pygment',
    version = '0.1',
    packages = find_packages(),
    install_requires = ['pygments'],
    author = 'Yegor Bugayenko',
    author_email = 'yegor@tpc2.com',
    description = 'Requs Highlighting Pygment',
    license = 'BSD',
    keywords = 'requs',
    url = 'http://www.requs.org/',
    entry_points = {
        'pygments.lexers': [
            'requs = requs:RequsLexer'
        ]
    }
)
