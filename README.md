# Asteroids clone

## Development

### Cloning repository

```shell
git clone --recurse-submodules https://github.com/mskcode/game.git
```

### Building binaries

```shell
mkdir -p build/debug
cd build/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug -G "Ninja"
ninja
```

After the build completes (`ninja` in this case), the application executable
proper (`game`) and unit test executable (`asteroids_test`) can be found
from `./bin` directory.

## TODO

* [ ] Some kind of logging setup would be nice.
