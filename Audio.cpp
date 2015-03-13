/***********************************************************************************************
 * AL Gore Library: An MSVC++ class implementation that wraps OpenAL and ALURE using other libs*
 ***********************************************************************************************
 * This file is distributed under the Revised BSD License, also known as the "New" BSD License *
 * See the text of the "New BSD License" for rules about using this file in your project.      *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/

#include <Windows.h>
#include "Audio.h"

void OUTPUT(char * fmt, ...)
{
 char buf [32768];
 va_list args;
 va_start (args, fmt);
 vsprintf_s (buf, fmt, args);
 va_end (args);
 OutputDebugString(TEXT(buf));
}

/*
 * Compare strings, case insensitive.
 */
#define LOWER(c) ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
bool contains( const char *astr, const char *bstr )
{
 if ( astr == null ) { OUTPUT( "Str_cmp: null astr.\n" ); return false; }
 if ( bstr == null ) { OUTPUT( "Str_cmp: null bstr.\n" ); return false; }
 for ( ; *astr || *bstr; astr++, bstr++ ) if ( LOWER(*astr) != LOWER(*bstr) ) return false;
 return true;
}

// Used during Init(), maybe it shouldn't die() here...
void checkForErrors(void)
{
 ALCdevice *device = alcGetContextsDevice(alcGetCurrentContext());
 ALCenum ALCerror = alcGetError(device);
 ALenum ALerror;
 if(ALCerror != ALC_NO_ERROR) OUTPUT( "ALC %s\n",  alcGetString(device, ALCerror));
 ALerror = alGetError();
 if(ALerror != AL_NO_ERROR) OUTPUT("AL %s\n", alGetString(ALerror));
}

void printChar(int c, int *width) { OUTPUT("%c",c); *width = ((c == '\n') ? 0 : ((*width) + 1)); }
void indent(int *width) { int i; for(i = 0; i < indentation; i++) printChar(' ', width); }

void printList(const char *header, char separator, const char *list)
{
    int width = 0, start = 0, end = 0;
    OUTPUT("%s:\n", header);
    if(list == NULL || list[0] == '\0') return;
    indent(&width);
    while(1)    {
        if(list[end] == separator || list[end] == '\0')        {
            if(width + end - start + 2 > maxmimumWidth)            {
                printChar('\n', &width);
                indent(&width);
            }
            while(start < end)            {
                printChar(list[start], &width);
                start++;
            }
            if(list[end] == '\0')                break;
            start++;
            end++;
            if(list[end] == '\0')                break;
            printChar(',', &width);
            printChar(' ', &width);
        }
        end++;
    }
    printChar('\n', &width);
}

//int unusedBuffers, unusedSources;

void GetALCErrorString(ALenum err){
 switch(err) {
  case ALC_NO_ERROR: OUTPUT("AL_NO_ERROR"); break;
  case ALC_INVALID_DEVICE: OUTPUT("ALC_INVALID_DEVICE"); break;
  case ALC_INVALID_CONTEXT: OUTPUT("ALC_INVALID_CONTEXT"); break;
  case ALC_INVALID_ENUM: OUTPUT("ALC_INVALID_ENUM"); break;
  case ALC_INVALID_VALUE: OUTPUT("ALC_INVALID_VALUE"); break;
  case ALC_OUT_OF_MEMORY: OUTPUT("ALC_OUT_OF_MEMORY"); break;
 }
}

bool ALError( char *tb ) {
 ALenum errCode;
 if ( ( errCode = alGetError() ) != AL_NO_ERROR )  {
  OUTPUT( "Audio %s Error #%d %s\n", tb, errCode, (char *) alGetString( errCode ) );
  return true;
 }
 return false;
}



void ALSource::bindBuffer( ALBuffer buffer ) {
 alGetError();
 alSourcei (id, AL_BUFFER,   buffer.id );
 alSourcef (id, AL_PITCH,    pitch  );
 alSourcef (id, AL_GAIN,     gain   );
 alSourcefv(id, AL_POSITION, position.asFloat3() );
 alSourcefv(id, AL_VELOCITY, velocity.asFloat3() );
 alSourcef (id, AL_ROLLOFF_FACTOR, rolloff );
 alSourcei (id, AL_LOOPING,  loop   );
 alSourcei (id, AL_SOURCE_RELATIVE, relative );
 ALError("ALSource:bindBuffer() had an error");
 state=stopped;
}

void ALSource::bindSound( ALSound *sound ) {
 alGetError();
 alSourcei (id, AL_BUFFER,   sound->waveform->buffer.id );
 alSourcef (id, AL_PITCH,    sound->pitch  );
 alSourcef (id, AL_GAIN,     sound->gain   );
 alSourcefv(id, AL_POSITION, sound->position.asFloat3() );
 alSourcefv(id, AL_VELOCITY, sound->velocity.asFloat3() );
 alSourcef (id, AL_ROLLOFF_FACTOR, rolloff );
 alSourcei (id, AL_LOOPING,  sound->loop   );
 alSourcei (id, AL_SOURCE_RELATIVE, sound->relative );
 ALError("ALSource:bindSound() had an error");
 state=stopped;
}

void ALSource::bindStream( ALUREStream *stream ) {
 alGetError();
 alSourcef (id, AL_PITCH,    pitch  );
 alSourcef (id, AL_GAIN,     gain   );
 alSourcefv(id, AL_POSITION, position.asFloat3() );
 alSourcefv(id, AL_VELOCITY, velocity.asFloat3() );
 alSourcef (id, AL_ROLLOFF_FACTOR, rolloff );
 alSourcei (id, AL_LOOPING,  AL_FALSE   ); // handled elsewhere
 alSourcei (id, AL_SOURCE_RELATIVE, relative );
 stream->source=this;
 ALError("ALSource:bindStream() had an error");
 state=stopped;
}

