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

#include "VarInt.hpp"
#include "EndOfTrackEvent.hpp"
#include "EnumMetaEvent.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;

EndOfTrackEvent::EndOfTrackEvent()
{ }
	
EndOfTrackEvent::EndOfTrackEvent( const EndOfTrackEvent& tm )
{ }
	
EndOfTrackEvent::~EndOfTrackEvent()
{ }

const EndOfTrackEvent& 
EndOfTrackEvent::operator = ( const EndOfTrackEvent& tm )
{
	return ( *this );
}

EnumMetaEvent EndOfTrackEvent::Get_Type() const
{
	return ( META_End_of_Track );
}

MidiEvent* EndOfTrackEvent::Clone() const
{
	return ( new EndOfTrackEvent( *this ) );
}

unsigned long int EndOfTrackEvent::Get_Length() const
{
	return ( 3 );
}

void EndOfTrackEvent::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emitting End of Track event\n" );
	write8( os, 0xFF );
	write8( os, 0x2F );
	write8( os, 0x00 );
}
