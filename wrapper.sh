#!/bin/sh


export LD_LIBRARY_PATH=wiiuse/src/release-x86_64-redhat-linux:$LD_LIBRARY_PATH

./wiicontrol $@




