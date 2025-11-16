# C++ Conversion for HAMOOPIG

This document describes the conversion of the HAMOOPIG engine from C to C++ with classes.

## Changes Made

### 1. File Renaming
- `src/main.c` → `src/main.cpp`

### 2. Class Conversion

The original C structures have been converted to C++ classes:

#### Fireball Class
```cpp
class Fireball {
public:
    Sprite* spriteFBall;
    s8 direcao;
    u8 speedX;
    bool active;
    // ... other members
};
```

Previously: `typedef struct { ... } FireballDEF;`

#### Player Class
```cpp
class Player {
public:
    Sprite* sprite;
    Sprite* sombra;
    Fireball fball;
    u16 bufferSpecial;
    // ... other members
};
```

Previously: `struct PlayerDEF { ... };`

#### GraphicElement Class
```cpp
class GraphicElement {
public:
    Sprite* sprite;
};
```

Previously: `struct GraphicElementDEF { ... };`

### 3. C++ Header Wrapping

C library headers are now wrapped in `extern "C"` blocks:

```cpp
extern "C" {
#include <genesis.h>
}
```

This ensures proper C linkage when compiling with g++.

### 4. Build System

#### Using the C++ Build Script

A custom build script `build_cpp.sh` has been created to compile C++ files:

```bash
./build_cpp.sh
```

This script:
- Compiles `.cpp` files with `m68k-elf-g++`
- Uses appropriate C++ flags (`-fno-exceptions`, `-fno-rtti`)
- Maintains compatibility with SGDK

#### Building with make

The regular make command can be used after resources are set up:

```bash
make compile
```

### 5. Key C++ Features Used

- **Classes**: Instead of `typedef struct`, we use proper C++ classes
- **Public members**: All members are public to maintain C-style direct access
- **No constructors/destructors**: Keeping simple POD-like structures for compatibility
- **No exceptions/RTTI**: Disabled for embedded system compatibility

## Benefits of C++ Conversion

1. **Better Organization**: Classes provide logical grouping of data
2. **Type Safety**: C++ provides stronger type checking
3. **Namespace Support**: Can use namespaces to avoid naming conflicts
4. **Future Extensibility**: Easy to add methods to classes later

## Compatibility Notes

- The code maintains binary compatibility with SGDK
- All SGDK C functions work as before
- Resource files (sprites, sounds, etc.) work the same way
- The Sega Genesis/Mega Drive ROM output is identical

## Building a Complete ROM

To build a complete ROM, you need:

1. Resource files in the `res/` directory
2. Run the resource compiler
3. Compile with `./build_cpp.sh` or `make compile`

## Original Code Structure

The original code used C structs:
- `FireballDEF` - typedef struct
- `PlayerDEF` - struct  
- `GraphicElementDEF` - struct

These are now proper C++ classes with the same memory layout.

## Technical Details

### Compiler
- **C++ Compiler**: `m68k-elf-g++` (GCC 13.2.0)
- **Target**: Motorola 68000 (Sega Genesis/Mega Drive)
- **Standard**: GNU++11
- **Optimizations**: `-O3` with LTO

### Disabled C++ Features
- Exceptions (`-fno-exceptions`)
- RTTI (`-fno-rtti`)
- Standard library (embedded environment)

## Future Enhancements

Possible C++ features that could be added:
- Member functions for Player/Fireball classes
- Constructors for initialization
- Operator overloading for convenience
- Templates for generic code
- Namespaces for better organization

## Credits

Original HAMOOPIG engine by GameDevBoss (Daniel Moura)
C++ conversion for modern development practices
