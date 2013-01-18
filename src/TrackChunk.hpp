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

#ifndef SCMNOTE_TRACK_CHUNK_HPP
#define SCMNOTE_TRACK_CHUNK_HPP

#include <iostream>
#include <vector>

#include "MidiChunk.hpp"
#include "MidiItem.hpp"

namespace scmnote
{
	class TrackChunk : public MidiChunk
	{
	public:
		TrackChunk();
		TrackChunk( const TrackChunk& tc );
		virtual ~TrackChunk();
		virtual const TrackChunk& operator = ( const TrackChunk& tc );

		virtual string Get_Type() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;

		virtual void Append( MidiItem* item );
		virtual vector<MidiItem*> Get_Items() const;

	protected:
		vector<MidiItem*> m_Items;
	};
}

#endif
