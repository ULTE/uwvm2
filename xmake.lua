set_xmakever("2.9.0")

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
	set_warnings("all", "extra", "error")

	local enable_cxx_module = get_config("use-cxx-module")
	if enable_cxx_module then
		add_defines("UWVM_MODULE")
		set_policy("build.c++.modules", true)
		set_policy("build.c++.modules.std", true)
	end 

	local disable_cpp_exceptions = get_config("fno-exceptions")
	if disable_cpp_exceptions then
		set_exceptions("no-cxx")
	end

    local enable_debug_timer = get_config("debug-timer")
	if enable_debug_timer then
		add_defines("UWVM_TIMER")
	end

    local enable_int = get_config("enable-int")
	if not enable_int or enable_int == "none" then
		add_defines("UWVM_DISABLE_INT")
	elseif enable_int == "default" then
		add_defines("UWVM_USE_DEFAULT_INT")
	elseif enable_int == "uwvm-int" then
		add_defines("UWVM_USE_UWVM_INT")
	end

    local enable_jit = get_config("enable-jit")
	if not enable_jit or enable_jit == "none" then
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
	local enable_cxx_module = get_config("use-cxx-module")

	-- third-parties/fast_io
	add_includedirs("third-parties/fast_io/include")
	
	if enable_cxx_module then
		add_files("third-parties/fast_io/share/fast_io/fast_io.cppm", {public = is_debug_mode})
		add_files("third-parties/fast_io/share/fast_io/fast_io_crypto.cppm", {public = is_debug_mode})
	end 

	-- src
	add_includedirs("src/")

	if enable_cxx_module then
		-- utils
		add_files("src/utils/**.cppm", {public = is_debug_mode})

		-- wasm parser
		add_files("src/parser/wasm/**.cppm", {public = is_debug_mode})

		-- uwvm
		add_files("src/uwvm/**.cppm", {public = is_debug_mode})
	end 

	-- uwvm cmd callback
	add_files("src/uwvm/cmdline/params/**.cpp")

	-- uwvm main
	add_files("src/uwvm/main.cpp")

target_end()

-- test unit
for _, file in ipairs(os.files("test/non-platform-specific/**.cc")) do
    local name = path.basename(file)
    target(name)
        set_kind("binary")
		def_build()
        set_default(false)
			
		local enable_cxx_module = get_config("use-cxx-module")

		-- third-parties/fast_io
		add_includedirs("third-parties/fast_io/include")

		if enable_cxx_module then
			add_files("third-parties/fast_io/share/fast_io/fast_io.cppm", {public = is_debug_mode})
			add_files("third-parties/fast_io/share/fast_io/fast_io_crypto.cppm", {public = is_debug_mode})
		end

		-- src
		add_includedirs("src/")

		if enable_cxx_module then
			-- utils
			add_files("src/utils/**.cppm", {public = is_debug_mode})

			-- wasm parser
			add_files("src/parser/wasm/**.cppm", {public = is_debug_mode})

			-- uwvm
			add_files("src/uwvm/**.cppm", {public = is_debug_mode})
		end 

		-- uwvm cmd callback
		add_files("src/uwvm/cmdline/params/**.cpp")

        add_files(file)

        add_tests("default")

		set_warnings("all", "extra", "error")
	target_end()
end
