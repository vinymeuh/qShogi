# qShogi - Build instructions

qShogi build requires Qt 6.2 or greater with Qt 6 SVG module, a compiler with C++17 support and ```cmake``` 3.21 or greater.

Run following commands to do a Release build:

```
$ cd qShogi
$ mkdir build
$ cmake -DCMAKE_PREFIX_PATH="<QT_DIR>" -DCMAKE_BUILD_TYPE=Release ..
$ make
$ src/qShogi/qShogi
```

For a Debug build with shogi library testing enabled:

```
$ cd qShogi
$ mkdir build
$ cmake -DCMAKE_PREFIX_PATH="<QT_DIR>" -DCMAKE_BUILD_TYPE=Debug -DQSHOGI_LIBSHOGI_TESTING=ON ..
$ make shogiTesting
$ test/shogiTesting
```

And for code coverage:

```
$ cd qShogi
$ mkdir build
$ cmake -DCMAKE_PREFIX_PATH="<QT_DIR>" -DCMAKE_BUILD_TYPE=Debug -DQSHOGI_LIBSHOGI_TESTING=ON -DQSHOGI_LIBSHOGI_COVERAGE=ON ..
$ make shogiCoverage
$ firefox ./shogiCoverage/index.html
```
