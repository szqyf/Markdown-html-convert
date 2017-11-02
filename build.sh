if [ ! -d build-sh ]; then
mkdir build-sh
fi
cd build-sh
cmake .. -DCMAKE_BUILD_TYPE=${1:-Debug}
make
