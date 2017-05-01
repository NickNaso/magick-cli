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
          "conditions": [
            ['target_arch=="x64"', {
              "variables": {
                "GS4JS_HOME%": "<!(node gs4js-env-home.js)",  
                "GS4JS_LIB%": "gsdll64.lib",
                "GS4JS_DLL%": "gsdll64.dll",
                "conditions": [
                  ['"<!(node gs4js-env-home.js)" == ""', {
                    "GS4JS_HOME%": "C:/gs/bin"
                  }]
                ]
              }
            }, 
            {
              "variables": { 
                "GS4JS_HOME%": "<!(node gs4js-env-home.js)",  
                "GS4JS_LIB%": "gsdll32.lib",
                "GS4JS_DLL%": "gsdll32.dll",
                "conditions": [
                  ['"<!(node gs4js-env-home.js)" == ""', {
                    "GS4JS_HOME%": "C:/gs/bin"
                  }]
                ]
              }
            }]
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          },
          "libraries": ["<(module_root_dir)/build/Release/<(GS4JS_LIB)"],
          "copies": [
            {
              "destination": "<(module_root_dir)/build/Release",
              "files": ["<(GS4JS_HOME)/<(GS4JS_DLL)", "<(GS4JS_HOME)/<(GS4JS_LIB)"]
            }
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