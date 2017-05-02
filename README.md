<p align="center">
<img src="https://raw.githubusercontent.com/NickNaso/magick-cli/master/node-love-imagemagick.png"/>
</p>

# MagickCLI

## Native ImageMagick CLI for Node.js

* [Introduction](#introduction)
* [Motivations](#motivations)
* [Prerequisites](#prerequisites)
* [Installation](#install)
* [Installation options](#installoptions)
* [Usage](#usage)
* [Team](#team)
* [Acknowledgements](#acknowledgements)
* [License](#license)

<a name="introduction"></a>

## Introduction

**ImageMagick** is a free and open-source software suite for displaying, converting, and editing raster and vector 
image files. It utilizes multiple computational threads to increase performance and can read, process, or write mega-, 
giga-, or tera-pixel image sizes.

### More resource and info about ImageMagick

* [Introduction to ImageMagick](http://imagemagick.org/script/index.php)

* [ImageMagick on Wikipedia](https://en.wikipedia.org/wiki/ImageMagick)

* [ImageMagick command-line](http://imagemagick.org/script/command-line-processing.php)

<a name="motivations"></a>

## Motivations

At the time i created this module i was not able to find any module on npm that execute ImageMagick command through its C API,
otherwise there were some module that call ImageMagick through the execution of the corresponding shell command. This is a
good way to start using some library from node, but there are the following drawbacks:

* **Performance** - The call to the shell command take more time and more resources than calling a library C or C++ API directly from Node.js environment.

* **Errror handler** - Sometimes you cannot intercept and handle errors in a good and a proper way.

To fit all needs MagickCLI has sync and async methods so it could be used in a web application where it's very important
to not block the event loop, so all requests will be served without any delay originated by our application.

[Understanding Node.js event loop](https://nodesource.com/blog/understanding-the-nodejs-event-loop/)

<a name="prerequisites"></a>

## Prerequisites

Before installing MagickCLI you need to assure you have the following prerequisites:

* **Node.JS** see: [Installing Node.js via package manager](https://nodejs.org/en/download/package-manager/)

* **Node.js native addon build tool** see: [node-gyp](https://github.com/nodejs/node-gyp)

* **ImageMagick** for your Operating System.

## At moment MagickCLI is fully compatible with ImgameMagick from version 7.0.1 to 7.0.5

## Linux

You can install ImageMagick from binary or directly from source:

* [Install from soucre](http://imagemagick.org/script/install-source.php#unix)

* [Install from binary](http://imagemagick.org/script/download.php#unix)

Maybe your linux distribution has already packaged ImageMagick version 7.0.1 or above
so you can install it using your package manager and all is more simple.

## Windows

* Download the installer for your platform from this link [ImageMagick Windows Installer](http://imagemagick.org/script/download.php#windows)

* Install ImageMagick on your system.

## macOS

* Install Homebrew following the official guide [here](https://brew.sh/index_it.html)

* Open terminal and install ImageMagick

```bash
brew install imagemagick
``` 

* Open terminal and install **pkg-info**

```bash
brew install pkg-info
```

<a name="install"></a>

## Installation

If you want to use **MagickCLI** you have to install it. There are two methods for that:

In dependencies of your ```package.json``` add the following item:

```json
"magick-cli": "version"
```

then digit

```console
npm install
```

**Example**:

```json
"magick-cli": "*" for the latest version
"magick-cli": "1.0.0" for the version 1.0.0
```

**OR**

launch this command:

```console
npm install magick-cli --save
```

<a name="team"></a>

## The Team

### Nicola Del Gobbo

<https://github.com/NickNaso/>

<https://www.npmjs.com/~nicknaso>

<https://twitter.com/NickNaso>

### Mauro Doganieri

<https://github.com/mauro-d>

<https://www.npmjs.com/~mauro-d>

<https://twitter.com/maurodoganieri>

<a name="acknowledgements"></a>

## Acknowledgements

Thank you to all people that encourage me every day.

<a name="license"></a>

## License

Licensed under [Apache license V2](./LICENSE)