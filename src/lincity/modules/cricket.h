/* ---------------------------------------------------------------------- *
 * src/lincity/modules/cricket.h
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

#ifndef __cricket_h__
#define __cricket_h__


#define GROUP_CRICKET_COLOUR (white(20))
#define GROUP_CRICKET_COST   2000
#define GROUP_CRICKET_COST_MUL 3
#define GROUP_CRICKET_BUL_COST 1000
#define GROUP_CRICKET_TECH     12
#define GROUP_CRICKET_FIREC 20
#define GROUP_CRICKET_RANGE 9
#define GROUP_CRICKET_SIZE 2

#define CRICKET_LABOR   8
#define MAX_LABOR_AT_CRICKET (20 * CRICKET_LABOR)
#define CRICKET_GOODS  3
#define MAX_GOODS_AT_CRICKET (20 * CRICKET_GOODS)
#define MAX_WASTE_AT_CRICKET (20 * CRICKET_GOODS / 3)
#define CRICKET_RUNNING_COST 1
#define CRICKET_ANIMATION_SPEED 750

#include <array>                    // for array

#include "modules.h"

class CricketConstructionGroup: public ConstructionGroup {
public:
    CricketConstructionGroup(
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
        commodityRuleCount[STUFF_LABOR].maxload = MAX_LABOR_AT_CRICKET;
        commodityRuleCount[STUFF_LABOR].take = true;
        commodityRuleCount[STUFF_LABOR].give = false;
        commodityRuleCount[STUFF_GOODS].maxload = MAX_GOODS_AT_CRICKET;
        commodityRuleCount[STUFF_GOODS].take = true;
        commodityRuleCount[STUFF_GOODS].give = false;
        commodityRuleCount[STUFF_WASTE].maxload = MAX_WASTE_AT_CRICKET;
        commodityRuleCount[STUFF_WASTE].take = false;
        commodityRuleCount[STUFF_WASTE].give = true;
    }
    // overriding method that creates a Cricket
    virtual Construction *createConstruction();
};

extern CricketConstructionGroup cricketConstructionGroup;

class Cricket: public Construction {
public:
    Cricket(ConstructionGroup *cstgrp) {
        this->constructionGroup = cstgrp;
        // this->anim = 0;
        this->animate_enable = false;
        this->active = false;
        this->busy = 0;
        this->daycount = 0;
        this->working_days = 0;
        this->covercount = 0;
        initialize_commodities();

        commodityMaxCons[STUFF_LABOR] = 100 * CRICKET_LABOR;
        commodityMaxCons[STUFF_GOODS] = 100 * CRICKET_GOODS;
        commodityMaxProd[STUFF_WASTE] = 100 * (CRICKET_GOODS / 3);
    }

    virtual ~Cricket() { }
    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;
    void cover();

    virtual void save(xmlTextWriterPtr xmlWriter) override;
    virtual bool loadMember(xmlpp::TextReader& xmlReader) override;

    int daycount, covercount;
    int anim;
    bool animate_enable, active;
    int working_days, busy;
};

#endif /* __cricket_h__ */
/** @file lincity/modules/cricket.h */
