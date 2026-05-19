paraview_add_plugin(sz3reader
  REQUIRED_ON_CLIENT
  REQUIRED_ON_SERVER
  VERSION "1.0"
  MODULES sz3reader::vtkSZ3Reader
  MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../Reader/vtk.module")
