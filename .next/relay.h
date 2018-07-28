/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * relay.h
 * Copyright (C) 2017 Andrey Ivanov <search_terminal@mail.ru>
 *
 * monoceros is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * monoceros is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _RELAY_H_
#define _RELAY_H_


class RELAY
{
public:
    setpin();
	getstatus();
    setstatus();
	setref();
	setvalue();
    relayswitch();
    relaytermostat();
protected:
	bool relay;

private:

};

#endif // _RELAY_H_

