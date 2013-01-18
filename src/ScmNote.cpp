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


#include <libguile.h>
#include <string>
#include <cstdlib>
#include <climits>

#include "MidiFile.hpp"
#include "NoteMessage.hpp"
#include "ProgramChangeMessage.hpp"
#include "ControllerChange.hpp"
#include "EnumController.hpp"
#include "TempoEvent.hpp"

#include "ScmNote.hpp"
#include "ScmSongStatus.hpp"
#include "debug.hpp"

using namespace scmnote;

//******************************************************************
// Public Functions
//******************************************************************

MidiFile* ScmNote::ReadScmSong( string filename )
{
	DEBUG_MSG( "Attempting to open file " << filename << " for reading.\n" );

	SCM scmFileName = scm_makfrom0str( filename.c_str() );
	SCM scmFileMode = scm_makfrom0str( "r" );

	SCM scmSong = scm_read( scm_open_file( scmFileName, scmFileMode ) );

	return ( ScmNote::ParseScmSong( scmSong ) );
}

//******************************************************************
// Protected Functions
//******************************************************************

MidiFile* ScmNote::ParseScmSong( SCM scmData )
{
	DEBUG_MSG( "Parsing song: \n" );

	scm_display( scmData, SCM_UNDEFINED );
	scm_newline( SCM_UNDEFINED );

	ScmSongStatus status;
	MidiFile* midifile = new MidiFile();
	status.dur = midifile->Get_TicksPerQuarter();
	
	TrackChunk* meta = new TrackChunk();
	TrackChunk* track = new TrackChunk();

	ParseScmItem( scmData, *meta, *track, status );

	midifile->AppendTrackChunk( meta );
	midifile->AppendTrackChunk( track );

	return ( midifile );
}

void ScmNote::ParseScmItem( SCM scmItem, TrackChunk& meta,
							TrackChunk& chunk, ScmSongStatus& status )
{
	DEBUG_MSG( "Parsing item: " );
	scm_display( scmItem, SCM_UNDEFINED );
	scm_newline( SCM_UNDEFINED );
	if ( scm_list_p( scmItem ) == SCM_BOOL_T)
	{
		DEBUG_MSG( "Its a list\n" );
		ParseScmListItem( scmItem, meta, chunk, status );
	}
	else
	{
		if ( scm_number_p( scmItem ) == SCM_BOOL_T )
		{
			DEBUG_MSG( "Its a number\n" );
			ParseScmNum( scmItem, meta, chunk, status );
		}
		else
		{
			DEBUG_MSG( "Its a symbol\n" );
			ParseScmSymbol( scmItem, meta, chunk, status );
		}
	}
}

void ScmNote::ParseScmSymbol( SCM scmItem, TrackChunk& meta,
							  TrackChunk& chunk, ScmSongStatus& status )
{
	//	SCM scmStringList = scm_string_to_list( scm_symbol_to_string( scmItem ) );
	string symString = SCM_CHARS( scmItem );
	DEBUG_MSG( "Parsing symbol with string: " << symString << endl );

	switch ( symString[0] ) 
	{
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
		ParseScmNoteSymbol( scmItem, meta, chunk, status );
	case 'r':
		//return ( ParseScmRestSymbol( scmItem, status ) );
		break;
	}
}

void ScmNote::ParseScmNum( SCM scmItem, TrackChunk& meta,
						   TrackChunk& track, ScmSongStatus& status )
{
}

