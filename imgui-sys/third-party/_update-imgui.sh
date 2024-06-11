#!/bin/bash
set -euo pipefail

SCRIPT_DIR=$(dirname ${0} | python3 -c 'import os, sys; print(os.path.abspath(sys.stdin.read().strip()))' )
CIMGUI_DIR=${1:?}
COMMITISH=${2:?}
OUT_DIR=${3:?}

OUT_DIR=$(readlink -f "${OUT_DIR}")

# Make checkout

pushd "${CIMGUI_DIR}" > /dev/null

# Sanity check the supplied imgui path
git rev-parse HEAD
ls imgui/imgui.h

# Get files from specified rev
pwd
mkdir -p "${OUT_DIR}"
git checkout "${COMMITISH}"
git submodule update --init
git ls-files --recurse-submodules | tar caf - -T- | tar xC "${OUT_DIR}"

popd > /dev/null
