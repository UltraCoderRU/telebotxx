add_library(rapidjson INTERFACE IMPORTED GLOBAL)
target_include_directories(rapidjson INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)
