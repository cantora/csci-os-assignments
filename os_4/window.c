#include "window.h"
#include <assert.h>

#define WSIZE (1 << 13)

static int window[WSIZE];

#define PLUS_ONE(_element) ( (_element < (WSIZE-1) )? (_element+1) : 0)
#define MINUS_ONE(_element) ( (_element == 0 )? (WSIZE-1) : (_element-1) )

static void inc_head(struct phist *ph) {
	int tmp;

	tmp = HPLUS_ONE(ph->head);
	if(tmp == ph->tail)
		ph->tail = HPLUS_ONE(ph->tail);

	ph->head = tmp;
}

void phist_init(struct phist *ph) {
	ph->head = 0;
	ph->tail = 0;
}

void phist_push(struct phist *ph, const struct phist_record *ph_r) {
	ph->records[ph->head] = *ph_r;
	inc_head(ph);
}

void phist_len(struct phist *ph, int *len) {
	int tmp;

	tmp = HPLUS_ONE(ph->head);
	if(tmp == ph->tail)
		*len = WSIZE;
	else
		*len = (ph->head - ph->tail) + 1;
}

void phist_at(struct phist *ph, int t, struct phist_record *ph_r) {
	int len, i, ptr;
	
	phist_len(ph, &len);
	assert(t >= 0 && t < len);

	ptr = ph->head;
	for(i = 0; i < t; i++) {
		ptr = HMINUS_ONE(ptr);
	}

	*ph_r = ph->records[ptr];
}

void phist_fault_sum(struct phist *ph, int *sum) {
	int ptr;

	*sum = 0;
	ptr = ph->tail;
	do {
		*sum += (ph->records[ptr].fault == 1);
	} while( (ptr = HPLUS_ONE(ptr)) != ph->head );
}