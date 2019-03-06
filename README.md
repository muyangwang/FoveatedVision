# FoveatedVision Library

A c++ project based on
[![N|Solid](https://opencv.org/assets/theme/logo.png)](https://opencv.org/)

FoveatedVision Library aims at creating a tool to accerate image processing.

# Table of Contents
1. [Innovation](#Innovation)
2. [Build](#Build)
3. [API](##API)
4. [Demos](#demo)

## Innovation
Human vision has a 
## Build

##### File structures
The file structure of the project:
| DirName | Usage |
| ------ | ------ |
| FVlibs | C++ Library for foveated Vision|
| Matlab | Matlab test codes |
| demo | several demo programs using the libray |
| test | testcases |
| utilities | utility functions/files |
| img | Used image and results |

##### Prerequest
The project requires installation of opencv libraries(Version used: `openCV 4.0.1`) and support for `c++11`.

You can install openCV through [`homebrew`](https://brew.sh/) on Mac:
```sh
$ brew install opencv
$ brew install pkg-config
```
You can install openCV from [`source`](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html) or package manager on Linux machines.

Make sure 
```sh
$ pkg-config opencv --cflags --libs
```
can correctly return link info for opencv libraries.


To build the library only:
```sh
$ cd FVlibs
$ make clean
$ make libs
```
A static library named `FVlib.a` will be created. Use the library with the `.h` files in the same directory.

To build demos, execute 
```sh
$ cd demo
$ make demo1
$ make demo2
$ make demo3
```
to build each demo separately if **the library is already compiled and saved as FVlibs/FVlib.a**.

To build **the library and all demos together**, execute
```sh
$ cd demo
$ chmod +x build.sh
$ ./build.sh
```
## API
The library structure:
| filename | Usage |
| ------ | ------ |
| color.h/cpp | color class for foveated images|
| field.h | field class storing info of each layer |
| foveatedImage.h/cpp | foveatedImage class |
| foveatredVideo.h/cpp | fv class for webcam stream(not implemented yet) |
| img | Used image and results |

foveatedImage.h/cpp `foveatedImage_t` class member function interface:

```sh
1. foveatedImage_t::foveatedImage_t(cv::Mat* rawImage, cv::Point centerPosition, channel_t channel);
```
Create a foveated image object from an openCV Mat image. Must specify fovea center on the raw image. Color channel can be either `bgr` or `grayscale`.

```sh
2. void foveatedImage_t::resetCenter(cv::Point newCenter);
```
Choose a new center for current foveated image.

```sh
3. cv::Mat* createReconstructedImage();
```
Create a visualized reconstructed foveated image.
Example raw image and corresponding reconstructed image :
<p float="left">
  <img src="img/raw.png" width="400" />
  <img src="img/recon.png" width="300" /> 
</p>



## demo













  - Type some Markdown on the left
  - See HTML in the right
  - Magic

# New Features!

  - Import a HTML file and watch it magically convert to Markdown
  - Drag and drop images (requires your Dropbox account be linked)


You can also:
  - Import and save files from GitHub, Dropbox, Google Drive and One Drive
  - Drag and drop markdown and HTML files into Dillinger
  - Export documents as Markdown, HTML and PDF

Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site][df1]

> The overriding design goal for Markdown's
> formatting syntax is to make it as readable
> as possible. The idea is that a
> Markdown-formatted document should be
> publishable as-is, as plain text, without
> looking like it's been marked up with tags
> or formatting instructions.

This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

### Tech

Dillinger uses a number of open source projects to work properly:

* [AngularJS] - HTML enhanced for web apps!
* [Ace Editor] - awesome web-based text editor
* [markdown-it] - Markdown parser done right. Fast and easy to extend.
* [Twitter Bootstrap] - great UI boilerplate for modern web apps
* [node.js] - evented I/O for the backend
* [Express] - fast node.js network app framework [@tjholowaychuk]
* [Gulp] - the streaming build system
* [Breakdance](http://breakdance.io) - HTML to Markdown converter
* [jQuery] - duh

And of course Dillinger itself is open source with a [public repository][dill]
 on GitHub.

### Installation

Dillinger requires [Node.js](https://nodejs.org/) v4+ to run.

Install the dependencies and devDependencies and start the server.

```sh
$ cd dillinger
$ npm install -d
$ node app
```

For production environments...

```sh
$ npm install --production
$ NODE_ENV=production node app
```

### Plugins

Dillinger is currently extended with the following plugins. Instructions on how to use them in your own application are linked below.

| Plugin | README |
| ------ | ------ |
| Dropbox | [plugins/dropbox/README.md][PlDb] |
| Github | [plugins/github/README.md][PlGh] |
| Google Drive | [plugins/googledrive/README.md][PlGd] |
| OneDrive | [plugins/onedrive/README.md][PlOd] |
| Medium | [plugins/medium/README.md][PlMe] |
| Google Analytics | [plugins/googleanalytics/README.md][PlGa] |


### Development

Want to contribute? Great!

Dillinger uses Gulp + Webpack for fast developing.
Make a change in your file and instantanously see your updates!

Open your favorite Terminal and run these commands.

First Tab:
```sh
$ node app
```

Second Tab:
```sh
$ gulp watch
```

(optional) Third:
```sh
$ karma test
```
#### Building for source
For production release:
```sh
$ gulp build --prod
```
Generating pre-built zip archives for distribution:
```sh
$ gulp build dist --prod
```
### Docker
Dillinger is very easy to install and deploy in a Docker container.

By default, the Docker will expose port 8080, so change this within the Dockerfile if necessary. When ready, simply use the Dockerfile to build the image.

```sh
cd dillinger
docker build -t joemccann/dillinger:${package.json.version} .
```
This will create the dillinger image and pull in the necessary dependencies. Be sure to swap out `${package.json.version}` with the actual version of Dillinger.

Once done, run the Docker image and map the port to whatever you wish on your host. In this example, we simply map port 8000 of the host to port 8080 of the Docker (or whatever port was exposed in the Dockerfile):

```sh
docker run -d -p 8000:8080 --restart="always" <youruser>/dillinger:${package.json.version}
```

Verify the deployment by navigating to your server address in your preferred browser.

```sh
127.0.0.1:8000
```

#### Kubernetes + Google Cloud

See [KUBERNETES.md](https://github.com/joemccann/dillinger/blob/master/KUBERNETES.md)


### Todos

 - Write MORE Tests
 - Add Night Mode

License
----

MIT


**Free Software, Hell Yeah!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>

