#!/bin/bash
test -d xcode && rm -rf xcode
mkdir xcode
cd xcode
cmake -G "Xcode" ..
cd ..
