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

#ifndef SCMNOTE_DEBUG_H
#define SCMNOTE_DEBUG_H

#include <iostream>
#include <string>

namespace scmnote {
	
#ifdef DEBUG_SCMNOTE

#define DEBUG_MSG(outputstream) \
    cerr << "debug: " << outputstream; \
	
#define FIXME(msg) \
	cerr << "fixme: " << msg; \

#else

#define DEBUG_MSG(outputstream) ;

#define FIXME(msg) ;

#endif

} // namespace
#endif
