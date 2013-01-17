# Mandrill

This is my awesome 2D game engine.

I know I'm not supposed to be writing an engine, but a game instead, but fuck that. I'm hard core. Like Chuck Norris.

## Windows

NFI yet.
1) Download and install Visual Studio. I'm using the 2008 version, but 2010 should work as well. No idea about 2012.
2) Download and install the Direct X SDK here: http://www.microsoft.com/en-au/download/details.aspx?id=6812
3) Open Visual C++ and then go to Tools/Options
4) In the new window look for  ../Project and Solutions/VC++ Directories
5) In the right look for the combo box of "Show Directories for:"
6) In the combo box click on Include
7) In the box that's under the combo box, double click in the last spot (which is blank).
8) After click on it a "Examine" option will appear. You have to search for the instalation folder for DirectX and add the Include folder. (C:\Program Files\Microsoft DirectX SDK (June 2010)\Include)
9) After you have done the process with the Include. Repeat it but with the "Libraries" option in the dropdown, and the Library folder in DirectX.

## Mac OSX

### Compiling

```bash
brew install sdl
mkdir build
cd build
cmake ..
make
./demo
```
