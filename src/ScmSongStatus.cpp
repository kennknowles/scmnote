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

#include "ScmSongStatus.hpp"

using namespace scmnote;

ScmSongStatus::ScmSongStatus()
{ 
	meta_wait=0;
	meter_top=4;
	meter_bottom=4;
	prev_dur=0;
	current_dur=0;
	base_dur=96;
	prev_note=0;
	prev_octave=3;
	channel=0;
	velocity=100;
	dur = base_dur;
}

ScmSongStatus::ScmSongStatus( const ScmSongStatus& status )
{
	meta_wait = status.meta_wait;
	meter_top = status.meter_top;
	meter_bottom = status.meter_bottom;
	prev_dur = status.prev_dur;
	current_dur = status.current_dur;
	dur = status.dur;
	prev_note = status.prev_note;
	prev_octave = status.prev_octave;
	channel = status.channel;
	velocity = status.velocity;
	base_dur = status.base_dur;
}

ScmSongStatus::~ScmSongStatus() { }
