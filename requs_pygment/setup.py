# -*- coding: utf-8 -*-
from setuptools import setup, find_packages

setup(
    name='requs_pygment',
    version='0.1',
    packages=find_packages(),
    install_requires=['pygments'],
    py_modules=['requs_pygment'],
    author='Yegor Bugayenko',
    author_email='yegor256@gmail.com',
    description='Requs Highlighting Pygment',
    license='BSD',
    keywords='requs',
    url='http://www.requs.org/',
    entry_points={
        'pygments.lexers': [
            'requs = requs_pygment:RequsLexer'
        ]
    }
)
