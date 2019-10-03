#!/bin/bash

ScriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ProjectDir="$( cd "$( dirname $ScriptDir )" >/dev/null 2>&1 && pwd )"
BuildDir="$ProjectDir/build"

function checkForToolChain {
    if ! hash meson 2>/dev/null; then
        echo "meson is required, but it's not installed.  Aborting."
        exit 1
    fi

    if ! hash ninja 2>/dev/null; then
        echo "ninja is required, but it's not installed.  Aborting."
        exit 1
    fi
}

checkForToolChain

if [ ! -d $BuildDir ]; then
    if ! meson $BuildDir $ProjectDir; then
        echo "meson was not successfull"
        exit 1
    fi
fi

if ! ninja -C $BuildDir; then
    echo "ninja was not successfull"
    exit 1
fi
