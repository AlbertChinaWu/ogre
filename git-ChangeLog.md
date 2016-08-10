# Changes in master but not on Bitbucket

## Python Bindings (new component)
* cover OgreMain, RTShaderSystem, Overlay and OgreBites
* allows implementing Listeners in Python (see Sample)
* still rough edged around iterators
* SWIG based: can be extended for C#, Java, etc.

## OgreBites (new component)
* provides simple UI and input handling
* handles set up/ tear down of Ogre
* based on SdkTrays & SdkCameraManager
* includes reusable parts of SampleBrowser

[see a Python sample using OgreBites here](https://github.com/OGRECave/ogre/blob/master/Samples/Python/bites_sample.py)

## GLSupport (new component)
* Factored out GL Support classes that handle GL context creation
* Defines new GLNativeSupport interface. Platform specific classes (e.g. GLX, WGL) no longer directly accessible.
* Shared between all GL RenderSystems
* allows specifying GL context profile (Core, Compability, ES)
* only one place for fixing GLX/ WGL/ Carbon related bugs
* Dropped 10.000 LOC. Could use SDL2 internally to drop even more

## GLES2: use ES context profile on Desktop
* run and test the GLES2/3 RenderSystem on Desktop
* optionally uses GLSupport Module instead of EGL for Extensions/ Context

## RTShaderSystem
* fix flipped Environment Maps using GLSL (GLSES) shaders
* fix different lighting intensity compared to legacy GL

## OgreMain
* restored API compatibility with 1.9 (`StringUtil::BLANK`, `StringUtil::StrStreamType`)
* fix build on iOS using cross-toolchain/ add instructions
* fix GLSLES Shaders for ShadowVolumeExtrudeProgram
* OSX: `externalWindowHandle` expects a `NSWindow*` by default. `macAPICocoaUseNSView=false` switches to old behaviour.
* FileSystemLayer: use `$XDG_CACHE_HOME` as base path on Linux

## Tests
* Visual Tests can be built without OIS
* Unit Tests are run and enforced on each commit on Linux
* Visual Tests are run on each commit on Linux
* Test Suite returns non-null for easy CI integration

[see the results of the Visual Tests for the GL RenderSystems here](https://ogrecave.github.io/ogre/gl_status/)

## Batteries Included
* by default Ogre will now automatically fetch and build its core dependencies

## Emscripten
* added minimal Sample to repository
* added build instructions

[the Emscipten Demo is available online here](https://ogrecave.github.io/ogre/emscripten/)

## SampleBrowser
* uses SDL2 instead of OIS for input when available (Desktop)
* can be compiled without any input. Start a sample using `./SampleBrowser <SampleNumber>`
* neither SDL2 nor OIS needed for Android anymore
* improved input handling on Android
* VolumeTerrain: fixed triplanar texturing shaders 

## EGL in GLNativeSupport ([branch](https://github.com/OGRECave/ogre/pull/185))
* all supported RenderSystems ported to GLNativeSupport 
* allow EGL to create "full" GL Contexts as well
* needed for [real headless rendering](http://devblogs.nvidia.com/parallelforall/egl-eye-opengl-visualization-without-x-server/)
* allows running GL3Plus on EGL (Linux / Mesa EGL)
