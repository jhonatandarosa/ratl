add_subdirectory(main)
add_subdirectory(test)

set(LCOV_REMOVE_EXTRA "'.conan/*'" "'*test/*'")
setup_target_for_coverage("${PROJECT_NAME}-coverage" "${PROJECT_NAME}-test" "coverage")