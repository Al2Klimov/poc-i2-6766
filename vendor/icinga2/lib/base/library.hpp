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

#ifndef LIBRARY_H
#define LIBRARY_H

#include "base/i2-base.hpp"
#include "base/string.hpp"
#include <memory>

namespace icinga
{

#ifndef _WIN32
typedef void *LibraryHandle;
#else /* _WIN32 */
typedef HMODULE LibraryHandle;
#endif /* _WIN32 */

class Library
{
public:
	Library() = default;
	Library(const String& name);

	void *GetSymbolAddress(const String& name) const;

	template<typename T>
	T GetSymbolAddress(const String& name) const
	{
		static_assert(!std::is_same<T, void *>::value, "T must not be void *");

		return reinterpret_cast<T>(GetSymbolAddress(name));
	}

private:
	std::shared_ptr<LibraryHandle> m_Handle;
};

}

#endif /* LIBRARY_H */
