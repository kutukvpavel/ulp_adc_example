# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/paul/esp/esp-idf/components/ulp/cmake"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/tmp"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/src/ulp_main-stamp"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/src"
  "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/src/ulp_main-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/src/ulp_main-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/paul/Docs_Root/Doc/repositories/ESP32/ulp_adc_example/build/esp-idf/main/ulp_main-prefix/src/ulp_main-stamp${cfgdir}") # cfgdir has leading slash
endif()
