

function(testfile_runner)
    set(oneValueArgs TESTFILE)

    cmake_parse_arguments(
        "testfile"
        ""
        "${oneValueArgs}"           # single value variables
        ""
        ${ARGN}
    )

    add_test(
        NAME ${testfile_TESTFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testfile_runner ${testfile_TESTFILE}
    )
endfunction()