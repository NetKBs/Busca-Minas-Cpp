# CMakeLists.txt
project(busca_minas)
cmake_minimum_required(VERSION 3.0)

if(WIN32)
    include(CMakeLists-windows.txt)
elseif(UNIX) 
    include(CMakeLists-linux.txt)
endif()