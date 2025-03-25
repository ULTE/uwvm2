set_xmakever("2.8.2")

set_project("uwvm")

-- Version
set_version("2.0.0")
add_defines("UWVM_VERSION_X=2")
add_defines("UWVM_VERSION_Y=0")
add_defines("UWVM_VERSION_Z=0")
add_defines("UWVM_VERSION_S=0")

set_allowedplats("windows", "mingw", "linux", "djgpp", "unix", "bsd", "freebsd", "dragonflybsd", "netbsd", "openbsd", "macosx", "iphoneos", "watchos", "wasm-wasi", "serenity", "sun", "cross")

includes("xmake/impl.lua")
includes("xmake/platform/impl.lua")

set_defaultmode("releasedbg")
set_allowedmodes(support_rules_table)

function def_build()

	if is_mode("debug") then
		add_rules("debug")
	elseif is_mode("release") then
		add_rules("release")
	elseif is_mode("minsizerel") then
		add_rules("minsizerel")
	elseif is_mode("releasedbg") then
		add_rules("releasedbg")
	end

    set_languages("c23", "cxx26")

	set_encodings("utf-8")
	set_warnings("all")

	set_policy("build.c++.modules", true)
	set_policy("build.c++.modules.std", true)

	local disable_cpp_exceptions = get_config("fno-exceptions")
	if disable_cpp_exceptions then
		set_exceptions("no-cxx")
	end

    local enable_debug_timer = get_config("debug-timer")
	if enable_debug_timer then
		add_defines("UWVM_TIMER")
	end

    local enable_int = get_config("enable-int")
	if enable_int == "no" then
		add_defines("UWVM_DISABLE_INT")
	elseif enable_int == "default" then
		add_defines("UWVM_USE_DEFAULT_INT")
	elseif enable_int == "uwvm-int" then
		add_defines("UWVM_USE_UWVM_INT")
	end

    local enable_jit = get_config("enable-jit")
	if enable_jit == "no" then
		add_defines("UWVM_DISABLE_JIT")
	elseif enable_jit == "default" then
		add_defines("UWVM_USE_DEFAULT_JIT")
	elseif enable_jit == "llvm" then
		add_defines("UWVM_USE_LLVM_JIT")
	end

    if is_plat("windows") then
        windows_target()
    elseif is_plat("mingw") then
        mingw_target()
	elseif is_plat("linux") then
        linux_target()
	elseif is_plat("macosx", "iphoneos", "watchos") then
        darwin_target()
	elseif is_plat("djgpp") then
        djgpp_target()
	elseif is_plat("unix", "bsd", "freebsd", "dragonflybsd", "netbsd", "openbsd") then
        bsd_target()
    end
end

target("uwvm")
	set_kind("binary")
	def_build()

	local is_debug_mode = is_mode("debug") -- public all modules in debug mode

	-- third-parties/fast_io
	add_includedirs("third-parties/fast_io/include")
	add_files("third-parties/fast_io/share/fast_io/fast_io.cppm", {public = is_debug_mode})

	-- src
	add_includedirs("src/")

	-- utils
	add_files("src/utils/**.cppm", {public = is_debug_mode})

	-- uwvm
	add_files("src/uwvm/**.cppm", {public = is_debug_mode})

	-- uwvm main
	add_files("src/uwvm/main.cc")

target_end()
