/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef USERSPACE_LIB_SOUND_H_
#define USERSPACE_LIB_SOUND_H_

#include <libc/stdint.h>

#define SND_MAX_KNOBS 256
#define SND_KNOB_NAME_SIZE 256
#define SND_KNOB_MAX_VALUE UINT32_MAX

#define SND_KNOB_MASTER 0
#define SND_DEVICE_MAIN 0

typedef struct snd_knob_list {
	uint32_t device;              /* IN */
	uint32_t num;                 /* OUT */
	uint32_t ids[SND_MAX_KNOBS];  /* OUT */
} snd_knob_list_t;

typedef struct snd_knob_info {
	uint32_t device;               /* IN */
	uint32_t id;                   /* IN */
	char name[SND_KNOB_NAME_SIZE]; /* OUT */
} snd_knob_info_t;

typedef struct snd_knob_value {
	uint32_t device; /* IN */
	uint32_t id;     /* IN */
	uint32_t val;    /* OUT for SND_MIXER_READ_KNOB, IN for SND_MIXER_WRITE_KNOB */
} snd_knob_value_t;


/* IOCTLs */
#define SND_MIXER_GET_KNOBS 0
#define SND_MIXER_GET_KNOB_INFO  1
#define SND_MIXER_READ_KNOB 2
#define SND_MIXER_WRITE_KNOB 3

#endif /* USERSPACE_LIB_SOUND_H_ */
