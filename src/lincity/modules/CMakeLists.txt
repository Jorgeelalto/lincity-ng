add_library(lincity_lib_modules  STATIC
		all_modules.cpp
		all_modules.h
		blacksmith.cpp
		blacksmith.h
		coal_power.cpp
		coal_power.h
		coalmine.cpp
		coalmine.h
		commune.cpp
		commune.h
		cricket.cpp
		cricket.h
		fire.cpp
		fire.h
		firestation.cpp
		firestation.h
		health_centre.cpp
		health_centre.h
		heavy_industry.cpp
		heavy_industry.h
		light_industry.cpp
		light_industry.h
		market.cpp
		market.h
		mill.cpp
		mill.h
		modules.h
		modules_interfaces.h
		monument.cpp
		monument.h
		oremine.cpp
		oremine.h
		organic_farm.cpp
		organic_farm.h
		parkland.cpp
		parkland.h
		port.cpp
		port.h
		pottery.cpp
		pottery.h
		power_line.cpp
		power_line.h
		recycle.cpp
		recycle.h
		residence.cpp
		residence.h
		rocket_pad.cpp
		rocket_pad.h
		school.cpp
		school.h
		shanty.cpp
		shanty.h
		solar_power.cpp
		solar_power.h
		substation.cpp
		substation.h
		tip.cpp
		tip.h
		track_road_rail.cpp
		track_road_rail.h
		university.cpp
		university.h
		water.cpp
		water.h
		waterwell.cpp
		waterwell.h
		windmill.cpp
		windmill.h
		windpower.cpp
		windpower.h
		)

add_library(LinCity::lib_modules ALIAS lincity_lib_modules)

target_link_libraries(lincity_lib_modules
		PUBLIC
		tinygettext
		LinCity::lib
		PkgConfig::libXMLPlusPlus
)

target_include_directories(lincity_lib_modules PRIVATE ${PHYSFS_INCLUDE_DIR})
target_link_libraries(lincity_lib_modules PRIVATE ${PHYSFS_LIBRARY})

include_directories(.)
