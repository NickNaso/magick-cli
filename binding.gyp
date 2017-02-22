{
    "targets": [
        {
            "target_name": "MagickCLI",
            "sources": ["src/magick-cli.cc"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}