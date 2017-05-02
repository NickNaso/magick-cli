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

<a name="usage"></a>

## Usage

```js
'use strict'

const MagickCLI = require('magick-cli')

try {
  // Take decision based on ImageMagick version
  const version = MagickCLI.version()
  console.log(version)
  MagickCLI.executeSync('magick input.png -resize 50% output.png')
} catch (err) {
  // Handle error
  throw err
}
```

## API

### version

**version()** method returns an string that represent the version of ImageMagick library
installed on the system. It is important in those circumstances where you have to take
decision based on different version.

#### Example - version

```js
'use strict'

const MagickCLI = require('magick-cli')

try {
  const version = MagickCLI.version()
  console.log(version)
  // Take decision based on ImageMagick version
  if (version != 7.0.1) {
    // ... some stuff
  } else {
    // ... other stuff
  }
} catch (err) {
  // Handle error
  throw err
}
```

### executeSync

**executeSync(cmd)** method takes the ImageMagick command parameters in input as a string and executes in a synchronous way.
If something wrong happens in calling this method an Error with description and code error will be thrown.

#### Example - executeSync

```js
'use strict'

const MagickCLI = require('magick-cli')

try {
  MagickCLI.executeSync('magick input.png -resize 50% output.png')
} catch (err) {
  // Handle error
  throw err
}
```

### execute

**execute(cmd, callback)** method takes in input the ImageMagick command parameters as a string and an optional callback. 
The execution will be asynchronous so this ensure better performance especially in a web application enviroment, because 
it'll not block the Node.Js event loop.
This method has an optional callback function as input, in that case, a possible error will be handled by this function. 
If noone function will be provided the method returns a Promise that will be resolved or rejected as reported in the 
following example.

#### Example - execute

```js
'use strict'

const MagickCLI = require('magick-cli')

let cmd = 'magick input.png -resize 50% output.png'
MagickCLI.execute(cmd, function (err) {
  if (err) {
    console.log("Ooops... something wrong happened")
  }
})

```

```js
'use strict'

const MagickCLI = require('magick-cli')

let cmd = '-magick input.png -resize 50% output.png'
MagickCLI.execute(cmd)
.then(() => {
  console.log("All is ok")
})
.catch((err) => {
 console.log("Ooops... something wrong happened")
})

```

### Error

The error raised from **magick-cli** in all of its method is an instance of Error object that cointains a message that
describes what happened and at the same time cointains the ImageMagick error code so you can inspect what happened in a better
way.

### Min and Max supported revision

This module was built based on ImageMagick C API that is compatible with some specifics versions. The module has two
properties  **MIN_SUPPORTED_REVISION** and **MAX_SUPPORTED_REVISION** which respectively indicate the minimum and maximum
supported ImageMagick's version.

#### Example - Min and Max supported revision

```js
'use strict'

const MagickCLI = require('magick-cli')

console.log(MagickCLI.MIN_SUPPORTED_REVISION)
console.log(MagickCLI.MAX_SUPPORTED_REVISION)

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