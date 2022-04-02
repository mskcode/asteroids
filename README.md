# Asteroids clone

## Development

### Cloning repository

    git clone --recurse-submodules https://github.com/mskcode/asteroids.git

### Building binaries

    mkdir -p build/debug
    cd build/debug
    cmake ../.. -DCMAKE_BUILD_TYPE=Debug
    make

After the build completes (`make` in this case), the application executable
proper (`asteroids`) and unit test executable (`asteroids_test`) can be found
from `./bin` directory.
