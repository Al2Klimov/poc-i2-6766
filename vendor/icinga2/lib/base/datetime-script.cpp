/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2018 Icinga Development Team (https://icinga.com/)      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "base/datetime.hpp"
#include "base/function.hpp"
#include "base/functionwrapper.hpp"
#include "base/scriptframe.hpp"
#include "base/objectlock.hpp"

using namespace icinga;

static String DateTimeFormat(const String& format)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	DateTime::Ptr self = static_cast<DateTime::Ptr>(vframe->Self);
	REQUIRE_NOT_NULL(self);

	return self->Format(format);
}

Object::Ptr DateTime::GetPrototype()
{
	static Dictionary::Ptr prototype = new Dictionary({
		{ "format", new Function("DateTime#format", DateTimeFormat, { "format" }) }
	});

	return prototype;
}
