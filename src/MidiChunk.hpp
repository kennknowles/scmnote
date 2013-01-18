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

#ifndef SCMNOTE_MIDI_CHUNK_HPP
#define SCMNOTE_MIDI_CHUNK_HPP

#include <iostream>
#include <string>

namespace scmnote
{
	class MidiChunk
	{
	public:
		virtual string Get_Type() const = 0;
		virtual unsigned long int Get_Length() const = 0;
		virtual void Emit( ostream& os ) const = 0;
	};
}

#endif
