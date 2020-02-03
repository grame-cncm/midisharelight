/*
  MidiShareLight Project
  Copyright (C) Grame 2020

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#pragma once

#include <mutex>

typedef struct lifocell {
	struct lifocell* volatile link;	/* next cell in the list */
	long value[3];			/* any data here		 */
} lifocell;

struct lifo {
	lifocell *  top;	/* top of the stack          */
	long	count;
	std::mutex mtx;
};
typedef struct lifo lifo;


#ifdef __cplusplus
extern "C" {
#endif

 void          lifoinit  (lifo* lf);
 void          lifopush  (lifo * lf, lifocell * cl);
 lifocell*     lifopop   (lifo * lf);

#ifdef __cplusplus
}
#endif


static inline lifocell* lifoavail(lifo* lf) 		{ return (lifocell*)lf->top; }
static inline long 		lifosize (const lifo * lf) 	{ return lf->count; }
