include(CMakeParseArguments)
include(GoogleTest)

function(add_cpp_exercise_app target source_dir)
  set(source_paths "")
  foreach(source IN LISTS ARGN)
    list(APPEND source_paths "${source_dir}/${source}")
  endforeach()

  add_executable(${target} ${source_paths})
  target_include_directories(${target} PRIVATE "${source_dir}")
  set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endfunction()

function(add_cpp_exercise_library target source_dir)
  set(source_paths "")
  foreach(source IN LISTS ARGN)
    list(APPEND source_paths "${source_dir}/${source}")
  endforeach()

  add_library(${target} STATIC ${source_paths})
  target_include_directories(${target} PUBLIC "${source_dir}")
  set_target_properties(${target} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  )
endfunction()

function(add_cpp_gtest_binary target)
  cmake_parse_arguments(ARG "" "" "SOURCES;LIBRARIES;INCLUDE_DIRS;COMPILE_DEFINITIONS" ${ARGN})

  add_executable(${target} ${ARG_SOURCES})
  target_include_directories(${target} PRIVATE
    "${PROJECT_SOURCE_DIR}"
    ${ARG_INCLUDE_DIRS}
  )
  target_link_libraries(${target} PRIVATE GTest::gtest_main ${ARG_LIBRARIES})

  if(ARG_COMPILE_DEFINITIONS)
    target_compile_definitions(${target} PRIVATE ${ARG_COMPILE_DEFINITIONS})
  endif()

  set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )

  gtest_discover_tests(${target})
endfunction()

function(add_valgrind_leak_test name target)
  if(NOT VALGRIND_EXECUTABLE)
    return()
  endif()

  add_test(
    NAME ${name}
    COMMAND
      "${VALGRIND_EXECUTABLE}"
      --leak-check=full
      --show-leak-kinds=all
      --errors-for-leak-kinds=definite,indirect,possible
      --error-exitcode=1
      "$<TARGET_FILE:${target}>"
  )
endfunction()
