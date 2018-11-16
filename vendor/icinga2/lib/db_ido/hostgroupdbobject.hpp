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

#ifndef HOSTGROUPDBOBJECT_H
#define HOSTGROUPDBOBJECT_H

#include "db_ido/dbobject.hpp"
#include "icinga/hostgroup.hpp"
#include "base/configobject.hpp"

namespace icinga
{

/**
 * A HostGroup database object.
 *
 * @ingroup ido
 */
class HostGroupDbObject final : public DbObject
{
public:
	DECLARE_PTR_TYPEDEFS(HostGroupDbObject);

	HostGroupDbObject(const DbType::Ptr& type, const String& name1, const String& name2);

	Dictionary::Ptr GetConfigFields() const override;
	Dictionary::Ptr GetStatusFields() const override;

private:
	static void MembersChangedHandler(const HostGroup::Ptr& hgfilter);
};

}

#endif /* HOSTGROUPDBOBJECT_H */