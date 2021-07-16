# Mu, a Palm OS Emulator

The continuation of the Mu along with the RetroArch Core is dedicated to
Emily (1998-2020), your friendship was very important to me and I hope
that you are resting well.
 -- Your friend, Stephanie

# The goal of this project

This is a complete restart of my Palm OS emulator, with the last one the code got too messy and the goal too ambitious(to emulate every palm API in software and for compatibility with all Palm OS versions and devices).

To emulate every part of the Palm m515 that is used by the OS perfectly.
This means no hacks like POSE where API calls are intercepted and replaced with those that dont use the actual hardware.
It is also written in C for RetroArch so it will run on everything at the start, not just Win95 like POSE and Copilot and is being developed with modern emulator features in mind, save/load state and overclocking are available from the start.

## Why the m515?

It is the best Palm brand OS 4 device that has no special hardware builtin(cellphone, barcode scanner, keyboard attachment), it has a color screen, and available ROM dumps.

## What about accessories?

The Palm keyboard attachment will likely be emulated later on so the PC keyboard can be used on text fields.

## What about OS 5?

I am planning on adding Tungsten T3 support as soon as possible.

## Credits
[Firebird Emu](https://github.com/nspire-emus/firebird) (ARMv5TE Core)  
[uARM](https://dmitry.gr/?r=05.Projects&proj=07.%20Linux%20on%208bit) (PXA260 CPU Peripherals and reference CPU core)  
[Musashi v3.4](https://github.com/kstenerud/Musashi) (last version that builds outside of MAME)(68k Core)  
[blip_buf 1.1.0](https://github.com/TASVideos/BizHawk/tree/master/blip_buf) (Audio Resampler)  
https://www.iconarchive.com/show/crystal-clear-icons-by-everaldo/App-palm-icon.html (Desktop Icon)  
https://tango.freedesktop.org/Tango_Icon_Library (Palm Action Buttons, All UI buttons)  
https://www.iconfinder.com/icons/2317746/chip_computer_cpu_device_frequency_microchip_processor_icon (hwTestSuite Icon)  
https://www.flaticon.com/free-icon/cow_235371#term=cow&page=1&position=13 (muExpDriver Icon)  
https://findicons.com/icon/164302/cursor (Libretro Port Joystick Cursor)

## Building

#### Using CMake

Using CMake, you just need to do:

 * `cmake .`
 * `cmake --build .`
   * You may specify a CMake target.

#### For RetroArch

Make sure you have done all the steps here https://docs.libretro.com/ under "For Developers/Compilation" so you build environment works.  

    cd ./libretroBuildSystem
    make

#### For Qt

First install _Qt 5.14.2_, you may optional install as well _Qt Creator_.

 * Windows: <https://download.qt.io/archive/qt/5.14/5.14.2/qt-opensource-windows-x86-5.14.2.exe>
 * Mac: <https://download.qt.io/archive/qt/5.14/5.14.2/qt-opensource-mac-x64-5.14.2.dmg>
 * Linux: <https://download.qt.io/archive/qt/5.14/5.14.2/qt-opensource-linux-x64-5.14.2.run>

When running _CMake_ you will need to pass `-DCMAKE_PREFIX_PATH` to the
location of `Qt5Config.cmake`.

 * With _Qt 5.14.2_ on Windows building with...
   * mingw-w64: `C:\qt\Qt5.14.2\5.14.2\mingw73_64\lib\cmake\Qt5`
   * Visual Studio: `C:\qt\Qt5.14.2\5.14.2\msvc2017_64\lib\cmake\Qt5`

If you are using CLion, you may need to go into _Settings_ ->
_Build, Execution, Deployment_ -> _CMake_ and add it to _CMake Options_.

For Qt Creator, open the `.pro` file and click "Run" or build from
command line.

If you get `error: 'thread' in namespace 'std' does not name a type` while
trying to build the Qt Project then you should install the _POSIX Threaded_
variant of Mingw-w64 and not the _Win32 Threaded_ variant.

#### TestSuite for Palm OS
Install prc-tools from the below link(self compiled or prepackaged VM)  

    cd ./tools/palm/hwTestSuite
    ./make.sh

#### MuExpDriver for Palm OS
Install prc-tools from the below link(self compiled or prepackaged VM)  

    cd ./tools/palm/muExpansionDriver
    ./make.sh

## Running
#### Files
palmos40-en-m500.rom: f50e4d5e4d98dc831f2c34a9107651eb (MD5)  
palmos41-en-m515.rom: 83cb1d1c76e568b916dc2e7c0bf669f6 (MD5)  
palmos52-en-t3.rom: de46ec84d9aabf655eabdf9b00a3845d (MD5)   
bootloader-dbvz.rom: 9da101cd2317830649a31f8fa46debec (MD5)  

#### For Qt
 1. Run once to create the directory tree
 2. Copy "palmos41-en-m515.rom" and "palmos52-en-t3.rom" to "~/Mu"
 3. (Optional)Copy "bootloader-en-m515.rom" to "~/Mu"
 4. Run emu and press start button

#### For RetroArch
 1. Download "Palm OS(Mu)" from "Online Updater->Core Updater"
 2. Go back, select "Load Core", select "Palm OS(Mu)"
 3. Copy "palmos41-en-m515.rom" and "palmos52-en-t3.rom" to the RetroArch system directory
 4. (Optional)Copy "bootloader-en-m515.rom" to the RetroArch system directory
 5. Run a .prc or .img file

## Tools
[Prc-tools, Palm OS SDKs, pilrc, pilot-link](https://github.com/meepingsnesroms/prc-tools-remix)

## License

 * `CC BY-NC 3.0 US`
   * Attribution is to:
     * Emily "meepingsnesroms"
     * Stephanie Gawroriski <xerthesquirrel@gmail.com>

<a rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/us/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/3.0/us/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/us/">Creative Commons Attribution-NonCommercial 3.0 United States License</a>.

## Links
[Website](https://meepingsnesroms.github.io/)  
[Discord](https://discord.gg/hWSz8VN)

## Also see Mu's sister project
[🐿SquirrelJME](https://multiphasicapps.net)