void ScmNote::ParseScmListItem( SCM scmItem, TrackChunk& meta,
								TrackChunk& track, ScmSongStatus& status )
{
	DEBUG_MSG( "ParseScmListItem\n" );
	SCM scmListType = SCM_CAR( scmItem );

	if ( scm_equal_p( scmListType, scm_eval_0str( "'sim" ) ) == SCM_BOOL_T )
	{
		ParseScmMerger( scmItem, meta, track, status );
		return;
	}
	if ( (scm_equal_p( scmListType, scm_eval_0str("'velocity") ) == SCM_BOOL_T)
		 || (scm_equal_p( scmListType, scm_eval_0str("'vel") ) == SCM_BOOL_T))
	{
		DEBUG_MSG("ParseScmListItem: velocity change\n");
		status.velocity = ( scm_num2long( SCM_CADR(scmItem), 0,
										  "ParseScmListItem - velocity" ) );
		return;
	}
	
	if ( (scm_equal_p(scmListType, scm_eval_0str("'instrument")) == SCM_BOOL_T)
		 || (scm_equal_p( scmListType, scm_eval_0str("'inst") ) == SCM_BOOL_T))
	{
		DEBUG_MSG("ParseScmListItem: instrument change\n");
		ParseScmInstrumentChange( scmItem, meta, track, status );
		return;
	}
	
	if (scm_equal_p(scmListType, scm_eval_0str("'channels")) == SCM_BOOL_T)
	{
		DEBUG_MSG("ParseScmListItem: channels branching\n");
		ParseScmChannels( scmItem, meta, track, status );
		return;
	}

	if (scm_equal_p(scmListType, scm_eval_0str("'repeat")) == SCM_BOOL_T)
	{
		DEBUG_MSG("ParseScmListItem: repeater\n");
		ParseScmRepeat( scmItem, meta, track, status );
		return;
	}

	if (scm_equal_p(scmListType, scm_eval_0str("'tempo")) == SCM_BOOL_T)
	{
		DEBUG_MSG("ParseScmListItem: tempo\n");
		ParseScmTempo( scmItem, meta, track, status );
		return;
	}
	
	if ((scm_equal_p(scmListType, scm_eval_0str("'vol")) == SCM_BOOL_T)
		|| (scm_equal_p(scmListType, scm_eval_0str("'volume")) == SCM_BOOL_T))
	{
		DEBUG_MSG("ParseScmListItem: volume\n");
		ParseScmVolume( scmItem, meta, track, status );
		return;
	}
	
	if ((scm_equal_p(scmListType, scm_eval_0str("'duration")) == SCM_BOOL_T)
		|| (scm_equal_p(scmListType, scm_eval_0str("'dur")) == SCM_BOOL_T))
	{
		DEBUG_MSG("ParseScmListItem: dur\n");
		unsigned long topDuration = scm_num2long( SCM_CADR(scmItem), 0,
											   "ParseScmListitem - top" );
		unsigned long bottomDuration = scm_num2long( SCM_CADDR(scmItem), 0,
											   "ParseScmListitem - bottom" );
		status.dur = status.base_dur * topDuration / bottomDuration;
		return;
	}
	
	ParseScmListItemBody( scmItem, meta, track, status );
}

void ScmNote::ParseScmListItemBody( SCM scmItem, TrackChunk& meta,
									TrackChunk& track, ScmSongStatus& status )
{
	DEBUG_MSG( "ParseScmListItemBody\n" );
	
	for( SCM scmIter = scmItem;
		 scm_null_p( scmIter ) == SCM_BOOL_F; 
		 scmIter = SCM_CDR( scmIter ) )
	{
		SCM scmItem = SCM_CAR( scmIter );
		
		ParseScmItem( scmItem, meta, track, status );
	}
}
		 
void ScmNote::ParseScmMerger( SCM scmItem, TrackChunk& meta,
							  TrackChunk& track, ScmSongStatus& status )
{
	DEBUG_MSG( "ParseScmMerger\n" );
	// read all the tracks to be simultanized
	vector<TrackChunk> simulTracks;
	vector<TrackChunk> simulMeta;

	for ( SCM scmIter = SCM_CDR( scmItem );
		  scm_null_p( scmIter ) == SCM_BOOL_F; 
		  scmIter = SCM_CDR( scmIter ) )
	{
		TrackChunk newTrack;
		TrackChunk newMeta;

		ScmSongStatus local_status( status );

		SCM scmSimul = SCM_CAR( scmIter );
		
		ParseScmItem( scmSimul, newMeta, newTrack, status );

		DEBUG_MSG( "SubTrack read, with " << newTrack.Get_Items().size() 
				   << " items\n" );

		DEBUG_MSG( "aoeu: " 
				   << newTrack.Get_Items()[0]->Get_DeltaTime()->Get_Value()
				   << endl );

		simulTracks.push_back( newTrack );
		simulTracks.push_back( newMeta );
	}

	TrackChunk mergedTrack = MergeTracks( simulTracks );
	TrackChunk mergedMeta = MergeTracks( simulMeta );

	DEBUG_MSG( "Merger: mergedTrack contains "
			   << mergedTrack.Get_Items().size() << " items.\n" );
	
	for ( int i = 0; i < mergedTrack.Get_Items().size(); i++ )
	{
		track.Append( mergedTrack.Get_Items()[i] );
	}
		
	for ( int i = 0; i < mergedMeta.Get_Items().size(); i++ )
	{
		meta.Append( mergedMeta.Get_Items()[i] );
	}
}


