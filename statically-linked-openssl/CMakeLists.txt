cmake_minimum_required (VERSION 3.5)
project (sm3)

find_package(openssl 1.1)
if (NOT OPENSSL_FOUND)
  if (NOT "$ENV{OPENSSL_ROOT_DIR}" STREQUAL "")
    set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
  elseif (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
  elseif(UNIX AND NOT APPLE)
    set(OPENSSL_ROOT_DIR "/usr/include/openssl")
  else()
    message(FATAL_ERROR "openssl not found and don't know where to look, please specify OPENSSL_ROOT_DIR")
  endif()

  set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
  set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/libssl.dylib;${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib")
endif()
message("OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message("OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

add_executable(sm3 main.cpp sm3.c)
set_property(TARGET sm3 PROPERTY CXX_STANDARD 17)
target_include_directories(sm3 PRIVATE ${OPENSSL_INCLUDE_DIR})
#target_link_libraries(sm3 ${OPENSSL_LIBRARIES})
