/* ---------------------------------------------------------------------- *
 * substation.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#include "substation.h"

#include <list>                     // for _List_iterator
#include <map>                      // for map
#include <string>                   // for basic_string, operator<

#include "modules.h"

SubstationConstructionGroup substationConstructionGroup(
    N_("Power Substation"),
     FALSE,                     /* need credit? */
     GROUP_SUBSTATION,
     GROUP_SUBSTATION_SIZE,
     GROUP_SUBSTATION_COLOUR,
     GROUP_SUBSTATION_COST_MUL,
     GROUP_SUBSTATION_BUL_COST,
     GROUP_SUBSTATION_FIREC,
     GROUP_SUBSTATION_COST,
     GROUP_SUBSTATION_TECH,
     GROUP_SUBSTATION_RANGE
);

//helper groups for graphics and sound sets, don't add them to ConstructionGroup::groupMap
SubstationConstructionGroup substation_RG_ConstructionGroup = substationConstructionGroup;
SubstationConstructionGroup substation_G_ConstructionGroup  = substationConstructionGroup;


Construction *SubstationConstructionGroup::createConstruction() {
  return new Substation(this);
}

void Substation::update()
{
    int use_hivolt = (SUBSTATION_HIVOLT < commodityCount[STUFF_HIVOLT])?SUBSTATION_HIVOLT:commodityCount[STUFF_HIVOLT];
    if ( (use_hivolt > 0)
     && (commodityCount[STUFF_LOVOLT] <= MAX_LOVOLT_AT_SUBSTATION-2 * use_hivolt))
    {
        consumeStuff(STUFF_HIVOLT, use_hivolt);
        produceStuff(STUFF_LOVOLT, 2 * use_hivolt);
        working_days += use_hivolt;
    }
    if (total_time % 100 == 99) //monthly update
    {
        reset_prod_counters();
        busy = working_days/SUBSTATION_HIVOLT;
        working_days = 0;
    }
}

void Substation::animate() {
  if (commodityCount[STUFF_LOVOLT] > (MAX_LOVOLT_AT_SUBSTATION / 2))
    frameIt->resourceGroup = ResourceGroup::resMap["SubstationOn"];
  else if (commodityCount[STUFF_LOVOLT] > (MAX_LOVOLT_AT_SUBSTATION / 10))
    frameIt->resourceGroup = ResourceGroup::resMap["SubstationOff"];
  else
    frameIt->resourceGroup = ResourceGroup::resMap["Substation"];
  soundGroup = frameIt->resourceGroup;
}

void Substation::report()
{
    int i = 0;
    mps_store_title(i, constructionGroup->name);
    i++;
    mps_store_sfp(i++, N_("busy"), busy);
    // i++;
    list_commodities(&i);
}

/** @file lincity/modules/substation.cpp */
