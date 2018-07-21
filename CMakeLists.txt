cmake_minimum_required(VERSION 2.8)
project(inspectrum)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HACKRF REQUIRED libhackrf)
pkg_check_modules(FFTW REQUIRED fftw3f)

include_directories(${HACKRF_INCLUDE_DIRS} /usr/local/include/ol)

add_executable(hackrf_laser hackrf_laser.c)
target_link_libraries(hackrf_laser m ol ${HACKRF_LIBRARIES} ${FFTW_LIBRARIES})
