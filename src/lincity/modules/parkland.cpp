/* ---------------------------------------------------------------------- *
 * parkland.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#include "parkland.h"

#include <string>                   // for basic_string

#include "modules.h"

// Parkland:
ParklandConstructionGroup parklandConstructionGroup(
     N_("Park"),
     TRUE,                     /* need credit? */
     GROUP_PARKLAND,
     GROUP_PARKLAND_SIZE,
     GROUP_PARKLAND_COLOUR,
     GROUP_PARKLAND_COST_MUL,
     GROUP_PARKLAND_BUL_COST,
     GROUP_PARKLAND_FIREC,
     GROUP_PARKLAND_COST,
     GROUP_PARKLAND_TECH,
     GROUP_PARKLAND_RANGE
);

ParklandConstructionGroup parkpondConstructionGroup(
     N_("Park (Pond)"),
     TRUE,                     /* need credit? */
     GROUP_PARKPOND,
     GROUP_PARKLAND_SIZE,
     GROUP_PARKLAND_COLOUR,
     GROUP_PARKLAND_COST_MUL,
     GROUP_PARKLAND_BUL_COST,
     GROUP_PARKLAND_FIREC,
     GROUP_PARKLAND_COST,
     GROUP_PARKLAND_TECH,
     GROUP_PARKLAND_RANGE
);

Construction *ParklandConstructionGroup::createConstruction() {
  return new Parkland(this);
}

void Parkland::update()
{
    if (world(x,y)->pollution > 10 && (total_time & 1) == 0)
        world(x,y)->pollution --;
}

void Parkland::report()
{
    int i = 0;

    mps_store_title(i, constructionGroup->name);
    i++;
    mps_store_sd(i++, N_("Air Pollution"), world(x,y)->pollution);
}

/** @file lincity/modules/parkland.cpp */
