### Building PhysicsFS

When building PhysicsFS, you have to disable unused archivers. This makes the
file size smaller and fixes a heap of Windows compilation issues.

```bash
cmake -DPHYSFS_ARCHIVE_ISO9660=0 -DPHYSFS_ARCHIVE_7Z=0 -DPHYSFS_ARCHIVE_GRP=0 -DPHYSFS_ARCHIVE_WAD=0 -DPHYSFS_ARCHIVE_HOG=0 -DPHYSFS_ARCHIVE_MVL=0 -DPHYSFS_ARCHIVE_QPAK=0 -DPHYSFS_ARCHIVE_SLB=0 -DPHYSFS_HAVE_CDROM_SUPPORT=0 -DPHYSFS_SUPPORTS_GRP=1 -DPHYSFS_BUILD_SHARED=1 -DPHYSFS_BUILD_TEST=0 ..
```

### Building GLFW

Question: Why do we need shared libs again?

cmake -DBUILD_SHARED_LIBS=ON -G Xcode ..

When the application binary runs, it's going to try and find the location of
the libglfw lib. This location is stored within the lib itself. You can check
the location it uses with `otool -L`. You'll notice that if you've just
compiled it, it will be an absolute location pointing to somewhere on your
computer. We need to change it so its relative to the OSX bundle. We can do it
via the steps below:

```bash
otool -L libglfw.3.0.dylib # to check its location
install_name_tool -id @executable_path/../Frameworks/libglfw.3.0.dylib libglfw.3.0.dylib # to change its location
```

### Building libpng

```bash
cp ./scripts/makefile.darwin makefile
make ARCH="-arch i386 -arch x86_64" # it includes ppc for some silly reason
sudo make install
make clean
```

### Using Boost

Yeah, I use boost. Come at me bro. We use `boost::format` because its easy and fast.

```bash
brew install boost boost-bcp # bcp allows us to extract only small parts of the boost framework
cd engine/extlibs/headers
rm -rf boost
bcp --boost=/usr/local/include format.hpp .
```

### Logging

See: https://github.com/elanthis/easylogger

### Flat Header Map

Build Settings -> Editior Menu -> Add Build Setting -> Add User Defined Settings

```
USE_HEADERMAP = NO
```

This allows us to `#include "engine/logger.hpp"`. By default, Xcode ignores the directory
structure of the header files, and just lets you do whatever you like. `#include "logger"` for
example. Problem with that though, is that if you have headers of the same name, you're kinda
screwed. I also prefer to use the correct namespaces.
