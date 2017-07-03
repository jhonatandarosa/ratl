#!/bin/bash
DIR=ratl-0.0.1
ZIP_NAME=$DIR.zip
rm $ZIP_NAME
mkdir $DIR
cp -R CMakeModules $DIR/
cp -R src $DIR/
cp -R server-impls $DIR/
cp -R examples $DIR/
cp CMakeLists.txt $DIR/
zip -r $ZIP_NAME $DIR
rm -rf $DIR