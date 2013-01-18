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

#ifndef SCMNOTE_SCM_SONG_STATUS_HPP
#define SCMNOTE_SCM_SONG_STATUS_HPP

#include "VarInt.hpp"

namespace scmnote
{

	class ScmSongStatus
	{
	public:
		ScmSongStatus();
		ScmSongStatus( const ScmSongStatus& status );
		virtual ~ScmSongStatus();

		unsigned int meta_wait;
		unsigned int meter_top;
		unsigned int meter_bottom;
		VarInt prev_dur;
		VarInt current_dur;
		unsigned int dur;
		char prev_note;
		unsigned int prev_octave;
		unsigned int channel;
		unsigned int velocity;
		unsigned int base_dur;
	};
}

#endif
