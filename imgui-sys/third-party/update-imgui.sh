#!/bin/bash
set -euo pipefail

SCRIPT_DIR=$(dirname ${0} | python3 -c 'import os, sys; print(os.path.abspath(sys.stdin.read().strip()))' )

cd ${SCRIPT_DIR}
./_update-imgui.sh ~/code/vendor/cimgui 1.89.9 ./imgui-master/
./_update-imgui.sh ~/code/vendor/cimgui 1.89.9dock ./imgui-docking/

./_update-imgui.sh ~/code/vendor/cimgui 1.89.9 ./imgui-master-freetype/
./_update-imgui.sh ~/code/vendor/cimgui 1.89.9dock ./imgui-docking-freetype/

pushd imgui-master/generator
luajit generator.lua gcc false -DIMGUI_USE_WCHAR32
popd

pushd imgui-docking/generator
luajit generator.lua gcc "internal" -DIMGUI_USE_WCHAR32
popd

pushd imgui-master-freetype/generator
luajit generator.lua gcc freetype -DIMGUI_USE_WCHAR32
popd

pushd imgui-docking-freetype/generator
luajit generator.lua gcc "internal,freetype" -DIMGUI_USE_WCHAR32
popd
