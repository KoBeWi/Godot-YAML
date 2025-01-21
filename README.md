# <img src="Media/Icon.png" width="64" height="64"> Godot YAML

GDExtension for Godot engine that parses YAML files. It uses [Rapid YAML](https://github.com/biojppm/rapidyaml) library.

## Installation

Download a release and extract it into your project directory. If you built from source, copy the contents into `addons/YAML`. The editor will automatically detect the extension and enable it and you will be able to use it right away.

## Usage

The extension comes with a YAML class that provides 2 static methods: `parse_string()` and `parse_file()`. The latter is the same as the former, except it loads a file as text and then parses the content.

The class works similarly to built-in JSON class. `parse_string()` will return a Variant, which is the result of parsing.

```GDScript
var string = """
- 1
- 2
- 3
"""
print(YAML.parse_string(string)) # Prints "[1, 2, 3]".
```

The extension is able to load Godot's native types, like Vector2. However, since YAML does not support Godot type syntax, you need to enclose them in quotes.

```GDScript
var string = """
"Vector2i(0, 0)": Epicenter
"Vector2i(1, 0)": Eastern Corridor
"""
var data = YAML.parse_string(string) # Returns a Dictionary with Vector2i keys.
```

If a string fails to parse, the result will be `null`. If `parse_file()` fails to open the file, it will also return `null`.

## Limitations

- Only parsing is supported, no writing.
- The extension has no error handling like JSON class. Errors are simply printed to output.
- [Limitations of Rapid YAML](https://github.com/biojppm/rapidyaml?tab=readme-ov-file#known-limitations) apply.

___
You can find all my addons on my [profile page](https://github.com/KoBeWi).

<a href='https://ko-fi.com/W7W7AD4W4' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://cdn.ko-fi.com/cdn/kofi1.png?v=3' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>
