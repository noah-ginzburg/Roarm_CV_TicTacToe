from setuptools import find_packages
from setuptools import setup

setup(
    name='manual_move_action',
    version='0.0.0',
    packages=find_packages(
        include=('manual_move_action', 'manual_move_action.*')),
)
