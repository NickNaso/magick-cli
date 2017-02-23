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
            "libraries": [
                '<!@(pkg-config --libs MagickWand)',
                '<!@(pkg-config --libs MagickCore)'
                
          ],
          'cflags': [
            '<!@(pkg-config --cflags --libs MagickWand)',
            '<!@(pkg-config --cflags --libs MagickCore)'
          ]
        }
    ]
}