# -*- coding: utf-8 -*-

import os
import sys

from setuptools import setup, Extension

# Publish the library to PyPI.
if "publish" in sys.argv[-1]:
    os.system("python setup.py sdist upload")
    sys.exit()

# Default compile arguments.
ext = Extension("scats.scats",
                sources=[os.path.join("scats", "scats.cpp")],
                language="c++")

# Hackishly inject a constant into builtins to enable importing of the
# package before the library is built.
if sys.version_info[0] < 3:
    import __builtin__ as builtins
else:
    import builtins
builtins.__SCATS_SETUP__ = True
import scats  # NOQA
from scats.build import build_ext  # NOQA

setup(
    name='scats',
    version='0.1.0',
    author='Pavel Sobolev',
    author_email='paveloom@mail.ru',
    url="https://github.com/Paveloom/C3.1",
    license="Unlicense",
    packages=["scats"],
    setup_requires=["pybind11"],
    install_requires=["pybind11"],
    ext_modules=[ext],
    description='Спектрально-корреляционный анализ временных рядов',
    long_description=open("README.md").read(),
    package_data={"": ["README.md", "LICENSE.md"]},
    include_package_data=True,
    cmdclass=dict(build_ext=build_ext),
    classifiers=[
        "Development Status :: 1 - Planning",
        "Intended Audience :: Developers",
        "Intended Audience :: Science/Research",
        "Natural Language :: Russian",
        "Operating System :: Unix",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Topic :: Scientific/Engineering :: Astronomy",
    ],
    zip_safe=True,
)