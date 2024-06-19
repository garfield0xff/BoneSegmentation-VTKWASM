# BoneSegmentation - VTK, WASM
<img src="https://github.com/garfield0xff/BoneSegmentation-VTKWASM/assets/170846390/45a27ac7-ec36-4352-9cfe-fbf8b87934d9">

# Project
This project is designed to perform 3D bone segmentation using DICOM format data in the coronal, sagittal, and axial dimensions. It includes features such as rotation and mesh boolean operations.

## Installation
1. VTK 8.6.0 
 - [Official Download VTK]
    (https://gitlab.kitware.com/vtk/vtk)
    
2. CLANG 3.9.0


## Build Option
1. Building using Emscripten for WebAssembly
- [Official Build Option VTK WASM]
    (https://docs.vtk.org/en/latest/advanced/build_wasm_emscripten.html)

```bash
emcmake cmake .. \
-DBUILD_SHARED_LIBS:BOOL=OFF \
-DCMAKE_BUILD_TYPE:STRING=Release \
-DVTK_ENABLE_LOGGING:BOOL=OFF \
-DVTK_ENABLE_WRAPPING:BOOL=OFF \
-DVTK_MODULE_ENABLE_VTK_hdf5:STRING=NO \
-DVTK_MODULE_ENABLE_VTK_RenderingContextOpenGL2:STRING=DONT_WANT \
-DVTK_MODULE_ENABLE_VTK_RenderingLICOpenGL2:STRING=DONT_WANT \
-DVTK_MODULE_ENABLE_VTK_RenderingCellGrid:STRING=NO \
```

2. Build File 
```bash
cd /project/directory/
mkdir build
cd build
emcmake cmake .. -DVTK_DIR="VTK_BUILD_PATH"
emcmake make
```

## Use Wasm In Ts
```bash
export const createWasmExportsByGL = (_canvas: HTMLCanvasElement | null) => {
    return {
        canvas: _canvas,
        onRuntimeInitialized: function () {
            setTimeout(() => {
                window.dispatchEvent(new Event("resize"))
            })
        }
    }
}
```