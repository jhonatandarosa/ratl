function(make_relative DIR RESULT)

    foreach(filepath ${ARGN})
        if(EXISTS ${filepath})
            if(${DIR})
                file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}" ${filepath})
            else()
                file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}" ${filepath})
            endif()
        else()
            set(rel ${DIR}/${filepath})
        endif()
        list(APPEND REL_PATHS ${rel})
    endforeach()

    set(${RESULT} ${REL_PATHS} PARENT_SCOPE)

endfunction()

function(add_source_directory DIR)

    # save current variables values
    foreach(var ${ARGN})
        set("${var}_before" ${${var}})
        set(${var})
    endforeach()

    # add subdirectory with CMakeLists.txt
    add_subdirectory(${DIR})

    # adjust paths of files in args
    foreach(var ${ARGN})
        set(files)
        # do something interesting with file 'f'
        foreach(filepath ${${var}})
            make_relative(${DIR} rel ${filepath})
            list(APPEND files ${rel})
        endforeach()
        set(${var} "${${var}_before}" ${files} PARENT_SCOPE)
    endforeach()

endfunction()