void ScmNote::ParseScmNoteSymbol( SCM scmItem, TrackChunk& meta,
								  TrackChunk& chunk, ScmSongStatus& status )
{
	string symString = SCM_CHARS( scmItem );
	
	// These are the parameters to our shiznit
	unsigned int channel = status.channel;
	unsigned int velocity = status.velocity;
	char note = symString[0];
	unsigned int octave = status.prev_octave;
	VarInt duration = status.dur;
	int accidental = 0;

	// Figuring out the pitch class
	int i;
	i = 1;
	while ( ( i < symString.size() )
			&& ( (symString[i] == 'b')
				 || (symString[i] == '#') ) )
	{
		switch ( symString[i] )
		{
		case 'b':
			DEBUG_MSG( "accidental--\n" );
			accidental--; break;
		case '#':
			DEBUG_MSG( "accidental++\n" );
			accidental++; break;
		}
		i++;
	}

	// Determine the octave
	int startNum = i;
	while ( ( i < symString.size() )
			&& ( symString[i] >= '0' )
			&& ( symString[i] <= '9' ) )
	{
		i++;
	}
	
	if ( i > startNum )
	{
		octave = atol( symString.substr( startNum, i - startNum ).c_str() );
		DEBUG_MSG( "octave changed to: " << octave << endl );
		status.prev_octave = octave;
	}

	VarInt deltaOnTime = status.prev_dur;
	NoteMessage noteOnMsg( VOICE_Note_On,
						   status.channel,
						   note,
						   accidental,
						   octave,
						   velocity );
	chunk.Append( new MidiItem( deltaOnTime, noteOnMsg ) );

	// Setting up the note off event
	while ( ( i < symString.size() )
			&& ( symString[i] == 'o' ) )
	{
		duration += status.dur;
		DEBUG_MSG( "duration inc\n" );
		i++;
	}

	VarInt deltaOffTime = duration;
	status.meta_wait += duration.Get_Value();
	NoteMessage noteOffMsg( VOICE_Note_Off,
							status.channel,
							note,
							accidental,
							octave,
							velocity );

	DEBUG_MSG( "Delta time for note: " << deltaOffTime.Get_Value() << endl );
	
	chunk.Append( new MidiItem( deltaOffTime, noteOffMsg ) );
}

void ScmNote::ParseScmRestSymbol( SCM scmItem,
								  TrackChunk& meta,
								  TrackChunk& chunk,
								  ScmSongStatus& status )
{
	string symString = SCM_CHARS( scmItem );
	unsigned long int duration = status.dur;
	int i = 1;

	while ( ( i < symString.size() )
            && ( symString[i] == 'o' ) )
    {
        duration += status.dur;
        DEBUG_MSG( "rest duration inc\n" );
    }
	
	status.prev_dur = duration;
	status.meta_wait += duration;
}

void ScmNote::ParseScmInstrumentChange( SCM scmItem, TrackChunk& meta,
										TrackChunk& track, 
										ScmSongStatus& status )
{
	// TODO: write this, fucker
	long instrument = ( scm_num2long( SCM_CADR(scmItem), 0,
									  "ParseScmInstrumentChange - velocity"));
	long channel = status.channel;

	ProgramChangeMessage event( VOICE_Program_Change, channel, instrument );
	VarInt deltaTime = status.prev_dur;
	status.prev_dur = 0;

	track.Append( new MidiItem( deltaTime, event ) );
}

void ScmNote::ParseScmChannels( SCM scmItem, TrackChunk& meta,
								TrackChunk& track,
								ScmSongStatus& status )
{

	vector<TrackChunk> simulTracks;
	vector<TrackChunk> simulMeta;

	// each iteration parses one of the items and puts it on a new
	// channel.  Channels always start from 0 and are ignored after
	// 0x0f - but the loop doesn't terminate, so we can give diagnostic
	// errors
	
	int channel = 0;
	for ( SCM scmIter = SCM_CDR(scmItem);
		  scm_null_p( scmIter ) == SCM_BOOL_F;
		  scmIter = SCM_CDR( scmIter ), channel++ )
	{
		if ( channel <= 0x0F )
		{
			DEBUG_MSG( "Parsing track with channel=" << channel );

			SCM scmCurrent = SCM_CAR( scmIter );
			TrackChunk newTrack;
			TrackChunk newMeta;
			ScmSongStatus local_status( status );
			
			local_status.channel = channel;
			
			ParseScmItem( scmCurrent, newMeta, newTrack, local_status );
			
			simulTracks.push_back( newTrack );
			simulMeta.push_back( newMeta );
		}
		else
		{
			DEBUG_MSG( "Channel greater than 0x0F, ignoring!!" );
		}
	}
	
	TrackChunk mergedTrack = MergeTracks( simulTracks );
	TrackChunk mergedMeta = MergeTracks( simulMeta );
	
	DEBUG_MSG( "Channel: mergedTrack contains "
			   << mergedTrack.Get_Items().size() << " items.\n" );
	
	for ( int i = 0; i < mergedTrack.Get_Items().size(); i++ )
	{
		track.Append( mergedTrack.Get_Items()[i] );
	}
	for ( int i = 0; i < mergedMeta.Get_Items().size(); i++ )
	{
		meta.Append( mergedMeta.Get_Items()[i] );
	}
}

