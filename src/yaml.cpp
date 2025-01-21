#include "yaml.h"

#define RYML_DEFAULT_CALLBACK_USES_EXCEPTIONS
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "rapidyaml-0.7.2.hpp"

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>

void YAML::_bind_methods() {
	ClassDB::bind_static_method("YAML", D_METHOD("parse_string", "string"), YAML::parse_string);
	ClassDB::bind_static_method("YAML", D_METHOD("parse_file", "path"), YAML::parse_file);
}

Variant get_variant(const ryml::csubstr &string) {
	const String gdstring = String::utf8(string.str, string.len);
	const Variant variant = UtilityFunctions::str_to_var(gdstring);

	if (variant == Variant() && gdstring != "null" && gdstring != "nil") {
		return gdstring;
	}
	return variant;
}

Variant godotize_element(const ryml::ConstNodeRef &element) {
	if (element.is_map()) {
		Dictionary dictionary;

		for (const ryml::ConstNodeRef &child : element.children()) {
			const Variant key = get_variant(child.key());
			Variant value = godotize_element(child);
			dictionary[key] = value;
		}
		return dictionary;
	} else if (element.is_seq()) {
		Array array;
		array.resize(element.num_children());

		int i = 0;
		for (const ryml::ConstNodeRef &child : element.children()) {
			array[i++] = godotize_element(child);
		}
		return array;
	} else if (element.is_val() || element.is_keyval()) {
		return get_variant(element.val());
	}
	return Variant();
}

Variant YAML::parse_string(const String &p_string) {
	try {
		ryml::Tree tree = ryml::parse_in_arena(p_string.utf8().get_data());
		return godotize_element(tree.rootref());
	} catch (const std::runtime_error &e) {
		print_error(e.what());
		return Variant();
	}
}

Variant YAML::parse_file(const String &p_path) {
	Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::READ);
	if (file.is_null()) {
		print_error(vformat("YAML: Failed to load file \"%s\".", p_path));
		return Variant();
	}
	return parse_string(file->get_as_text());
}
