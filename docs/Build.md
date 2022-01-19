# Build instructions

## qShogi

qShogi build requires Qt 6.2 or greater with Qt 6 SVG module, a compiler with C++17 support and ```cmake``` 3.21 or greater.

Run following commands to do a Release build:

```
$ cd qShogi
$ mkdir build && cd build
$ cmake -DCMAKE_PREFIX_PATH="${QT_DIR}" -DCMAKE_BUILD_TYPE=Release ..
$ make
$ src/qShogi
```

## libshogi

Libshogi is a pure C++ library with not Qt dependencies.

Build it alone is not very useful but we can run tests with **shogiTesting** target.

```
$ cd qShogi
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DLIBSHOGI_TESTING=ON ..
$ make shogiTesting
$ libshogi/tests/shogiTesting
```

Code coverage report is generated with GCOVR.

```
$ cd qShogi
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DLIBSHOGI_TESTING=ON -DLIBSHOGI_COVERAGE=ON ..
$ make shogiCoverage
$ firefox ./shogiCoverage/index.html
```
