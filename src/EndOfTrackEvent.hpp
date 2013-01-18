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

#ifndef SCMNOTE_END_OF_TRACK_EVENT_HPP
#define SCMNOTE_END_OF_TRACK_EVENT_HPP

#include <iostream>

#include "MetaEvent.hpp"
#include "EnumMetaEvent.hpp"

namespace scmnote
{
	class EndOfTrackEvent : public MetaEvent
	{
	public:
		EndOfTrackEvent();
		EndOfTrackEvent( const EndOfTrackEvent& tm );
		virtual ~EndOfTrackEvent();
		const EndOfTrackEvent& operator = ( const EndOfTrackEvent& tm );

		virtual EnumMetaEvent Get_Type() const;

		virtual MidiEvent* Clone() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;
	};
}

#endif
