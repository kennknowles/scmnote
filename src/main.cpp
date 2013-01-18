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

#include <string>
#include <iostream>
#include <fstream>
#include <libguile.h>

#include "ScmNote.hpp"
#include "MidiFile.hpp"
#include "cmdline.h"
#include "debug.hpp"

using namespace scmnote;

void main_func( void* closure, int argc, char* argv[] )
{

	cerr.setf( ios::unitbuf );
	cout.setf( ios::unitbuf );

	ostream* outstream;
	string outFilename;
	string inFilename;
	
	gengetopt_args_info args_info;
	
	if ( cmdline_parser( argc, argv, &args_info ) != 0 )
		exit(1);

	if ( args_info.inputs_num != 1 )
	{
		cerr << "Must supply exactly 1 filename\n";
		cmdline_parser_print_help();
		exit(1);
	}

	inFilename = args_info.inputs[0];

	if ( args_info.stdout_given )
	{
		if ( args_info.out_file_given )
		{
			cerr << "Cannot specify both -s and -o\n";
		}
		else
		{
			outstream = &cout;
		}
	}
	else
	{
		if ( args_info.out_file_given )
		{
			outFilename = args_info.out_file_arg;
		}
		else
		{
			DEBUG_MSG( "infile is " << inFilename << endl );
			int lastSlash = inFilename.rfind("/");
			if ( lastSlash < 0 )
			{
				lastSlash = -1;
				DEBUG_MSG( "No slash found" );
			}
			else
			{
				DEBUG_MSG( "Slash found at position " << lastSlash << endl );
			}

			string inFileprefix = inFilename.substr( lastSlash+1,
													 inFilename.rfind(".") 
													 - lastSlash - 1);
			outFilename = inFileprefix + ".mid";
			DEBUG_MSG( "outfile is " << outFilename<< "\n" );
		}
		
		outstream = new ofstream( outFilename.c_str(), ios::out );
	}

	DEBUG_MSG( "...?\n" );

	MidiFile* midiFile = ScmNote::ReadScmSong( inFilename ); 

	DEBUG_MSG( "...!\n" );


	midiFile->Emit( *outstream );
}


int main( int argc, char* argv[] )
{
	scm_boot_guile( argc, argv, main_func, 0 );
}


/*




#include <iostream>
#include <fstream>


void write16( ostream& outfile, long val )
{
	outfile.put( (val & 0xFF00) >> 8 );
	outfile.put( val & 0x00FF );
}


void write32( ostream& outfile, long val )
{
	write16( outfile, (val & 0xFFFF0000) >> 16 );
	write16( outfile, val & 0x0000FFFF );
}



void headerChunk( ostream& outfile )
{
	// output type "MThd"
	// we don't want trailing 0's in these files!!
	outfile << "MThd";

	// The length of the header chunk, a 32 bit number, value always 6
	write32( outfile, 6 );

	// Format of file, 16 bits
	// For this program, always 0 (one track)
	write16( outfile, 0 );
	
	//Number of tracks, always one for format zero
	write16( outfile, 1 );
	
	//Default division... MSB 0 -> tick per quarter note in the other 15 bits
	// This should be 1 second per quarter note
	write16( outfile, 120 );
}

void trackChunk( ostream& outfile )
{
	// type "MTrk"
	outfile << "MTrk";
	
	// length in bytes... will calculate later :)
	// 
	write32( outfile, 8 );

	// 4 bytes for each event = 8
	// delta time of 0;
	outfile.put( 0 );

	// note on event
	// 9 is required, 0 is the track number
	outfile.put( 0x90 );
	
	// key which was pressed, 3c = middle c
	outfile.put( 0x3c );

	// velocity, 40 = mezzo forte according to the docs
	outfile.put( 0x40 );



	// delta time of 100;
	outfile.put( 120 );
	
	// note off event
	// id number 8, track 0
	outfile.put( 0x80 );
 
	// key
	outfile.put( 0x3c );

	// release velocity, 40 = default for insensitive stuff
	outfile.put( 0x40 );
}

int main( int argc, char* argv[] )
{
	ostream* outfile = &cout;
	
	headerChunk( *outfile );
	trackChunk( *outfile );
}

*/
