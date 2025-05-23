add_subdirectory(modules)

add_library(lincity_lib  STATIC
		all_buildings.cpp
		all_buildings.h
		commodities.cpp
		commodities.hpp
		ConstructionCount.cpp
		ConstructionCount.h
		ConstructionManager.cpp
		ConstructionManager.h
		ConstructionRequest.cpp
		ConstructionRequest.h
		engglobs.cpp
		engglobs.h
		engine.cpp
		engine.h
		groups.h
		init_game.cpp
		init_game.h
		lc_locale.cpp
		lc_locale.h
		lclib.cpp
		lclib.h
		lctypes.h
		lin-city.h
		lintypes.cpp
		lintypes.h
		resources.cpp
		resources.hpp
		simulate.cpp
		simulate.h
		stats.cpp
		stats.h
		sustainable.h
		transport.cpp
		transport.h
		UserOperation.cpp
		UserOperation.h
		Vehicles.cpp
		Vehicles.h
		world.cpp
		world.h
		xmlloadsave.cpp
		xmlloadsave.h
)

add_library(LinCity::lib ALIAS lincity_lib)

target_link_libraries(lincity_lib
		PUBLIC
		LinCity::lib_modules
		$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
		ZLIB::ZLIB
		PkgConfig::libXMLPlusPlus
		PRIVATE
		tinygettext
		LinCity::physfsstream
		LinCity::gui
		)

target_include_directories(lincity_lib PRIVATE ${PHYSFS_INCLUDE_DIR})
target_link_libraries(lincity_lib PRIVATE ${PHYSFS_LIBRARY})

if (NOT WIN32)
	add_compile_definitions(lincity_lib PRIVATE DEFAULT_LIBDIR="lib")    # TODO
endif()

include_directories(.)
