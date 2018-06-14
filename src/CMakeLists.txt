project(ratl)

add_subdirectory(main)
add_subdirectory(test)

set(LCOV_REMOVE_EXTRA "'.conan/*'" "*thirdparty/*" "'*test/*'")
setup_target_for_coverage("${PROJECT_NAME}-coverage" "${PROJECT_NAME}-test" "coverage")