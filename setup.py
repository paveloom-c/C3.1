from setuptools import setup, Extension
from Модуль.scats.build import get_pybind_include, BuildExt

__version__ = '0.2.1'

ext_modules = [
    Extension(
        'scats',
        ['Модуль/scats/scats.cpp'],
        include_dirs=[
            # Путь к библиотеке scats
            'Библиотека/scats',

            # Путь к заголовочным файлам pybind11
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
        language='c++'
    ),
]

setup(
    name='scats',
    version=__version__,
    author='Pavel Sobolev',
    author_email='paveloom@mail.ru',
    url='https://github.com/Paveloom/C3.1',
    license="Unlicense",
    description='Спектрально-корреляционный анализ временных рядов',
    long_description=open("README.md").read(),
    long_description_content_type='text/markdown',
    package_data={"": ["README.md", "LICENSE.md"]},
    include_package_data=True,
    package_dir={'':'Модуль/scats'},
    ext_modules=ext_modules,
    install_requires=['setuptools', 'pybind11>=2.4', 'wheel'],
    setup_requires=['pybind11>=2.4'],
    cmdclass={'build_ext': BuildExt},
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
    zip_safe=True
)