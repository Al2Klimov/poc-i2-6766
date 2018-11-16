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

#include "base/loader.hpp"
#include "base/logger.hpp"
#include "base/exception.hpp"
#include "base/application.hpp"

using namespace icinga;

boost::thread_specific_ptr<std::priority_queue<DeferredInitializer> >& Loader::GetDeferredInitializers()
{
	static boost::thread_specific_ptr<std::priority_queue<DeferredInitializer> > initializers;
	return initializers;
}

void Loader::ExecuteDeferredInitializers()
{
	if (!GetDeferredInitializers().get())
		return;

	while (!GetDeferredInitializers().get()->empty()) {
		DeferredInitializer initializer = GetDeferredInitializers().get()->top();
		GetDeferredInitializers().get()->pop();
		initializer();
	}
}

void Loader::AddDeferredInitializer(const std::function<void()>& callback, int priority)
{
	if (!GetDeferredInitializers().get())
		GetDeferredInitializers().reset(new std::priority_queue<DeferredInitializer>());

	GetDeferredInitializers().get()->push(DeferredInitializer(callback, priority));
}
