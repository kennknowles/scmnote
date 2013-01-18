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

#ifndef SCMNOTE_SCMNOTE_HPP
#define SCMNOTE_SCMNOTE_HPP

#include <iostream>
#include <libguile.h>

#include "MidiFile.hpp"
#include "TrackChunk.hpp"
#include "ScmSongStatus.hpp"

namespace scmnote
{

	class ScmNote
	{
	public:
		static MidiFile* ReadScmSong( string filename );

	private:
		static MidiFile* ParseScmSong( SCM scmData );

		static void ParseScmItem( SCM scmItem,
								  TrackChunk& meta,
								  TrackChunk& track,
								  ScmSongStatus& status );
		
		static void ParseScmSymbol( SCM scmItem,
									TrackChunk& meta,
									TrackChunk& track,
									ScmSongStatus& status );
		
		static void ParseScmNum( SCM scmItem,
								 TrackChunk& meta,
								 TrackChunk& track,
								 ScmSongStatus& status );
		
		static void ParseScmListItem( SCM scmItem, 
									  TrackChunk& meta,
									  TrackChunk& track,
									  ScmSongStatus& status );

		static void ParseScmListItemBody( SCM scmItem,
										  TrackChunk& meta,
										  TrackChunk& track,
										  ScmSongStatus& status );
		
		static void ParseScmMerger( SCM scmItem, 
									TrackChunk& meta,
									TrackChunk& track,
									ScmSongStatus& status );
		
		static void ParseScmNoteSymbol( SCM scmItem,
										TrackChunk& meta,
										TrackChunk& chunk,
										ScmSongStatus& status );
		
		static void ParseScmRestSymbol( SCM scmItem,
										TrackChunk& meta,
										TrackChunk& chunk,
										ScmSongStatus& status );
		
		static void ParseScmInstrumentChange( SCM scmItem,
											  TrackChunk& meta,
											  TrackChunk& track,
											  ScmSongStatus& status );

		static void ParseScmChannels( SCM scmItem,
									  TrackChunk& meta,
									  TrackChunk& track,
									  ScmSongStatus& status );
		
		static void ParseScmRepeat( SCM scmItem,
									TrackChunk& meta,
									TrackChunk& track,
									ScmSongStatus& status );

		static void ParseScmTempo( SCM scmItem,
								   TrackChunk& meta,
								   TrackChunk& track,
								   ScmSongStatus& status );
		
		static void ParseScmVolume( SCM scmItem,
									TrackChunk& meta,
									TrackChunk& track,
									ScmSongStatus& status );
		
		static TrackChunk& MergeTracks( vector<TrackChunk> simulTracks );
	};
}

#endif
