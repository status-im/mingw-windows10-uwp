# mingw-windows10-uwp

### Windows 10 Store ready sample of MinGW dll with C exported methods PInvoked from Windows 10 UWP application

- UWP appx bundle with MinGW dll passing Windows 10 Store Certification Kit checks
- Tested for x64 only
- Tested with MinGW-w64 64 bit compiler installed with [MSYS2 toolchain][1]
- Sample based on [implementation][2] of WinRT support for libVLC

Environment requirements:

- `Visual Studio 2017` with `UWP development tools` and `"C++ Universal Windows Platform development tools"` 
package installed
- `x86_64 MSYS2` installation with configured `pacman` packager. Latest MinGW-w64 compiler build obtained 
with `pacman` packager by running following command in MSYS2 terminal:
```
   pacman -S mingw-w64-x86_64-toolchain
```
- MinGW-w64 `winstorecompat` library to redefine some forbidden API calls for UWP platform. 
`winstorecompat` library is available in latest builds of MinGW-w64 and can be obtained along
with x86_64-toolchain MSYS2 MinGW toolchain as described above.

Build steps:

- To build DLL launch MSYS2 MinGW-w64 64 bit compiler command line.
- cd to `MinGWDLL` directory
- Run [`build.sh`][3] script to build MinGW dll. In background script does following things:
  - Creates custom `gcc` specfile to link `winstorecompat` library before linking to
  system libraries. Replaces linking with `msvcrt` (Desktop Microsoft C runtime) with linking to
  `msvcr120_app` (Visual Studio 2013 UWP platform C runtime). `msvcr120_app` is bundled along 
  with installation of MinGW-w64 compiler.
  - Asks `gcc` to build shared `PureMinGWDLL.dll` library with custom flag `-Wl,--dynamicbase` 
  to pass Windows 10 Store Certification Kit security checks.
  - Runs `appcontainer.pl` script to modify `PE header` of `PureMinGWDLL.dll` binary. It sets
  `appcontainer` bit flag to be compatible with Windows 10 Store binary requriements.
- `InvokeMinGWDllUWP` directory contains Visual Studio 2017 UWP project to PInvoke `PureMinGWDLL.dll` 
shared library and display obtained values on screen. To build just launch `InvokeMinGWDllUWP.sln` 
with Visual Studio 2017 and run the Build. UWP solution references
`Microsoft Visual C++ 2013 Runtime Package for Windows Universal` to be bundled into appx package.


[1]: http://www.msys2.org/
[2]: https://code.videolan.org/videolan/vlc-winrt/blob/master/libvlc/compile.sh
[3]: https://github.com/status-im/mingw-windows10-uwp/blob/master/MinGWDLL/build.sh