import os
from setuptools import setup, Extension
from Cython.Build import cythonize

SHARED_OBJECT_PATH = "Object/libgaussianSinc.so"

HEADER_INCLUDE_DIR ="Faddeeva"

extensions = [
	Extension(
		name="bandlimit.GaussianSinc",
		sources=["bandlimit/GaussianSinc.pyx"],
		include_dirs=[HEADER_INCLUDE_DIR],
		extra_objects=[SHARED_OBJECT_PATH],
		runtime_library_dirs=['$ORIGIN']
		)
]

setup(
	packages=['bandlimit'],
	package_dir={'bandlimit':'bandlimit'},
	package_data={'bandlimit':['libgaussianSinc.so']
	},

	ext_modules=cythonize(
		extensions,
                compiler_directives={'language_level':3}
	),
)
