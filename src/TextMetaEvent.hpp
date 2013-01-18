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

#ifndef SCMNOTE_TEXT_META_EVENT_HPP
#define SCMNOTE_TEXT_META_EVENT_HPP

/*
  This class represents the following events:
  META_Text_Event, 
  META_Copyright_Notice,
  META_Sequence_Track_Name,
  META_Instrument_Name,
  META_Lyric,
  META_Marker,
  META_Cue_Point
*/

#include <iostream>
#include <string>

#include "VarInt.hpp"
#include "MetaEvent.hpp"
#include "EnumMetaEvent.hpp"

namespace scmnote
{
	class TextMetaEvent : public MetaEvent
	{
	public:
		TextMetaEvent( EnumMetaEvent type );
		TextMetaEvent( EnumMetaEvent type, string text );
		TextMetaEvent( const TextMetaEvent& tm );
		virtual ~TextMetaEvent();
		const TextMetaEvent& operator = ( const TextMetaEvent& tm );

		virtual void Set_Type( EnumMetaEvent type );
		virtual EnumMetaEvent Get_Type() const;

		VarInt Get_TextLength() const;
		string Get_Text() const;
		void Set_Text( string text );

		virtual MidiEvent* Clone() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;
	
	protected:
		EnumMetaEvent m_Type;
		string m_Text;
	};
}

#endif
