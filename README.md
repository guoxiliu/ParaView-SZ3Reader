# SZ3Reader Plugin

ParaView/VTK reader for direct visualization of data files compressed using the SZ3 compressor.

Version: 1.0

## Features

- Read `.sz3` compressed files directly in ParaView
- Multi-version SZ3 support with dynamic plugin loading
- Automatic version detection from compressed file header
- Supports both single (float32) and double (float64) precision
- Automatically fetches and builds SZ3 dependencies

## Supported SZ3 Versions

- 3.0.x
- 3.1.x
- 3.2.0, 3.2.1
- 3.3.0, 3.3.2

## Build Instructions

### Prerequisites

- CMake 3.18+
- C++17 compatible compiler
- Git

### Option 1: External Build

Build the plugin against an existing ParaView installation:

```bash
mkdir build && cd build
cmake .. -DParaView_DIR=/path/to/paraview/lib/cmake/paraview-6.x
cmake --build .
cmake --install . --prefix /path/to/install
```

### Option 2: Build with ParaView Superbuild

```bash
cd /path/to/paraview-superbuild
mkdir build && cd build
cmake .. -DENABLE_sz3reader=ON
cmake --build .
```

#### Superbuild CMake Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `ENABLE_sz3reader` | OFF | Enable building the sz3reader plugin |
| `sz3reader_SOURCE_SELECTION` | git | Source selection: `git` or `source` |
| `sz3reader_GIT_REPOSITORY` | https://github.com/guoxiliu/ParaView-SZ3Reader.git | Git repository URL |
| `sz3reader_GIT_TAG` | origin/main | Git tag, branch, or commit |
| `sz3reader_SOURCE_DIR` | - | Local source directory (when `SOURCE_SELECTION=source`) |

## Usage in ParaView

1. Launch ParaView
2. Tools → Manage Plugins → Load SZ3Reader (for external build, load `<install_dir>/lib/paraview-6.x/plugins/SZ3Reader/SZ3Reader.so`)
3. File → Open → Select a `.sz3` file
4. Set the domain dimensions (X, Y, Z). Set remaining dimensions to 1 if the data is less than 3D.
5. Check "Double Precision" if the data was compressed as float64
6. Click Apply

## Architecture

The plugin uses dynamic plugin loading (dlopen) to support multiple SZ3 versions:

- **SZ3Compat dispatcher**: Detects version from compressed file header and loads the appropriate plugin
- **Version plugins**: Separate shared libraries for each SZ3 version (libsz3_v302.so, libsz3_v317.so, etc.)
- **Automatic version detection**: Files compressed with SZ3 v3.2.0+ contain version info in header; older versions are detected by analyzing the data structure

## References

- SZ3 Compressor: https://szcompressor.org/ | https://github.com/szcompressor/SZ3
- ParaView: https://www.paraview.org/

## Contact

Please report bugs and suggestions in the Issues section.
