add_library(libstreamline STATIC)

target_sources(libstreamline PRIVATE
    json/json.cpp
    debug/logger.cpp
)

