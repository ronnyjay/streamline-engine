add_library(libstreamline STATIC)

target_sources(libstreamline PRIVATE
    config/config.cpp
    config/json/json.cpp
    debug/logger.cpp
)

