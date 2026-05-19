# Build SZ3Compat (multi-version SZ3 decompression with dynamic plugins)
add_subdirectory(SZ3Compat)

set(classes
  vtkSZ3Reader)

vtk_module_add_module(sz3reader::vtkSZ3Reader
  CLASSES ${classes})

vtk_module_link(sz3reader::vtkSZ3Reader
  PRIVATE
    SZ3Compat
    ${CMAKE_DL_LIBS})

vtk_module_include(sz3reader::vtkSZ3Reader
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SZ3Compat/include)

paraview_add_server_manager_xmls(
  XMLS
    sz3reader.xml)
