# algore
Automatically exported from code.google.com/p/algore

AL Gore Library
Author: Herb Gilliland

Tasty C++ class wrappers and mixer implementation for OpenAL built on Chris Robinson's ALURE library. Comes with some crunky LinkedList and ListItem classes which you are welcome to use or change.

Use with ALURE, OpenAL, libsndfile / libFLAC etc. Provides a simple and effective programmer interface to easily deal with the ALURE libraries and implements ALURE on Windows and Linux. Effectively uses both the one-off and streaming capabilities of OpenAL/ALURE and via libsndfile libflac et al supports a wide variety of sound file formats.

 #include <Windows.h>
 #include "Audio.h"

 Audio mixer; // Initializes our audio manager

 ALSound *s;

 audio.Load( "godspeed.wav" );
 audio.Load( "sounds/hello.wav" );
 audio.manager.CueAndPlay( "sounds/hello.wav", 1.0f, 1.0f, false, true );
 s=audio.manager.Cue( "sounds/hello.wav", 1.0f, 1.0f, false, true );
 s->Play();

 ALUREStream *streaming=audio.manager.AddStream("afilebiggerthan2mb.flac",null,0,false);
 streaming->Play();

 // Updated on a timer...
 SoundSequencer sequencer;
 SoundEvent event;

 sequencer.audio=&mixer;

 event=new SoundEvent;
 event.stream=audio.manager.AddStream("sounds/spoken/golden.wav",null,0,false); 
 event.delay=0.75f;
 sequencer.events.sounds.Add(event);

 // During timed loop:
 ... 
 sequencer.Update( deltaSecondsf );
Coming soon:

Full EAX/EFX support
Verified capturing features
Speex integration with networked audio support (TeamSpeak?)
Integrated 3D sourcing (currently supports 3D audio sourcing, but needs more controller objects)
