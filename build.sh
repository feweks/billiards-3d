if [ ! -d "build" ]; then
    echo "Configuring the project"
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    cd ..
fi

echo "Building the project..."
cmake --build build

if [ $? -eq 0 ]; then
    echo "Build was succesfull, running..."
    cd "bin"
    ./billiards
else
    echo "Build failed. See error(s) above"
fi
