<p>
 
<img height="64" src="https://i.imgur.com/oXRdycNl.png">

<br>

Javascript's God Mode : one language to rule them all. Code everything, everywhere, for everything, in JavaScript.

No VM. No Bytecode. No Garbage Collector. Full Compiled and Native binaries.

**NectarJS** is a **JavaScript native compiler**.

**NectarJS** is able to compile native apps for: Windows, Mac, Linux, iOS, Android, Raspberry, STM32 and more.

**NectarJS** aims to make JavaScript universal.

**NectarJS** is in active development, join us on [Discord](https://discord.gg/cpe2UuN) on [IRC](https://kiwiirc.com/client/irc.freenode.net/#nectarjs) if you need more information.

**NectarJS** roadmap is on [Trello](https://trello.com/invite/b/6F4rvEj2/9d7677f9dc6b5bf2f5b33e45fc794182/nectarjs)

**NectarJS** [Quick Start](https://nectarjs.com/docs/nectarjs/quick-start/) documentation

**NectarJS** [Quick Hack](https://nectarjs.com/docs/contribute/quick-hack/) documentation

**NectarJS** Full documentation is here (WIP) : [NectarJS Doc](https://nectarjs.com/documentation/)

</p>

# Efficiency

Some benchmarks with the file example/fibo.js and differents fibos arguments:

|          | NodeJS v12.8.1 | QuickJS 2020-07-05 | NectarJS v0.6.104     |
|----------|----------------|--------------------|-----------------------|
| fibo(30) | 0.15s / 7.0Mb  | 0.20s / 1.1Mb      | **0.07s / 1.1Mb**     |
| fibo(40) | 1.80s / 7.0Mb  | 21.06s / 1.1Mb     | **0.50s / 1.0Mb**     |
| fibo(45) | 19.44s / 7.0Mb | 238.85s / 1.1Mb    | **4.82s / 1.0Mb**     |

# Main objectives
* Supporting EcmaScript 3 standard (then 5, 6 ...)
* Supporting NodeJS and NPM ecosystem
* Supporting a maximum of platforms (Windows, Mac, Linux, Android, Arduino, ...)
* Being secure
* Embeding debuging tools
* Compile everything that can be transpiled in JS : Ruby (Opal), Python (Transcript, Brython, JavaScrypthon), TypeScript ...

# Install
 
```
npm install -g nectarjs
```

# Starting with compilation

The simplest way to use NectarJS is :

```
nectar file.js
```

The output file name will be automatically chosen regarding the target. You can specify another output with `-o something.out`

To show more compilation infos :

```
nectar --verbose file.js
```

Changing the stack size (usefull on Windows) :

```
nectar --stack 10000000 flood.js
```

For more informations about compilation output, use `--verbose`

For help, use `--help`

# Using native compiler

* You need to have GCC installed on your machine and registered in your path to compile.

## Testing your installation

You can test your installation by running `npm run njs_test` 

You can also test ES3 support with `npm run es3_test`

## Windows

You can install Mingw for Windows here : https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/

You can also install Linux for Windows and use a linux system on Windows

## Linux / FreeBSD

On Linux or FreeBSD, you can install it with your distro (apt install gcc, yum install gcc, ...). You can use GCC, CLANG, or any derivative of those compilers (arm-gcc ...)

## Apple iOS

You can install xCode and you are ready.

## First compilation

```
nectar -b native file.js
or
nectar file.js
```

You can select a preset (speed or size):

```
nectar file.js --preset [speed|size]
```

You can also run the compiled executable just after compilation using --run:

```
nectar file.js --run
```

You can enable the quiet mode with --quiet:

```
nectar file.js --quiet
```

# Using compiler environments

NectarJS supports various compilation env:
* std
* node
* arduino
* wasm
* android

To compile a file using an env, you can use the --env switch :

```
nectar arduino-led.js --env arduino --target mega2560
```

# Android compilation

First step, you have to install Android SDK and Android NDK.

Second step, you need to setup NectarJS with the paths of the SDK and the NDK :

```
nectar --setsdk path_to_sdk --setndk path_to_ndk
```

You can show your configuration with: `nectar --config`

Third step: compile your JS app for Android using :

`nectar file.js --env android`

The result file is an Android APK.

You can select your target with `--target release|debug`.

Need: SDK Android-19 and Android-28
NDK: tested with NDK 21

# iOS compilation

You need Xcode to be able to compiler applications with NectarJS.

To compile a iOS app, select the iOS env with the flag --env ios :

`nectar app.js --env ios`

You can also target a plateform for running simulation :

`nectar app.js --env ios --target 'iPhone-8, 13.5' --run`

NectarJS will then compile your app and launch it with the simulator.

To test your configuration, you can compile example/ios.js app.

# STM32 compilation

To compile SMT32 firmware with NectarJS, you need first to instal mbed-cli and to setup your environment:

`https://os.mbed.com/docs/mbed-os/v6.0/build-tools/install-and-set-up.html`

Once done, compile your code by selecting the stm32 env, and choosing a target: 

`nectar example/stm32.js --env stm32 --target NUCLEO_F446RE`

You can select a preset (speed or size) with:

`--preset speed` or `--preset size`

# Compatibility targets/platforms :

* All supported GCC platforms

* All supported Clang platforms

* All supported AVR-GCC platforms

# Store 

NectarJS compiled apps are tested to be publishable on :

* Apple Store
    * https://apps.apple.com/fr/app/hiphen-plant/id1523867733

# Actively tested for :

* android

* wasm

* asm-js

* wast

* mac-osx

* linux-x86-32

* linux-x86-64

* linux-arm32v7

* win-x86-32

* win-x86-64

* Sun OS

* arduino-nano

* arduino-uno

* arduino-mega1280

* arduino-mega2560

* nucleo-l152re

* nucleo-l432kc

* nucleo-f446re

# String

* .length
* .toString()
* .indexOf(needle)
* .lastIndexOf(needle)
* .search(needle)
* .slice(start, end)
* .substring(start, end)
* .substr(start, end)
* .replace(needle, str)

# Array

* .length
* .push(value)
