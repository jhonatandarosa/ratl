function(conan_add_package PACKAGE VERSION AUTHOR CHANNEL)
    list(APPEND CI_PKGS "${PACKAGE}/${VERSION}@${AUTHOR}/${CHANNEL}")
    list(REMOVE_DUPLICATES CI_PKGS)
    set(CI_PKGS ${CI_PKGS} CACHE INTERNAL "Conan Install Packages" FORCE)

    foreach(ARG ${ARGN})
        list(APPEND CI_PKGS_OPTS "${PACKAGE}:${ARG}")
    endforeach()
    if (CI_PKGS_OPTS)
        list(REMOVE_DUPLICATES CI_PKGS_OPTS)
        set(CI_PKGS_OPTS ${CI_PKGS_OPTS} CACHE INTERNAL "Conan Install Packages Options" FORCE)
    endif()
endfunction()

function(conan_gen_conanfile CONANFILE)
    # [requires] section
    file(WRITE  ${CONANFILE} "[requires]\n")
    foreach(PKG ${CI_PKGS})
        file(APPEND ${CONANFILE} "${PKG}\n")
    endforeach()
    file(APPEND ${CONANFILE} "\n")

    # [options] section
    file(APPEND ${CONANFILE} "[options]\n")
    if(CI_PKGS_OPTS)
        foreach(PKG_OPT ${CI_PKGS_OPTS})
            file(APPEND ${CONANFILE} "${PKG_OPT}\n")
        endforeach()
    endif()
    file(APPEND ${CONANFILE} "\n")

    # [generators] section
    file(APPEND ${CONANFILE} "[generators]\ncmake")

endfunction()

function(conan_install)
    set(options BUILD_MISSING FAST)
    #    set(oneValueArgs DESTINATION RENAME)
    #    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments(CI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    list(APPEND CI_ARGS "-s")
    list(APPEND CI_ARGS "build_type=${CMAKE_BUILD_TYPE}")

    #########################################
    ########    compiler settings    ########

    # compiler type
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CI_COMPILER "clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CI_COMPILER "gcc")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CI_COMPILER "Visual Studio")
    endif ()

    # compiler version
    string(REGEX REPLACE
            "([1-9]+\\.[0-9]+)(.*)"
            "\\1"
            CI_COMPILER_VERSION
            ${CMAKE_CXX_COMPILER_VERSION}
    )

    list(APPEND CI_ARGS "-s")
    list(APPEND CI_ARGS "compiler=${CI_COMPILER}")
    #   TODO: make possible to specify libcxx or detect automatically
    list(APPEND CI_ARGS "-s")
    list(APPEND CI_ARGS "compiler.libcxx=libstdc++")

    list(APPEND CI_ARGS "-s")
    list(APPEND CI_ARGS "compiler.version=${CI_COMPILER_VERSION}")

    ########    compiler settings    ########
    #########################################
    set(CI_CONANFILE "${CMAKE_SOURCE_DIR}/conanfile.txt")

    if(NOT EXISTS ${CI_CONANFILE})
        conan_gen_conanfile(${CI_CONANFILE})
        set(CI_CONANFILE_GEN True)
    endif()
    if (CI_BUILD_MISSING)
        list(APPEND CI_ARGS "--build")
        list(APPEND CI_ARGS "missing")
    endif ()

    execute_process(
            COMMAND conan install .. ${CI_ARGS}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            RESULT_VARIABLE EXIT_CODE
    )

    if (CI_CONANFILE_GEN)
        file(REMOVE ${CI_CONANFILE})
    endif ()

    if (NOT ${EXIT_CODE} EQUAL 0)
        message(FATAL_ERROR "Conan install failed with exit code ${EXIT_CODE}")
    endif()
endfunction()