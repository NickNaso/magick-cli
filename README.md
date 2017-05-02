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