#include "register_types.h"

#include <godot_cpp/classes/engine.hpp>

#include "yaml.h"

void initialize_YAML_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		GDREGISTER_CLASS(YAML);
	}
}

void uninitialize_YAML_module(ModuleInitializationLevel p_level) {
}
