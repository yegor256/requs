import os
from setuptools import find_packages, setup

def read(*rnames):
    return open(os.path.join(os.path.dirname(__file__), *rnames)).read()

setup(name='RqdqlPlugin',
      version='0.5',
      description='Wiki pre-commit and pre-render hook plugins for Trac',
      long_description=read('doc/README.txt'),
      author='Ilshad Khabibullin',
      author_email='astoon.net@gmail.com',
      url='http://www.technoparkcorp.com/',
      license='Private use only, inside FaZend.com',
      packages=find_packages('src'),
      package_dir={'':'src'},
      entry_points = """
      [trac.plugins]
      RqdqlPlugin.validation = RqdqlPlugin.validation
      """,
)
