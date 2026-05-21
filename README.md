# webots-controller

Unofficial Conan package for Webots controller sources.

## Options

- `no_plugins` (default: `True`): disables runtime plugin loading paths (`dlopen` / `LoadLibrary`) by compiling stub implementations for robot window and remote control plugin entry points.

By default, headers are read from `./include/controller/c` and stb from `./src/stb`, matching this repo layout.

## Example

```bash
git submodule update --init --recursive 
conan create . \
  -o webots-controller/*:no_plugins=True
```
