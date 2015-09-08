#! /bin/bash

cd src

echo
echo "==============================================="
echo "                 Making project"
echo "==============================================="
echo
for file in *.c
do
  echo " >>> gcc src/$file -I/usr/local/include"
  echo "       -I/opt/X11/include -L/usr/local/lib" 
  echo "       -I/opt/X11/lib -w -framework OpenGL"
  echo "       -lglfw3 -lglew -o src/main"
done
for file in lib/*.c
do
  echo " >>> gcc src/$file -I/usr/local/include"
  echo "       -I/opt/X11/include -L/usr/local/lib" 
  echo "       -I/opt/X11/lib -w -framework OpenGL"
  echo "       -lglfw3 -lglew -o src/main"
done

make

echo

echo "==============================================="
echo "                 Running project"
echo "==============================================="
echo
echo " >>> ./src/main"
echo "     Program running..."
./main
echo "     Key pressed: exiting..."

echo

echo "==============================================="
echo "                 Cleaning files"
echo "==============================================="
echo
echo " >>> rm src/main"
rm main

echo

echo "==============================================="
echo "                  Exiting now"
echo "==============================================="

echo
cd ..
