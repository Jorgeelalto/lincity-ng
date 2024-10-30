/* ---------------------------------------------------------------------- *
 * src/lincity/modules/coal_power.h
 * This file is part of Lincity-NG.
 *
 * Copyright (C) 1995-1997 I J Peters
 * Copyright (C) 1997-2005 Greg Sharp
 * Copyright (C) 2000-2004 Corey Keasling
 * Copyright (C) 2022-2024 David Bears <dbear4q@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
** ---------------------------------------------------------------------- */

#define GROUP_COAL_POWER_COLOUR 0
#define GROUP_COAL_POWER_COST   100000
#define GROUP_COAL_POWER_COST_MUL 5
#define GROUP_COAL_POWER_BUL_COST   200000
#define GROUP_COAL_POWER_TECH   200
#define GROUP_COAL_POWER_FIREC  80
#define GROUP_COAL_POWER_RANGE  0
#define GROUP_COAL_POWER_SIZE  4

#define POWERS_COAL_OUTPUT 11000 //x2 for lo-volt
#define MAX_HIVOLT_AT_COALPS (20 * POWERS_COAL_OUTPUT)
#define POWER_PER_COAL 250
#define MAX_COAL_AT_COALPS (20 * POWERS_COAL_OUTPUT / POWER_PER_COAL)
#define POWERS_COAL_POLLUTION  20
#define LABOR_COALPS_GENERATE 100
#define MAX_LABOR_AT_COALPS (20 * LABOR_COALPS_GENERATE)
#define SMOKE_ANIM_SPEED 300

#include <cstdlib>             // for NULL
#include <array>               // for array
#include <iterator>            // for advance
#include <list>                // for _List_iterator, list, operator!=
#include <map>                 // for map
#include <string>              // for basic_string, operator<

#include "modules.h"

class Coal_powerConstructionGroup: public ConstructionGroup {
public:
    Coal_powerConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance,
        int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance,
        cost, tech, range, 2/*mps_pages*/
    ) {
        commodityRuleCount[STUFF_LABOR].maxload = MAX_LABOR_AT_COALPS;
        commodityRuleCount[STUFF_LABOR].take = true;
        commodityRuleCount[STUFF_LABOR].give = false;
        commodityRuleCount[STUFF_COAL].maxload = MAX_COAL_AT_COALPS;
        commodityRuleCount[STUFF_COAL].take = true;
        commodityRuleCount[STUFF_COAL].give = false;
        commodityRuleCount[STUFF_HIVOLT].maxload = MAX_HIVOLT_AT_COALPS;
        commodityRuleCount[STUFF_HIVOLT].take = false;
        commodityRuleCount[STUFF_HIVOLT].give = true;
    }
    // overriding method that creates a Coal_power
    virtual Construction *createConstruction();
};

extern Coal_powerConstructionGroup coal_powerConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_low_ConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_med_ConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_full_ConstructionGroup;


class Coal_power: public Construction {
public:
    Coal_power(ConstructionGroup *cstgrp) {
        this->constructionGroup = cstgrp;
        init_resources();
        world(x,y)->framesptr->resize(world(x,y)->framesptr->size()+8);
        std::list<ExtraFrame>::iterator frit = frameIt;
        std::advance(frit, 1);
        fr_begin = frit;
        frit->move_x = 5;
        frit->move_y = -378;
        std::advance(frit, 1);
        frit->move_x = 29;
        frit->move_y = -390;
        std::advance(frit, 1);
        frit->move_x = 52;
        frit->move_y = -397;
        std::advance(frit, 1);
        frit->move_x = 76;
        frit->move_y = -409;
        std::advance(frit, 1);
        frit->move_x = 65;
        frit->move_y = -348;
        std::advance(frit, 1);
        frit->move_x = 89;
        frit->move_y = -360;
        std::advance(frit, 1);
        frit->move_x = 112;
        frit->move_y = -371;
        std::advance(frit, 1);
        frit->move_x = 136;
        frit->move_y = -383;
        std::advance(frit, 1);
        fr_end = frit;
        for (frit = fr_begin; frit != world(x,y)->framesptr->end() && frit != fr_end; std::advance(frit, 1))
        {
            frit->resourceGroup = ResourceGroup::resMap["BlackSmoke"];
            frit->frame = -1; // hide smoke
        }
        this->anim = 0;
        this->tech = tech_level;
        this->working_days = 0;
        this->busy = 0;
        initialize_commodities();

        commodityMaxCons[STUFF_LABOR] = 100 * LABOR_COALPS_GENERATE;
        commodityMaxCons[STUFF_COAL] = 100 *
          (POWERS_COAL_OUTPUT / POWER_PER_COAL);
        // commodityMaxProd[STUFF_HIVOLT] = 100 * hivolt_output;
    }

    virtual void initialize() override {
        Construction::initialize();

        this->hivolt_output = (int)(POWERS_COAL_OUTPUT +
          (((double)tech * POWERS_COAL_OUTPUT) / MAX_TECH_LEVEL));
        commodityMaxProd[STUFF_HIVOLT] = 100 * hivolt_output;
    }

    virtual ~Coal_power() //remove 2 or more extraframes
    {
        if(world(x,y)->framesptr)
        {
            world(x,y)->framesptr->erase(fr_begin, fr_end);
            if(world(x,y)->framesptr->empty())
            {
                delete world(x,y)->framesptr;
                world(x,y)->framesptr = NULL;
            }
        }
    }

    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;

    virtual void save(xmlTextWriterPtr xmlWriter) override;
    virtual bool loadMember(xmlpp::TextReader& xmlReader) override;

    std::list<ExtraFrame>::iterator fr_begin, fr_end;
    int anim;
    int  hivolt_output;
    int  tech;
    int  working_days, busy;
};


/** @file lincity/modules/coal_power.h */
