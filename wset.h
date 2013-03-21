#ifndef OCPA4_WSET_H
#define OCPA4_WSET_H

#define WSET_MAX 15
#define WSET_FREQ_WIN 100 /* ticks */

typedef struct wset {
	/* the number of pages allocated
	 * to this process */
	size_t size;
	/* frequency of faults per WSET_FREQ_TICKS.
	 * increment */
	int freq; 
} wset_t;
#endif