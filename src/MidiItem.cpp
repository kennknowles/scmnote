/*
  This file is part of scmnote - A scheme music system
  Copyright (C) 2002 Free Software Foundation, Inc
  
  scmnote is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  scmnote is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with scmnote; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <iostream>

#include "MidiItem.hpp"

#include "MidiEvent.hpp"
#include "VarInt.hpp"
#include "debug.hpp"

using namespace scmnote;

//***************************************************************
// The Big Four
//***************************************************************

MidiItem::MidiItem()
{
	m_DeltaTime = new VarInt();
}

MidiItem::MidiItem( const MidiItem& mi )
{
	m_DeltaTime = new VarInt( *(mi.m_DeltaTime) );
	m_Event = mi.m_Event->Clone();
}

MidiItem::MidiItem( const VarInt& deltaTime, const MidiEvent& event )
{
	m_DeltaTime = new VarInt( deltaTime );
	m_Event = event.Clone();
}

MidiItem::~MidiItem()
{
	delete m_DeltaTime;
	delete m_Event;
}

const MidiItem& MidiItem::operator = ( const MidiItem& mi )
{
	if ( this != &mi )
	{
		(*m_DeltaTime) = *(mi.m_DeltaTime);
		(*m_Event) = *(mi.m_Event);
	}
	return ( *this );
}

//***************************************************************
// public functions
//***************************************************************

VarInt MidiItem::Get_Length() const
{
	return ( m_DeltaTime->Get_Length() + m_Event->Get_Length() );
}

VarInt* MidiItem::Get_DeltaTime() const
{
	return ( m_DeltaTime );
}

void MidiItem::Set_DeltaTime( const VarInt& dt )
{
	(*m_DeltaTime) = dt;
}

MidiEvent* MidiItem::Get_Event() const
{
	return ( m_Event );
}
	
void MidiItem::Set_Event( const MidiEvent& mi )
{
	(*m_Event) = mi;
}

void MidiItem::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emitting MidiItem:\n" );

	m_DeltaTime->Emit( os );
	m_Event->Emit( os );
}
