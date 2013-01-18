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

#ifndef SCMNOTE_ENUM_MIDI_FORMAT_HPP
#define SCMNOTE_ENUM_MIDI_FORMAT_HPP

namespace scmnote
{
	/*
	  FORMAT_MIDI_0:
	  one track, all events on that track

	  FORMAT_MIDI_1:
	  multiple tracks, and track 1 is the "meta" track that has all
	  "Time Signature", "Set Tempo", "Sequence/Track Name", "Sequence Number",
	  "Marker", "SMTPE Offset" meta events

	  FORMAT_MIDI_2:
	  multiple tracks, all totally independent
	*/ 

	enum EnumMidiFormat
	{
		FORMAT_MIDI_0,
		FORMAT_MIDI_1,
		FORMAT_MIDI_2
	};
}

#endif
