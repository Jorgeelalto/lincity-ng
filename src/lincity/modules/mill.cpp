/* ---------------------------------------------------------------------- *
 * mill.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#include "mill.h"

#include <list>                     // for _List_iterator
#include <string>                   // for basic_string
#include <vector>                   // for vector

#include "modules.h"


MillConstructionGroup millConstructionGroup(
    N_("Textile Mill"),
    FALSE,                     /* need credit? */
    GROUP_MILL,
    GROUP_MILL_SIZE,
    GROUP_MILL_COLOUR,
    GROUP_MILL_COST_MUL,
    GROUP_MILL_BUL_COST,
    GROUP_MILL_FIREC,
    GROUP_MILL_COST,
    GROUP_MILL_TECH,
    GROUP_MILL_RANGE
);

Construction *MillConstructionGroup::createConstruction() {
  return new Mill(this);
}

void Mill::update()
{
    bool use_coal = (commodityCount[STUFF_COAL]*MAX_LOVOLT_AT_MILL > commodityCount[STUFF_LOVOLT]*MAX_COAL_AT_MILL);
    flags &= ~(FLAG_POWERED);
    if ((use_coal?commodityCount[STUFF_COAL]:commodityCount[STUFF_LOVOLT]) >= (use_coal?COAL_USED_BY_MILL:COAL_USED_BY_MILL * MILL_POWER_PER_COAL)
    && (flags |= FLAG_POWERED, commodityCount[STUFF_FOOD] >= FOOD_USED_BY_MILL)
    && (commodityCount[STUFF_LABOR] >= MILL_LABOR)
    && (commodityCount[STUFF_GOODS] <= MAX_GOODS_AT_MILL - GOODS_MADE_BY_MILL))
    {
        if(use_coal)
            consumeStuff(STUFF_COAL, COAL_USED_BY_MILL);
        else
            consumeStuff(STUFF_LOVOLT, COAL_USED_BY_MILL * MILL_POWER_PER_COAL);
        consumeStuff(STUFF_FOOD, FOOD_USED_BY_MILL);
        consumeStuff(STUFF_LABOR, MILL_LABOR);
        produceStuff(STUFF_GOODS, GOODS_MADE_BY_MILL);
        ++working_days;
        animate_enable = true;
        if ((++pol_count %= 7) == 0)
        {   world(x,y)->pollution++;}
    }

    //monthly update
    if(total_time % 100 == 99) {
        reset_prod_counters();
        busy = working_days;
        working_days = 0;
    }
}

void Mill::animate() {
  int& frame = frameIt->frame;
  if(animate_enable && real_time >= anim) {
    anim = real_time + ANIM_THRESHOLD(MILL_ANIM_SPEED);
    animate_enable = false;
    if(++frame >= (int)frameIt->resourceGroup->graphicsInfoVector.size())
      frame = 1;
  }
  else if(!busy) {
    frame = 0;
  }
}

void Mill::report()
{
    int i = 0;
    mps_store_title(i, constructionGroup->name);
    mps_store_sfp(i++, N_("busy"), (float) busy);
    // i++;
    list_commodities(&i);
}


/** @file lincity/modules/mill.cpp */
