cmake_minimum_required(VERSION 3.13)
project(BoneSegmentation)

# -----------------------------------------------------------------------------
# Handle VTK dependencyma
# -----------------------------------------------------------------------------
set(VTK_DIR "VTK_DIR_PATH")

find_package(VTK
COMPONENTS
    FiltersSources      # VTK pipeline
    InteractionStyle    # Mouse handling
    InteractionWidgets
    # RenderingOpenGL2    # For Rendering
    RenderingUI         # For SDL2 Window
    CommonCore
    CommonColor
    CommonDataModel
    CommonComputationalGeometry
    IOImage
    FiltersCore
    FiltersModeling
    FiltersExtraction
    FiltersGeometry
    InteractionImage
    InteractionStyle
    RenderingVolume
    RenderingCore
    RenderingVolume
    # RenderingVolumeOpenGL2
    )


if (NOT VTK_FOUND)
  message(FATAL_ERROR "ReadDICOMSeries: Unable to find the VTK build folder.")
endif()

add_executable(CoreModule "BoneSegmentation.cxx" "StatusMessage.h" "IpwMprWidget.h" "MprImageViewer.h" "ImageViewerInteractorStyle.h" "MeshRenderer.h" "CellPickingInteractorStyle.h" "testInteractor.h" "vtkResliceCursorCallback.h")
target_link_libraries(CoreModule PRIVATE ${VTK_LIBRARIES})


# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS CoreModule
  MODULES ${VTK_LIBRARIES}
)