{ 
  "targets": [
    {
      "target_name": "MagickCLI",
      "sources": ["src/magick-cli.cc"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ['OS=="linux" or OS=="solaris" or OS=="freebsd"', {
          "libraries": [
            '<!@(pkg-config --libs MagickWand)',
            '<!@(pkg-config --libs MagickCore)'
          ],
          'cflags': [
            '<!@(pkg-config --cflags MagickWand)',
            '<!@(pkg-config --cflags MagickCore)'
          ]
        }],
        ['OS=="win"', {
          "variables": {
            "MAGICK%": '<!(python magick-cli-path.py)'
          } ,
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          },
          "libraries": [
            '-l<(MAGICK)/lib/CORE_RL_MagickWand_.lib',
            '-l<(MAGICK)/lib/CORE_RL_MagickCore_.lib'
          ],
          "include_dirs": [
            '<(MAGICK)/include'
          ]
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': [
                    '<!@(pkg-config --cflags MagickCore)',
                    '<!@(pkg-config --cflags MagickWand)'
                ],
                'OTHER_CPLUSPLUSFLAGS' : [
                    '<!@(pkg-config --cflags MagickCore)',
                    '<!@(pkg-config --cflags MagickWand)'
                    '-std=c++11',
                    '-stdlib=libc++',
                ],
                'OTHER_LDFLAGS': ['-stdlib=libc++']
          },
          "libraries": [
            '<!@(pkg-config --libs MagickWand)',
            '<!@(pkg-config --libs MagickCore)'
          ],
          'cflags': [
            '<!@(pkg-config --cflags MagickWand)',
            '<!@(pkg-config --cflags MagickCore)'
          ]
        }]
      ]
    }
  ]
}
