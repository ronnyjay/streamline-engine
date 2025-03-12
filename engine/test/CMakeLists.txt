include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SPARSE_SET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/scene/test_sparse_set.cpp")
file(GLOB TEST_REGISTRY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/scene/test_registry.cpp")

file(GLOB TEST_TRNS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_transformation.cpp")
file(GLOB TEST_TRIG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_trigonmetric.cpp")
file(GLOB TEST_EXPO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_exponential.cpp")
file(GLOB TEST_GEOM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_geometric.cpp")
file(GLOB TEST_MAT2_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_mat2x2.cpp")
file(GLOB TEST_MAT3_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_mat3x3.cpp")
file(GLOB TEST_MAT4_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_mat4x4.cpp")
file(GLOB TEST_VEC2_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_vec2.cpp")
file(GLOB TEST_VEC3_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_vec3.cpp")
file(GLOB TEST_VEC4_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/test_vec4.cpp")

set(GLOB_SOURCES 
  ${TEST_SPARSE_SET_SOURCES}
  ${TEST_REGISTRY_SOURCES}
  ${TEST_TRNS_SOURCES} 
  ${TEST_TRIG_SOURCES} 
  ${TEST_EXPO_SOURCES} 
  ${TEST_GEOM_SOURCES} 
  ${TEST_MAT2_SOURCES}
  ${TEST_MAT3_SOURCES}
  ${TEST_MAT4_SOURCES}
  ${TEST_VEC2_SOURCES}
  ${TEST_VEC3_SOURCES}
  ${TEST_VEC4_SOURCES}
)

add_executable(engine-test ${GLOB_SOURCES})

target_include_directories(engine-test PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(engine-test PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(engine-test)