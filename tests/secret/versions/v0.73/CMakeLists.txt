cmake_minimum_required(VERSION 3.10)
#project (c_project VERSION 1.0)
project(project VERSION 1.0 LANGUAGES CXX C)
#project(c_project VERSION 1.0 LANGUAGES C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")

# Поиск библиотеки Judy
find_library(JUDY_LIB NAMES Judy judy)
# Для совместимости с C-библиотекой Judy
find_path(JUDY_INCLUDE_DIR Judy.h)

#add_executable(project judy_sl_test.cpp)
add_executable(project test.cpp)

# Подключение библиотеки Judy
target_link_libraries(project PRIVATE ${JUDY_LIB})


#target_include_directories(c_project PUBLIC
#	${JUDY_INCLUDE_DIR}
#)
target_include_directories(project PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${JUDY_INCLUDE_DIR}
)

