/* ---------------------------------------------------------------------- *
 * src/lincity/modules/waterwell.h
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

#define GROUP_WATERWELL_COLOUR    (blue(31))
#define GROUP_WATERWELL_COST      1
#define GROUP_WATERWELL_COST_MUL 2
#define GROUP_WATERWELL_BUL_COST      1
#define GROUP_WATERWELL_TECH      0
#define GROUP_WATERWELL_FIREC 0
#define GROUP_WATERWELL_RANGE 0
#define GROUP_WATERWELL_SIZE 2

#define MAX_POLLUTION_AT_WATERWELL 3000
#define WATER_PER_UGW 400
#define MAX_WATER_AT_WATERWELL (20 * WATER_PER_UGW * GROUP_WATERWELL_SIZE * GROUP_WATERWELL_SIZE)
#include <array>                    // for array

#include "modules.h"

class WaterwellConstructionGroup: public ConstructionGroup {
public:
    WaterwellConstructionGroup(
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
        commodityRuleCount[STUFF_WATER].maxload = MAX_WATER_AT_WATERWELL;
        commodityRuleCount[STUFF_WATER].give = true;
        commodityRuleCount[STUFF_WATER].take = false;
    }
    // overriding method that creates a waterwell
    virtual Construction *createConstruction();
};

extern WaterwellConstructionGroup waterwellConstructionGroup;

class Waterwell: public Construction {
public:
    Waterwell(ConstructionGroup *cstgrp) {
        this->constructionGroup = cstgrp;
        this->busy = 0;
        this->working_days = 0;
        initialize_commodities();

        int area = cstgrp->size * cstgrp->size;
        commodityMaxProd[STUFF_WATER] = 100 * WATER_PER_UGW * area;
    }

    virtual ~Waterwell() { }
    virtual void update() override;
    virtual void report() override;
    virtual void place(int x, int y) override;

    int water_output;
    int ugwCount;
    int working_days, busy;
};

/** @file lincity/modules/waterwell.h */
