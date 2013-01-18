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

#ifndef SCMNOTE_MIDI_ITEM_HPP
#define SCMNOTE_MIDI_ITEM_HPP

#include <iostream>

#include "MidiEvent.hpp"
#include "VarInt.hpp"

namespace scmnote
{
	class MidiItem
	{
	public:
		MidiItem();
		MidiItem( const MidiItem& mi );
		MidiItem( const VarInt& deltaTime, const MidiEvent& event );
		virtual ~MidiItem();
		const MidiItem& operator = ( const MidiItem& mi );

		VarInt Get_Length() const;

		VarInt* Get_DeltaTime() const;
		void Set_DeltaTime( const VarInt& dt );

		MidiEvent* Get_Event() const;
		void Set_Event( const MidiEvent& mi );

		void Emit( ostream& os ) const;
		
	protected:
		VarInt* m_DeltaTime;
		MidiEvent* m_Event;
	};
	
}

#endif
