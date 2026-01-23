# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS components/esp-idf-lib/components/dht components/esp-idf-lib/components/esp_idf_lib_helpers)
idf_build_set_property(MINIMAL_BUILD ON)
project(show-dht11)
