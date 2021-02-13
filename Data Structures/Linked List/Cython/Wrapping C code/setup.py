from setuptools import setup, Extension
from Cython.Build import cythonize

ext = Extension('CyLinkedList', sources = ['CyLinkedList.pyx', 'SinglyLinkedList.c'])

setup(ext_modules = cythonize([ext]))
