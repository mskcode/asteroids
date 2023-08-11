# Asteroids clone

## Development

### Cloning repository

```shell
git clone --recurse-submodules https://github.com/mskcode/asteroids.git
```

### Building binaries

The fast way to test if project builds and runs is to run `build-and-run.sh`
with or without optional `--clean` parameter.

```shell
./build-and-run.sh
```

You can also do you by running CMake manually and go from there.

```shell
mkdir -p build/debug
cd build/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug -G "Ninja"
ninja
```

After the build completes (`ninja` in this case), the application executable
proper (`game`) and unit test executable (`asteroids_test`) can be found
from `./bin` directory.

### Adding Git submodules

```shell
cd submodules
git submodule add <repository_url>
```

Add the newly added submodule to `CMakeLists.txt` file in this root directory.

## TODO

* [ ] Some kind of logging setup would be nice.
