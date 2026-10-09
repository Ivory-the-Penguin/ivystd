# The Ivy Standard Library

The `ivystd` is a collection of headers (some stb-style, others header only) that are meant as useful utilities. The _original_ target is gamedev, but it can support other fields.

## Why?

I wanted to create this because I was sort of annoyed at bringing in dependencies on any games I worked on, and it feel's really un-pretty to me. To me this is meant like a unified library and feels nice to use but not sacrificing performance either.

## Progress

Currently there are **11** modules. Some modules use others, so it's not just a collection of standalone headers, they use each other. An ecosystem in other words.

The documentation for some of these modules is right inside the header. But for the others the documentation has not yet been written.

The `ivystd`, atleast for now, only support single threaded, and Unix. I might add support for Windows and multi-threaded programs

### Some planned modules:

- `ivy_os.h` (handles Unix calls)
- `ivy_filesystem.h` (handles file operations)
- `ivy_build.h` (similar to Tsoding's `nob.h`)
- `ivy_ini.h` (ini serialization)
- `ivy_obj.h` (obj serialization)
- `ivy_json.h` (json serialization)
- `ivy_tiled.h` (support for instantly loading Tiled maps)

## Credits

It's completely implemented by me. No AI was used at all in implementation!

I did give out credit to the people I was inspired by, and some code I copied:

- Zig's allocators
- C/C++'s Handmade Math
- C++'s `{fmt}`
- Tsoding's (Alexey Kutepov) sv (initial implementation was copied from him)
- rxi's `vec` and `map` (I took inspiration from the idea, but implementation is my own)
