# Copyright 2012 Jared Boone
# Copyright 2013 Benjamin Vernoux
#
# This file is part of HackRF.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

# Based heavily upon the libftdi cmake setup.

set(INSTALL_DEFAULT_BINDIR "bin" CACHE STRING "Appended to CMAKE_INSTALL_PREFIX")

if(MSVC)
add_library(libgetopt_static STATIC
    ../getopt/getopt.c
)
endif()
add_executable(hackrf_laser hackrf_laser.c ad5724.c)
install(TARGETS hackrf_laser RUNTIME DESTINATION ${INSTALL_DEFAULT_BINDIR})

if(NOT libhackrf_SOURCE_DIR)
include_directories(${LIBHACKRF_INCLUDE_DIR})
LIST(APPEND TOOLS_LINK_LIBS ${LIBHACKRF_LIBRARIES})
else()
LIST(APPEND TOOLS_LINK_LIBS hackrf)
endif()

if(MSVC)
LIST(APPEND TOOLS_LINK_LIBS libgetopt_static)
endif()

LIST(APPEND TOOLS_LINK_LIBS m fftw3f)

target_link_libraries(hackrf_laser ${TOOLS_LINK_LIBS})
