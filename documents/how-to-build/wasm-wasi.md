# WASM-WASI

## Use LLVM
1. Install [[xmake]](https://github.com/xmake-io/xmake/)
2. Install [[llvm]](https://github.com/llvm/llvm-project/releases)
3. Build
```shell
$ xmake f -p [wasm-wasip1|wasm-wasip2|wasm-wasip1-threads|wasm-wasip2-threads] -a [wasm32|wasm64] --sysroot=$HOME/sysroot/wasm-sysroots/wasm-sysroot/wasm32-wasip1 --links=unwind
$ xmake
```
4. Install UWVM2
```shell
$ xmake i -o <install_path>
```

### Additional Options
1. `--use-cxx-module=y` Use cpp module to compile, compiler may not be supported