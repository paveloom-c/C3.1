# -*- coding: utf-8 -*-

import os
import scats

extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.intersphinx",
    "sphinx.ext.napoleon",
    "sphinx.ext.mathjax",
]
intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'numpy': ('https://docs.scipy.org/doc/numpy/', None),
}

templates_path = ["_templates"]
source_suffix = ".rst"
master_doc = "index"

# General information about the project.
project = "scats"
author = "Pavel Sobolev"
copyright = "2020, " + author

version = scats.__version__
release = scats.__version__

exclude_patterns = ["_build"]
pygments_style = "sphinx"

import sphinx_rtd_theme
html_theme = "sphinx_rtd_theme"
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

html_context = dict(
    display_github=True,
    github_user="Paveloom",
    github_repo="C3.1",
    github_version="master",
    conf_py_path="/Документация/",
)
html_static_path = ["_static"]
html_show_sourcelink = False