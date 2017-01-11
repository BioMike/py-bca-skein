from distutils.core import setup, Extension

skein_module = Extension('py_bca_skein',
                               sources = ['skeinmodule.c',
                                          'skeinhash.c',
                                          'skein.c',
                                          'sha2.c'],
                               include_dirs=['.'],
                               extra_compile_args=['-O1'])

setup (name = 'py_bca_skein',
       version = '1.0',
       description = 'Bindings for Skein-myr proof of work hashing algorithm',
       ext_modules = [skein_module])
