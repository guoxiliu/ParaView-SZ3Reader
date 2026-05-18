# SZ3Reader ParaView Plugin
# Supports multi-version SZ3 decompression

cmake_minimum_required(VERSION 3.12...3.27)
project(SZ3ReaderPlugin)

# Standalone build: find ParaView installation
# In-tree build: ParaView is already available
if(NOT TARGET ParaView::paraview_plugins)
  find_package(ParaView REQUIRED)
endif()

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

paraview_add_plugin(SZ3Reader
  REQUIRED_ON_CLIENT
  REQUIRED_ON_SERVER
  VERSION "0.1"
  MODULES SZ3Reader::vtkSZ3Reader
  MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Reader/vtk.module")
