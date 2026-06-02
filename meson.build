project('Zetto Archiver',
    'cpp',
    version: '1.0',
    default_options: [
        'cpp_std=c++23',
        'buildtype=plain'
    ])

zlib = dependency('zlib', required: true)

if not zlib.found()
    error('zlib not found! Please install its lib and development files.')
endif

executable('compress',
           'src/compress.cpp',
           dependencies: zlib,
           install: true)

executable('uncompress',
           'src/uncompress.cpp',
           dependencies: zlib,
           install: true)

