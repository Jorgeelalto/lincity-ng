/* ---------------------------------------------------------------------- *
 * src/lincity/modules/modules.h
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

#ifndef __modules_h__
#define __modules_h__

// IWYU pragma: always_keep
// IWYU pragma: begin_exports
#include <libxml/xmlwriter.h> // TODO: do not include this in headers
#include <libxml++/parsers/textreader.h>
#include <string>

#include "gui_interface/mps.h"            // tally: 111111111111111111111111111111111
#include "lincity/all_buildings.h"        // tally: 1111111111111111111111111111111
#include "lincity/commodities.hpp"
#include "lincity/engglobs.h"             // tally:
#include "lincity/engine.h"               // tally: 1111111111111111111
#include "lincity/groups.h"               // tally: 11111111111111111111111111111111
#include "lincity/lin-city.h"             // tally: 111111111111111111111111111111111
#include "lincity/lintypes.h"             // tally: 111111111111111111111111111111111
#include "lincity/resources.hpp"
#include "lincity/stats.h"                // tally: 11111111111111
#include "lincity/world.h"                // tally: 111111111111111111111111
#include "lincity/xmlloadsave.h"
#include "tinygettext/gettext.hpp"        // tally: 111111111111111111111111111111111
// IWYU pragma: end_exports

#endif /* __modules_h__ */

/** @file lincity/modules/modules.h */
