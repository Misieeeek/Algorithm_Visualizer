add_library(common_lib STATIC)

target_sources(common_lib
    PUBLIC
        FILE_SET CXX_MODULES FILES
            math.cppm
)

