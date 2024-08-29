#include <array>                // for array

#include "lincity/transport.h"  // for MAX_HIVOLT_ON_POWERLINE
#include "modules.h"            // for Commodity, CommodityRule, Constructio...

#define POWER_LINE_FLASH_SPEED 100

class PowerlineConstructionGroup: public ConstructionGroup {
public:
    PowerlineConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance,
        int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance,
        cost, tech, range, 2/*mps_pages*/
    )
    {
        commodityRuleCount[STUFF_HIVOLT].maxload = MAX_HIVOLT_ON_POWERLINE;
        commodityRuleCount[STUFF_HIVOLT].take = true;
        commodityRuleCount[STUFF_HIVOLT].give = true;
    }
    // overriding method that creates a power line
    virtual Construction *createConstruction();
};

extern PowerlineConstructionGroup powerlineConstructionGroup;

class Powerline: public Construction {
public:
    Powerline(ConstructionGroup *cstgrp) {
        this->constructionGroup = cstgrp;
        init_resources();
        this->flags |= (FLAG_TRANSPARENT | FLAG_NEVER_EVACUATE);
        this->anim_counter = 0;
        this->anim = 0;
        this->flashing = false;
        initialize_commodities();
        this->trafficCount = this->commodityCount;

        commodityMaxCons[STUFF_HIVOLT] = 100 * 1;
    }
    virtual ~Powerline() { }
    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;
    void flow_power();
    std::array<int, STUFF_COUNT> trafficCount;
    int anim_counter;
    int anim;
    bool flashing;
};


/** @file lincity/modules/power_line.h */
