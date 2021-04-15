
/*
 *
 * sound.h
 * Created on the 23rd of August 2005
 *
 * Part of the OpenJazz project
 *
 *
 * Copyright (c) 2005 Alister Thomson
 * Dreamcast code by Troy(GPF)
 *
 * OpenJazz is distributed under the terms of
 * the GNU General Public License, version 2.0
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/*
 * Deals with the loading, playing and freeing of music and sound effects.
 *
 */


#include "OpenJazz.h"
#include <string.h>
#include "SDL_mixer.h"
 Mix_Music *music;

#define CHUNK_NUM 6 


int useAudio = 0;

static char *chunkFileName[CHUNK_NUM] = {
  "shot.wav", "jump.wav", "pickup.wav", "hurt.wav", "spring.wav" , "yam.wav",
};
static Mix_Chunk *chunk[CHUNK_NUM];
static int chunkFlag[CHUNK_NUM];

void closeSound() {
  int i;
  if ( !useAudio ) return;
  if ( Mix_PlayingMusic() ) {
    Mix_HaltMusic();
  }
  for ( i=0 ; i<CHUNK_NUM ; i++ ) {
    if ( chunk[i] ) {
      Mix_FreeChunk(chunk[i]);
    }
  }
  Mix_CloseAudio();
}


static void loadSounds() {
  int i;
  char name[52];
 for ( i=0 ; i<CHUNK_NUM ; i++ ) {
    strcpy(name, chunkFileName[i]);
    if ( NULL == (chunk[i] = Mix_LoadWAV(name)) ) {
      printf("Couldn't load: %s\n", name);
      useAudio = 0;
      return;
    }
    chunkFlag[i] = 0;
  }
}



void initSound() {
  int audio_rate;
  Uint16 audio_format;
  int audio_channels;
  int audio_buffers;

  if ( SDL_InitSubSystem(SDL_INIT_AUDIO) < 0 ) {
    printf( "Unable to initialize SDL_AUDIO: %s\n", SDL_GetError());
    return;
  }

  audio_rate = 44100;
  audio_format = AUDIO_S16;
  audio_channels = 2;
  audio_buffers = 1024;

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
    printf( "Couldn't open audio: %s\n", SDL_GetError());
    return;
  } else {
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  }

 useAudio = 1;
 loadSounds();

}


int loadMusic (char * fn) {
	if (useAudio==1) {
	// substitute psm with s3m in the file name
	int len;
	char file[100];
	strcpy(file,fn);
	len=strlen(file);
	if (len>4) {
		file[len-1]='m';
		file[len-2]='3';
		file[len-3]='s';
	}
 	 if ( NULL == (music = Mix_LoadMUS(file)) ) {
		printf("loadMusic:::Could not load: %s\n",file);
		return FAILURE;	
	}

	Mix_PlayMusic(music, -1);
}
  return SUCCESS;
}


void freeMusic (void) {

#ifdef USE_MODPLUG

  SDL_CloseAudio();

  ModPlug_Unload(musicFile);
  free(psmData);

#endif

  return;

}




void freeSounds (void) {

  // To do

  return;

}


void playSound (int sound) {
 if ( !useAudio ) return;
  Mix_PlayChannel(-1, chunk[sound], 0);

  return;

}

