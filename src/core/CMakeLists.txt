add_library(core_lib STATIC)

target_sources(core_lib
    PRIVATE
        appImp.cpp 
        stateManagerImp.cpp
        stateImp.cpp
    PUBLIC
        FILE_SET CXX_MODULES FILES
            app.cppm
            stateManager.cppm
)
