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
                'OTHER_LDFLAGS': ['-stdlib=libc++'],
                'MACOSX_DEPLOYMENT_TARGET': '10.7', # -mmacosx-version-min=10.7
            },
            "libraries": [
                '<!@(pkg-config --libs MagickWand)',
                '<!@(pkg-config --libs MagickCore)'
                
          ],
          'cflags': [
            '<!@(pkg-config --cflags MagickWand)',
            '<!@(pkg-config --cflags MagickCore)'
          ]
        }
    ]
}