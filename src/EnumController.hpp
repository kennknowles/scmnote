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

#ifndef SCMNOTE_ENUM_CONTROLLER_HPP
#define SCMNOTE_ENUM_CONTROLLER_HPP

namespace scmnote
{
	enum EnumController
	{
		CONTROLLER_Bank_Select_MSB,
		CONTROLLER_Bank_Select_LSB,
		CONTROLLER_Modulation_Wheel,
		CONTROLLER_Breath_Controller,
		CONTROLLER_Foot_Controller,
		CONTROLLER_Portamento_Time,
		CONTROLLER_Data_Entry_MSB,
		CONTROLLER_Channel_Volume,
		CONTROLLER_Balance,
		CONTROLLER_Pan,
		CONTROLLER_Expression_Controller,
		CONTROLLER_Effect_Control_1,
		CONTROLLER_Effect_Control_2,
		CONTROLLER_General_Purpose_Controller_1,
		CONTROLLER_General_Purpose_Controller_2,
		CONTROLLER_General_Purpose_Controller_3,
		CONTROLLER_General_Purpose_Controller_4,
		CONTROLLER_LSB, // for all the controllers preceding this one
		CONTROLLER_Damper_Pedal, 
		CONTROLLER_Portamento_On_Off,
		CONTROLLER_Sostenuto,
		CONTROLLER_Soft_Pedal,
		CONTROLLER_Legato_Footswitch,
		CONTROLLER_Hold_2  ,
		CONTROLLER_Sound_Controller_1, // this should go up to 10
		CONTROLLER_General_Purpose_Controller_5, // through 8
		CONTROLLER_Portamento_Control 
	};
}

#endif
