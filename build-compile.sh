#!/bin/bash
set -e

echo "=== Build Script ==="
echo "Select build type:"
echo "  1) Debug"
echo "  2) Release"
echo "  3) Both"
read -p "[1/2/3]: " choice

build_type() {
    local type=$1
    echo ""
    echo ">>> Installing dependencies ($type)..."
    conan install . --build=missing -s build_type=$type

    echo ">>> Configuration ($type)..."
    cmake --preset conan-$(echo $type | tr '[:upper:]' '[:lower:]')

    echo ">>> Building ($type)..."
    cmake --build --preset conan-$(echo $type | tr '[:upper:]' '[:lower:]')

    echo ">>> $type ready!"
}

case $choice in
1) build_type "Debug" ;;
2) build_type "Release" ;;
3)
    build_type "Debug"
    build_type "Release"
    ;;
*)
    echo "Error. Select 1, 2 or 3."
    exit 1
    ;;
esac

echo ""
echo "=== Done! ==="
