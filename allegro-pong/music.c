#include "pong_header.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

#define SONG "res/lines_of_code.wav"

static ALLEGRO_SAMPLE *sample=NULL;

void audio_init() {
	if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      exit(-1);
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      exit(-1);
   }

	if (!al_reserve_samples(1)){
		fprintf(stderr, "failed to reserve samples!\n");
		exit(-1);
	}

	sample = al_load_sample(SONG);
	if (!sample) {
		printf( "Audio clip sample not loaded!\n" ); 
      exit(-1);
	}
}

void play_music() {
	al_play_sample(sample, 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}

void audio_destroy() {
	al_destroy_sample(sample);
}
