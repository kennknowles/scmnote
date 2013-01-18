bin_PROGRAMS = scmnote

main_body = \
	main.cpp \
	scmnote.ggo \
	output.hpp \
	output.cpp

scmnote_SOURCES = \
	main.cpp \
	scmnote.ggo \
	output.hpp \
	output.cpp \
	debug.hpp \
	cmdline.h \
	cmdline.c \
	ScmNote.hpp \
	ScmNote.cpp \
	ScmSongStatus.hpp \
	ScmSongStatus.cpp \
	MidiFile.hpp \
	MidiFile.cpp \
	MidiChunk.hpp \
	TrackChunk.hpp \
	TrackChunk.cpp \
	MidiItem.hpp \
	MidiItem.cpp \
	MidiEvent.hpp \
	MetaEvent.hpp \
	VarInt.hpp \
	VarInt.cpp \
	ChannelMessage.hpp \
	ChannelVoiceMessage.hpp \
	NoteMessage.hpp \
	NoteMessage.cpp \
	ProgramChangeMessage.hpp \
	ProgramChangeMessage.cpp \
	TextMetaEvent.hpp \
	TextMetaEvent.cpp \
	EndOfTrackEvent.hpp \
	EndOfTrackEvent.cpp \
	TempoEvent.hpp \
	TempoEvent.cpp \
	ControllerChange.hpp \
	ControllerChange.cpp \
	EnumModeMessage.hpp \
	EnumVoiceMessage.hpp \
	EnumMidiFormat.hpp \
	EnumMetaEvent.hpp \
	EnumSysexEvent.hpp \
	EnumDivType.hpp \
	EnumController.hpp \
	HasChannel.hpp

INCLUDES = -DDEBUG_SCMNOTE -Werror -ansi -pedantic \
	-DDATADIR=\"$(pkgdatadir)\" \
	-DCONFDIR=\"$(sysconfdir)\"

cmdline.c cmdline.h : scmnote.ggo
	gengetopt < scmnote.ggo --unamed-opts
