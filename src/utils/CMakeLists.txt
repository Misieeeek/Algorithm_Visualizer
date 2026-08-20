add_library(utils_lib STATIC)

target_sources(utils_lib PUBLIC FILE_SET CXX_MODULES FILES utils.cppm)
