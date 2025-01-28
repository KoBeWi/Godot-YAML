#!/usr/bin/env python

# This file is for building as a Godot GDExtension.

env = SConscript("src/godot-cpp/SConstruct")

# Add source files.
env.Append(CPPPATH=["./,src/"])
sources = Glob("*.cpp") + Glob("src/*.cpp")

env.Append(CPPDEFINES=["GDEXTENSION"])

bin_path = "bin/"
extension_name = "YAML"
debug_or_release = "release" if env["target"] == "template_release" else "debug"

env.Append(CCFLAGS=["-fexceptions"])

if not "arch_suffix" in env:
    env["arch_suffix"] = env["arch"]

if env["target"] == "editor":
    env.Append(CPPPATH=["src/editor/"])
    sources += Glob("src/editor/*.cpp")

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# Create the library target (e.g. libYAML.linux.debug.x86_64.so).
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{0}/lib{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            bin_path,
            extension_name,
            env["platform"],
            debug_or_release,
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/lib{}.{}.{}.{}{}".format(
            bin_path,
            extension_name,
            env["platform"],
            debug_or_release,
            env["arch_suffix"],
            env["SHLIBSUFFIX"],
        ),
        source=sources,
    )

Default(library)