void ScmNote::ParseScmRepeat( SCM scmItem, TrackChunk& meta,
							  TrackChunk& track,
							  ScmSongStatus& status )
{
	unsigned long numRepeats = scm_num2long( SCM_CADR( scmItem ),
											 0,
											 "ParseScmRepeat - numRepeats" );
	
	for ( int i = 0; i < numRepeats; i++ )
	{
		ParseScmItem( SCM_CADDR( scmItem ), meta, track, status );
	}
	
}

void ScmNote::ParseScmTempo( SCM scmItem, TrackChunk& meta,
							 TrackChunk& track,
							 ScmSongStatus& status )
{
	unsigned long tempo = scm_num2long( SCM_CADR( scmItem ),
										0,
										"ParseScmTempo - tempo" );
	
	VarInt delta = status.meta_wait;
	TempoEvent event( tempo );
	
	meta.Append( new MidiItem( delta, event ) );

	status.meta_wait = 0;
}

void ScmNote::ParseScmVolume( SCM scmItem, TrackChunk& meta,
							  TrackChunk& track,
							  ScmSongStatus& status )
{
	unsigned long volume = scm_num2long( SCM_CADR( scmItem ),
										 0,
										 "ParseScmVolume - volume" );
	
	VarInt delta = status.prev_dur;
	ControllerChange event( status.channel,
							CONTROLLER_Channel_Volume, 
							(unsigned int)volume );
	
	meta.Append( new MidiItem( delta, event ) );

	status.prev_dur = 0;
}

TrackChunk& ScmNote::MergeTracks( vector<TrackChunk> simulTracks )
	{
	TrackChunk* mergedTrack = new TrackChunk();
	// INCREDIBLY INNEFFICENT IMPLEMENTATION:                                   
    DEBUG_MSG( "Merging " << simulTracks.size() << " tracks\n" );
	
    vector< unsigned int > indices( simulTracks.size() );
    bool moreEvents = false;
	
    for ( int i = 0; i < simulTracks.size(); i++ )
    {
        indices[i] = 0;
        if ( simulTracks[i].Get_Items().size() > 0 )
            moreEvents = true;
    }
	
    while ( moreEvents )
    {
        int minIndex = 0;
        unsigned long int minDeltaTime = UINT_MAX;
        for ( int i = 0; i < indices.size(); i++ )
        {
            vector<MidiItem*> items = simulTracks[i].Get_Items();
            if ( (indices[i] < simulTracks[i].Get_Items().size())
                 && (items[ indices[i] ]->Get_DeltaTime()->Get_Value()
                     < minDeltaTime) )
            {
				//                DEBUG_MSG( "Grabbing minDeltaTime: " <<
                //           items[ indices[i] ]->Get_DeltaTime()->Get_Value()
                //           << " and minIndex=" << i << endl );
				
                minDeltaTime =
                    items[ indices[i] ]->Get_DeltaTime()->Get_Value();

                minIndex = i;
            }
        }

		//        DEBUG_MSG( "Chose minIndex " << minIndex << endl );
		//        DEBUG_MSG( "Reducing delta times by " << minDeltaTime << endl );
		
        mergedTrack->Append( new
							 MidiItem( *simulTracks[minIndex].Get_Items()[ indices[minIndex] ] ) );
		
        for ( int i = 0; i < indices.size(); i++ )
        {
            if ( (indices[i] < simulTracks[i].Get_Items().size() ) )
            {
                MidiItem* curr = simulTracks[i].Get_Items()[indices[i]];
                curr->Set_DeltaTime( curr->Get_DeltaTime()->Get_Value()
                                     - minDeltaTime );
            }
        }

        indices[minIndex]++;

		
        moreEvents = false;
        for ( int i = 0; !moreEvents && (i < simulTracks.size()); i++ )
        {
            if ( indices[i] < simulTracks[i].Get_Items().size() )
                moreEvents = true;
        }
		
    }
	
	DEBUG_MSG( "Merged tracks contain " << mergedTrack->Get_Items().size()
			   << " items.\n" );
	return ( *mergedTrack );
	
}
