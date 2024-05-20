add_executable(CarShop src/CarData.cpp)
target_include_directories(CarShop PRIVATE include)
target_link_libraries(CarShop PRIVATE TimerService)