# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/paul/esp/esp-idf/components/bootloader/subproject"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/tmp"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/src/bootloader-stamp"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/src"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
