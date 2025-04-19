function wasm_wasi_target()
    set_toolchains("clang")
    add_ldflags("-fuse-ld=lld", {force = true})
    --- @todo TODO
end