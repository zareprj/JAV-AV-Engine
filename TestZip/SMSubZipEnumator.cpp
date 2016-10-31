
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "SMSubZipEnumator.h"


const UINT32 crc_table[256] = {
	0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
	0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
	0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
	0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
	0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
	0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
	0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
	0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
	0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
	0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
	0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
	0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
	0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
	0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
	0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
	0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
	0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
	0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
	0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
	0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
	0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
	0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
	0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
	0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
	0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
	0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
	0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
	0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
	0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
	0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
	0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
	0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
	0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
	0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
	0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
	0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
	0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
	0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
	0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
	0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
	0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
	0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
	0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
	0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
	0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
	0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
	0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
	0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
	0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
	0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
	0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
	0x2d02ef8dL
};

// ===========================================================================
// Local (static) routines in this file.
//

#define send_code(state, c, tree) send_bits(state, tree[c].fc.code, tree[c].dl.len)
// Send a code of the given tree. c and tree must not have side effects

// alternatively...
//#define send_code(state, c, tree)
//     { if (state.verbose>1) fprintf(stderr,"\ncd %3d ",(c));
//       send_bits(state, tree[c].fc.code, tree[c].dl.len); }

#define d_code(dist) ((dist) < 256 ? state.ts.dist_code[dist] : state.ts.dist_code[256+((dist)>>7)])
// Mapping from a distance to a distance code. dist is the distance - 1 and
// must not have side effects. dist_code[256] and dist_code[257] are never used.

#define Max(a,b) (a >= b ? a : b)
/* the arguments must not have side effects */

/* ===========================================================================
* Allocate the match buffer, initialize the various tables and save the
* location of the internal file attribute (ascii/binary) and method
* (DEFLATE/STORE).
*/
void SubZipEnumator::ct_init(TState &state, UINT16 *attr)
{
	int n;        /* iterates over tree elements */
	int bits;     /* bit counter */
	int length;   /* length value */
	int code;     /* code value */
	int dist;     /* distance index */

	state.ts.file_type = attr;
	//state.ts.file_method = method;
	state.ts.cmpr_bytelen = state.ts.cmpr_len_bits = 0L;
	state.ts.input_len = 0L;

	if (state.ts.static_dtree[0].dl.len != 0) return; /* ct_init already called */

	/* Initialize the mapping length (0..255) -> length code (0..28) */
	length = 0;
	for (code = 0; code < LENGTH_CODES-1; code++) {
		state.ts.base_length[code] = length;
		for (n = 0; n < (1<<extra_lbits[code]); n++) {
			state.ts.length_code[length++] = (UINT8)code;
		}
	}
	//Assert(state,length == 256, "ct_init: length != 256");
	/* Note that the length 255 (match length 258) can be represented
	* in two different ways: code 284 + 5 bits or code 285, so we
	* overwrite length_code[255] to use the best encoding:
	*/
	state.ts.length_code[length-1] = (UINT8)code;

	/* Initialize the mapping dist (0..32K) -> dist code (0..29) */
	dist = 0;
	for (code = 0 ; code < 16; code++) {
		state.ts.base_dist[code] = dist;
		for (n = 0; n < (1<<extra_dbits[code]); n++) {
			state.ts.dist_code[dist++] = (UINT8)code;
		}
	}
	//Assert(state,dist == 256, "ct_init: dist != 256");
	dist >>= 7; /* from now on, all distances are divided by 128 */
	for ( ; code < D_CODES; code++) {
		state.ts.base_dist[code] = dist << 7;
		for (n = 0; n < (1<<(extra_dbits[code]-7)); n++) {
			state.ts.dist_code[256 + dist++] = (UINT8)code;
		}
	}
	//Assert(state,dist == 256, "ct_init: 256+dist != 512");

	/* Construct the codes of the static literal tree */
	for (bits = 0; bits <= MAX_BITS; bits++) state.ts.bl_count[bits] = 0;
	n = 0;
	while (n <= 143) state.ts.static_ltree[n++].dl.len = 8, state.ts.bl_count[8]++;
	while (n <= 255) state.ts.static_ltree[n++].dl.len = 9, state.ts.bl_count[9]++;
	while (n <= 279) state.ts.static_ltree[n++].dl.len = 7, state.ts.bl_count[7]++;
	while (n <= 287) state.ts.static_ltree[n++].dl.len = 8, state.ts.bl_count[8]++;
	/* fc.codes 286 and 287 do not exist, but we must include them in the
	* tree construction to get a canonical Huffman tree (longest code
	* all ones)
	*/
	gen_codes(state,(ct_data *)state.ts.static_ltree, L_CODES+1);

	/* The static distance tree is trivial: */
	for (n = 0; n < D_CODES; n++) {
		state.ts.static_dtree[n].dl.len = 5;
		state.ts.static_dtree[n].fc.code = (UINT16)bi_reverse(n, 5);
	}

	/* Initialize the first block of the first file: */
	init_block(state);
}

/* ===========================================================================
* Initialize a new block.
*/
void SubZipEnumator::init_block(TState &state)
{
	int n; /* iterates over tree elements */

	/* Initialize the trees. */
	for (n = 0; n < L_CODES;  n++) state.ts.dyn_ltree[n].fc.freq = 0;
	for (n = 0; n < D_CODES;  n++) state.ts.dyn_dtree[n].fc.freq = 0;
	for (n = 0; n < BL_CODES; n++) state.ts.bl_tree[n].fc.freq = 0;

	state.ts.dyn_ltree[END_BLOCK].fc.freq = 1;
	state.ts.opt_len = state.ts.static_len = 0L;
	state.ts.last_lit = state.ts.last_dist = state.ts.last_flags = 0;
	state.ts.flags = 0; state.ts.flag_bit = 1;
}

#define SMALLEST 1
/* Index within the heap array of least frequent node in the Huffman tree */


/* ===========================================================================
* Remove the smallest element from the heap and recreate the heap with
* one less element. Updates heap and heap_len.
*/
#define pqremove(tree, top) \
{\
	top = state.ts.heap[SMALLEST]; \
	state.ts.heap[SMALLEST] = state.ts.heap[state.ts.heap_len--]; \
	pqdownheap(state,tree, SMALLEST); \
}

/* ===========================================================================
* Compares to subtrees, using the tree depth as tie breaker when
* the subtrees have equal frequency. This minimizes the worst case length.
*/
#define smaller(tree, n, m) \
	(tree[n].fc.freq < tree[m].fc.freq || \
	(tree[n].fc.freq == tree[m].fc.freq && state.ts.depth[n] <= state.ts.depth[m]))

/* ===========================================================================
* Restore the heap property by moving down the tree starting at node k,
* exchanging a node with the smallest of its two sons if necessary, stopping
* when the heap property is re-established (each father smaller than its
* two sons).
*/
void SubZipEnumator::pqdownheap(TState &state,ct_data *tree, int k)
{
	int v = state.ts.heap[k];
	int j = k << 1;  /* left son of k */
	int htemp;       /* required because of bug in SASC compiler */

	while (j <= state.ts.heap_len) {
		/* Set j to the smallest of the two sons: */
		if (j < state.ts.heap_len && smaller(tree, state.ts.heap[j+1], state.ts.heap[j])) j++;

		/* Exit if v is smaller than both sons */
		htemp = state.ts.heap[j];
		if (smaller(tree, v, htemp)) break;

		/* Exchange v with the smallest son */
		state.ts.heap[k] = htemp;
		k = j;

		/* And continue down the tree, setting j to the left son of k */
		j <<= 1;
	}
	state.ts.heap[k] = v;
}

/* ===========================================================================
* Compute the optimal bit lengths for a tree and update the total bit length
* for the current block.
* IN assertion: the fields freq and dad are set, heap[heap_max] and
*    above are the tree nodes sorted by increasing frequency.
* OUT assertions: the field len is set to the optimal bit length, the
*     array bl_count contains the frequencies for each bit length.
*     The length opt_len is updated; static_len is also updated if stree is
*     not null.
*/
void SubZipEnumator::gen_bitlen(TState &state,tree_desc *desc)
{
	ct_data *tree  = desc->dyn_tree;
	const int *extra     = desc->extra_bits;
	int base            = desc->extra_base;
	int max_code        = desc->max_code;
	int max_length      = desc->max_length;
	ct_data *stree = desc->static_tree;
	int h;              /* heap index */
	int n, m;           /* iterate over the tree elements */
	int bits;           /* bit length */
	int xbits;          /* extra bits */
	UINT16 f;              /* frequency */
	int overflow = 0;   /* number of elements with bit length too large */

	for (bits = 0; bits <= MAX_BITS; bits++) state.ts.bl_count[bits] = 0;

	/* In a first pass, compute the optimal bit lengths (which may
	* overflow in the case of the bit length tree).
	*/
	tree[state.ts.heap[state.ts.heap_max]].dl.len = 0; /* root of the heap */

	for (h = state.ts.heap_max+1; h < HEAP_SIZE; h++) {
		n = state.ts.heap[h];
		bits = tree[tree[n].dl.dad].dl.len + 1;
		if (bits > max_length) bits = max_length, overflow++;
		tree[n].dl.len = (UINT16)bits;
		/* We overwrite tree[n].dl.dad which is no longer needed */

		if (n > max_code) continue; /* not a leaf node */

		state.ts.bl_count[bits]++;
		xbits = 0;
		if (n >= base) xbits = extra[n-base];
		f = tree[n].fc.freq;
		state.ts.opt_len += (UINT32)f * (bits + xbits);
		if (stree) state.ts.static_len += (UINT32)f * (stree[n].dl.len + xbits);
	}
	if (overflow == 0) return;

	//Trace("\nbit length overflow\n");
	/* This happens for example on obj2 and pic of the Calgary corpus */

	/* Find the first bit length which could increase: */
	do {
		bits = max_length-1;
		while (state.ts.bl_count[bits] == 0) bits--;
		state.ts.bl_count[bits]--;           /* move one leaf down the tree */
		state.ts.bl_count[bits+1] += (UINT16)2; /* move one overflow item as its brother */
		state.ts.bl_count[max_length]--;
		/* The brother of the overflow item also moves one step up,
		* but this does not affect bl_count[max_length]
		*/
		overflow -= 2;
	} while (overflow > 0);

	/* Now recompute all bit lengths, scanning in increasing frequency.
	* h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
	* lengths instead of fixing only the wrong ones. This idea is taken
	* from 'ar' written by Haruhiko Okumura.)
	*/
	for (bits = max_length; bits != 0; bits--) {
		n = state.ts.bl_count[bits];
		while (n != 0) {
			m = state.ts.heap[--h];
			if (m > max_code) continue;
			if (tree[m].dl.len != (UINT16)bits) {
				//Trace("code %d bits %d->%d\n", m, tree[m].dl.len, bits);
				state.ts.opt_len += ((long)bits-(long)tree[m].dl.len)*(long)tree[m].fc.freq;
				tree[m].dl.len = (UINT16)bits;
			}
			n--;
		}
	}
}

/* ===========================================================================
* Generate the codes for a given tree and bit counts (which need not be
* optimal).
* IN assertion: the array bl_count contains the bit length statistics for
* the given tree and the field len is set for all tree elements.
* OUT assertion: the field code is set for all tree elements of non
*     zero code length.
*/
void SubZipEnumator::gen_codes (TState &state, ct_data *tree, int max_code)
{
	UINT16 next_code[MAX_BITS+1]; /* next code value for each bit length */
	UINT16 code = 0;              /* running code value */
	int bits;                  /* bit index */
	int n;                     /* code index */

	/* The distribution counts are first used to generate the code values
	* without bit reversal.
	*/
	for (bits = 1; bits <= MAX_BITS; bits++) {
		next_code[bits] = code = (UINT16)((code + state.ts.bl_count[bits-1]) << 1);
	}
	/* Check that the bit counts in bl_count are consistent. The last code
	* must be all ones.
	*/
	//Assert(state,code + state.ts.bl_count[MAX_BITS]-1 == (1<< ((UINT16) MAX_BITS)) - 1,
	//            "inconsistent bit counts");
	//Trace("\ngen_codes: max_code %d ", max_code);

	for (n = 0;  n <= max_code; n++) {
		int len = tree[n].dl.len;
		if (len == 0) continue;
		/* Now reverse the bits */
		tree[n].fc.code = (UINT16)bi_reverse(next_code[len]++, len);

		//Tracec(tree != state.ts.static_ltree, "\nn %3d %c l %2d c %4x (%x) ", n, (isgraph(n) ? n : ' '), len, tree[n].fc.code, next_code[len]-1);
	}
}

/* ===========================================================================
* Construct one Huffman tree and assigns the code bit strings and lengths.
* Update the total bit length for the current block.
* IN assertion: the field freq is set for all tree elements.
* OUT assertions: the fields len and code are set to the optimal bit length
*     and corresponding code. The length opt_len is updated; static_len is
*     also updated if stree is not null. The field max_code is set.
*/
void SubZipEnumator::build_tree(TState &state,tree_desc *desc)
{
	ct_data *tree   = desc->dyn_tree;
	ct_data *stree  = desc->static_tree;
	int elems            = desc->elems;
	int n, m;          /* iterate over heap elements */
	int max_code = -1; /* largest code with non zero frequency */
	int node = elems;  /* next internal node of the tree */

	/* Construct the initial heap, with least frequent element in
	* heap[SMALLEST]. The sons of heap[n] are heap[2*n] and heap[2*n+1].
	* heap[0] is not used.
	*/
	state.ts.heap_len = 0, state.ts.heap_max = HEAP_SIZE;

	for (n = 0; n < elems; n++) {
		if (tree[n].fc.freq != 0) {
			state.ts.heap[++state.ts.heap_len] = max_code = n;
			state.ts.depth[n] = 0;
		} else {
			tree[n].dl.len = 0;
		}
	}

	/* The pkzip format requires that at least one distance code exists,
	* and that at least one bit should be sent even if there is only one
	* possible code. So to avoid special checks later on we force at least
	* two codes of non zero frequency.
	*/
	while (state.ts.heap_len < 2) {
		int newcp = state.ts.heap[++state.ts.heap_len] = (max_code < 2 ? ++max_code : 0);
		tree[newcp].fc.freq = 1;
		state.ts.depth[newcp] = 0;
		state.ts.opt_len--; if (stree) state.ts.static_len -= stree[newcp].dl.len;
		/* new is 0 or 1 so it does not have extra bits */
	}
	desc->max_code = max_code;

	/* The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
	* establish sub-heaps of increasing lengths:
	*/
	for (n = state.ts.heap_len/2; n >= 1; n--) pqdownheap(state,tree, n);

	/* Construct the Huffman tree by repeatedly combining the least two
	* frequent nodes.
	*/
	do {
		pqremove(tree, n);   /* n = node of least frequency */
		m = state.ts.heap[SMALLEST];  /* m = node of next least frequency */

		state.ts.heap[--state.ts.heap_max] = n; /* keep the nodes sorted by frequency */
		state.ts.heap[--state.ts.heap_max] = m;

		/* Create a new node father of n and m */
		tree[node].fc.freq = (UINT16)(tree[n].fc.freq + tree[m].fc.freq);
		state.ts.depth[node] = (UINT8) (Max(state.ts.depth[n], state.ts.depth[m]) + 1);
		tree[n].dl.dad = tree[m].dl.dad = (UINT16)node;
		/* and insert the new node in the heap */
		state.ts.heap[SMALLEST] = node++;
		pqdownheap(state,tree, SMALLEST);

	} while (state.ts.heap_len >= 2);

	state.ts.heap[--state.ts.heap_max] = state.ts.heap[SMALLEST];

	/* At this point, the fields freq and dad are set. We can now
	* generate the bit lengths.
	*/
	gen_bitlen(state,(tree_desc *)desc);

	/* The field len is now set, we can generate the bit codes */
	gen_codes (state,(ct_data *)tree, max_code);
}

/* ===========================================================================
* Scan a literal or distance tree to determine the frequencies of the codes
* in the bit length tree. Updates opt_len to take into account the repeat
* counts. (The contribution of the bit length codes will be added later
* during the construction of bl_tree.)
*/
void SubZipEnumator::scan_tree (TState &state,ct_data *tree, int max_code)
{
	int n;                     /* iterates over all tree elements */
	int prevlen = -1;          /* last emitted length */
	int curlen;                /* length of current code */
	int nextlen = tree[0].dl.len; /* length of next code */
	int count = 0;             /* repeat count of the current code */
	int max_count = 7;         /* max repeat count */
	int min_count = 4;         /* min repeat count */

	if (nextlen == 0) max_count = 138, min_count = 3;
	tree[max_code+1].dl.len = (UINT16)-1; /* guard */

	for (n = 0; n <= max_code; n++) {
		curlen = nextlen; nextlen = tree[n+1].dl.len;
		if (++count < max_count && curlen == nextlen) {
			continue;
		} else if (count < min_count) {
			state.ts.bl_tree[curlen].fc.freq = (UINT16)(state.ts.bl_tree[curlen].fc.freq + count);
		} else if (curlen != 0) {
			if (curlen != prevlen) state.ts.bl_tree[curlen].fc.freq++;
			state.ts.bl_tree[REP_3_6].fc.freq++;
		} else if (count <= 10) {
			state.ts.bl_tree[REPZ_3_10].fc.freq++;
		} else {
			state.ts.bl_tree[REPZ_11_138].fc.freq++;
		}
		count = 0; prevlen = curlen;
		if (nextlen == 0) {
			max_count = 138, min_count = 3;
		} else if (curlen == nextlen) {
			max_count = 6, min_count = 3;
		} else {
			max_count = 7, min_count = 4;
		}
	}
}

/* ===========================================================================
* Send a literal or distance tree in compressed form, using the codes in
* bl_tree.
*/
void SubZipEnumator::send_tree (TState &state, ct_data *tree, int max_code)
{
	int n;                     /* iterates over all tree elements */
	int prevlen = -1;          /* last emitted length */
	int curlen;                /* length of current code */
	int nextlen = tree[0].dl.len; /* length of next code */
	int count = 0;             /* repeat count of the current code */
	int max_count = 7;         /* max repeat count */
	int min_count = 4;         /* min repeat count */

	/* tree[max_code+1].dl.len = -1; */  /* guard already set */
	if (nextlen == 0) max_count = 138, min_count = 3;

	for (n = 0; n <= max_code; n++) {
		curlen = nextlen; nextlen = tree[n+1].dl.len;
		if (++count < max_count && curlen == nextlen) {
			continue;
		} else if (count < min_count) {
			do { send_code(state, curlen, state.ts.bl_tree); } while (--count != 0);

		} else if (curlen != 0) {
			if (curlen != prevlen) {
				send_code(state, curlen, state.ts.bl_tree); count--;
			}
			//Assert(state,count >= 3 && count <= 6, " 3_6?");
			send_code(state,REP_3_6, state.ts.bl_tree); send_bits(state,count-3, 2);

		} else if (count <= 10) {
			send_code(state,REPZ_3_10, state.ts.bl_tree); send_bits(state,count-3, 3);

		} else {
			send_code(state,REPZ_11_138, state.ts.bl_tree); send_bits(state,count-11, 7);
		}
		count = 0; prevlen = curlen;
		if (nextlen == 0) {
			max_count = 138, min_count = 3;
		} else if (curlen == nextlen) {
			max_count = 6, min_count = 3;
		} else {
			max_count = 7, min_count = 4;
		}
	}
}

/* ===========================================================================
* Construct the Huffman tree for the bit lengths and return the index in
* bl_order of the last bit length code to send.
*/
int SubZipEnumator::build_bl_tree(TState &state)
{
	int max_blindex;  /* index of last bit length code of non zero freq */

	/* Determine the bit length frequencies for literal and distance trees */
	scan_tree(state,(ct_data *)state.ts.dyn_ltree, state.ts.l_desc.max_code);
	scan_tree(state,(ct_data *)state.ts.dyn_dtree, state.ts.d_desc.max_code);

	/* Build the bit length tree: */
	build_tree(state,(tree_desc *)(&state.ts.bl_desc));
	/* opt_len now includes the length of the tree representations, except
	* the lengths of the bit lengths codes and the 5+5+4 bits for the counts.
	*/

	/* Determine the number of bit length codes to send. The pkzip format
	* requires that at least 4 bit length codes be sent. (appnote.txt says
	* 3 but the actual value used is 4.)
	*/
	for (max_blindex = BL_CODES-1; max_blindex >= 3; max_blindex--) {
		if (state.ts.bl_tree[bl_order[max_blindex]].dl.len != 0) break;
	}
	/* Update opt_len to include the bit length tree and counts */
	state.ts.opt_len += 3*(max_blindex+1) + 5+5+4;
	//Trace("\ndyn trees: dyn %ld, stat %ld", state.ts.opt_len, state.ts.static_len);

	return max_blindex;
}

/* ===========================================================================
* Send the header for a block using dynamic Huffman trees: the counts, the
* lengths of the bit length codes, the literal tree and the distance tree.
* IN assertion: lcodes >= 257, dcodes >= 1, blcodes >= 4.
*/
void SubZipEnumator::send_all_trees(TState &state,int lcodes, int dcodes, int blcodes)
{
	int rank;                    /* index in bl_order */

	//Assert(state,lcodes >= 257 && dcodes >= 1 && blcodes >= 4, "not enough codes");
	//Assert(state,lcodes <= L_CODES && dcodes <= D_CODES && blcodes <= BL_CODES,
	//            "too many codes");
	//Trace("\nbl counts: ");
	send_bits(state,lcodes-257, 5);
	/* not +255 as stated in appnote.txt 1.93a or -256 in 2.04c */
	send_bits(state,dcodes-1,   5);
	send_bits(state,blcodes-4,  4); /* not -3 as stated in appnote.txt */
	for (rank = 0; rank < blcodes; rank++) {
		//Trace("\nbl code %2d ", bl_order[rank]);
		send_bits(state,state.ts.bl_tree[bl_order[rank]].dl.len, 3);
	}    
	//Trace("\nbl tree: sent %ld", state.bs.bits_sent);

	send_tree(state,(ct_data *)state.ts.dyn_ltree, lcodes-1); /* send the literal tree */
	//Trace("\nlit tree: sent %ld", state.bs.bits_sent);

	send_tree(state,(ct_data *)state.ts.dyn_dtree, dcodes-1); /* send the distance tree */
	//Trace("\ndist tree: sent %ld", state.bs.bits_sent);
}

/* ===========================================================================
* Determine the best encoding for the current block: dynamic trees, static
* trees or store, and output the encoded block to the zip file. This function
* returns the total compressed length (in bytes) for the file so far.
*/
UINT32 SubZipEnumator::flush_block(TState &state,UINT8 *buf, UINT32 stored_len, int eof)
{
	UINT32 opt_lenb, static_lenb; /* opt_len and static_len in bytes */
	int max_blindex;  /* index of last bit length code of non zero freq */

	state.ts.flag_buf[state.ts.last_flags] = state.ts.flags; /* Save the flags for the last 8 items */

	/* Check if the file is ascii or binary */
	if (*state.ts.file_type == (UINT16)UNKNOWN) set_file_type(state);

	/* Construct the literal and distance trees */
	build_tree(state,(tree_desc *)(&state.ts.l_desc));
	//Trace("\nlit data: dyn %ld, stat %ld", state.ts.opt_len, state.ts.static_len);

	build_tree(state,(tree_desc *)(&state.ts.d_desc));
	//Trace("\ndist data: dyn %ld, stat %ld", state.ts.opt_len, state.ts.static_len);
	/* At this point, opt_len and static_len are the total bit lengths of
	* the compressed block data, excluding the tree representations.
	*/

	/* Build the bit length tree for the above two trees, and get the index
	* in bl_order of the last bit length code to send.
	*/
	max_blindex = build_bl_tree(state);

	/* Determine the best encoding. Compute first the block length in bytes */
	opt_lenb = (state.ts.opt_len+3+7)>>3;
	static_lenb = (state.ts.static_len+3+7)>>3;
	state.ts.input_len += stored_len; /* for debugging only */

	//Trace("\nopt %lu(%lu) stat %lu(%lu) stored %lu lit %u dist %u ",
	//            opt_lenb, state.ts.opt_len, static_lenb, state.ts.static_len, stored_len,
	//          state.ts.last_lit, state.ts.last_dist);

	if (static_lenb <= opt_lenb) opt_lenb = static_lenb;

	// Originally, zip allowed the file to be transformed from a compressed
	// into a stored file in the case where compression failed, there
	// was only one block, and it was allowed to change. I've removed this
	// possibility since the code's cleaner if no changes are allowed.
	//if (stored_len <= opt_lenb && eof && state.ts.cmpr_bytelen == 0L
	//   && state.ts.cmpr_len_bits == 0L && state.seekable)
	//{   // && state.ts.file_method != NULL
	//    // Since LIT_BUFSIZE <= 2*WSIZE, the input data must be there:
	//    //Assert(state,buf!=NULL,"block vanished");
	//    copy_block(state,buf, (unsigned)stored_len, 0); // without header
	//    state.ts.cmpr_bytelen = stored_len;
	//    //Assert(state,false,"unimplemented *state.ts.file_method = STORE;");
	//    //*state.ts.file_method = STORE;
	//}
	//else
	if (stored_len+4 <= opt_lenb && buf != (UINT8*)NULL) {
		/* 4: two words for the lengths */
		/* The test buf != NULL is only necessary if LIT_BUFSIZE > WSIZE.
		* Otherwise we can't have processed more than WSIZE input bytes since
		* the last block flush, because compression would have been
		* successful. If LIT_BUFSIZE <= WSIZE, it is never too late to
		* transform a block into a stored block.
		*/
		send_bits(state,(STORED_BLOCK<<1)+eof, 3);  /* send block type */
		state.ts.cmpr_bytelen += ((state.ts.cmpr_len_bits + 3 + 7) >> 3) + stored_len + 4;
		state.ts.cmpr_len_bits = 0L;

		copy_block(state,buf, (unsigned)stored_len, 1); /* with header */
	}
	else if (static_lenb == opt_lenb) {
		send_bits(state,(STATIC_TREES<<1)+eof, 3);
		compress_block(state,(ct_data *)state.ts.static_ltree, (ct_data *)state.ts.static_dtree);
		state.ts.cmpr_len_bits += 3 + state.ts.static_len;
		state.ts.cmpr_bytelen += state.ts.cmpr_len_bits >> 3;
		state.ts.cmpr_len_bits &= 7L;
	}
	else {
		send_bits(state,(DYN_TREES<<1)+eof, 3);
		send_all_trees(state,state.ts.l_desc.max_code+1, state.ts.d_desc.max_code+1, max_blindex+1);
		compress_block(state,(ct_data *)state.ts.dyn_ltree, (ct_data *)state.ts.dyn_dtree);
		state.ts.cmpr_len_bits += 3 + state.ts.opt_len;
		state.ts.cmpr_bytelen += state.ts.cmpr_len_bits >> 3;
		state.ts.cmpr_len_bits &= 7L;
	}
	//Assert(state,((state.ts.cmpr_bytelen << 3) + state.ts.cmpr_len_bits) == state.bs.bits_sent, "bad compressed size");
	init_block(state);

	if (eof) {
		// //Assert(state,input_len == isize, "bad input size");
		bi_windup(state);
		state.ts.cmpr_len_bits += 7;  /* align on byte boundary */
	}
	//Trace("\n");

	return state.ts.cmpr_bytelen + (state.ts.cmpr_len_bits >> 3);
}

/* ===========================================================================
* Save the match info and tally the frequency counts. Return true if
* the current block must be flushed.
*/
int SubZipEnumator::ct_tally (TState &state,int dist, int lc)
{
	state.ts.l_buf[state.ts.last_lit++] = (UINT8)lc;
	if (dist == 0) {
		/* lc is the unmatched UINT8 */
		state.ts.dyn_ltree[lc].fc.freq++;
	} else {
		/* Here, lc is the match length - MIN_MATCH */
		dist--;             /* dist = match distance - 1 */
		//Assert(state,(UINT16)dist < (UINT16)MAX_DIST &&
		//              (UINT16)lc <= (UINT16)(MAX_MATCH-MIN_MATCH) &&
		//               (UINT16)d_code(dist) < (UINT16)D_CODES,  "ct_tally: bad match");

		state.ts.dyn_ltree[state.ts.length_code[lc]+LITERALS+1].fc.freq++;
		state.ts.dyn_dtree[d_code(dist)].fc.freq++;

		state.ts.d_buf[state.ts.last_dist++] = (UINT16)dist;
		state.ts.flags |= state.ts.flag_bit;
	}
	state.ts.flag_bit <<= 1;

	/* Output the flags if they fill a byte: */
	if ((state.ts.last_lit & 7) == 0) {
		state.ts.flag_buf[state.ts.last_flags++] = state.ts.flags;
		state.ts.flags = 0, state.ts.flag_bit = 1;
	}
	/* Try to guess if it is profitable to stop the current block here */
	if (state.level > 2 && (state.ts.last_lit & 0xfff) == 0) {
		/* Compute an upper bound for the compressed length */
		UINT32 out_length = (UINT32)state.ts.last_lit*8L;
		UINT32 in_length = (UINT32)state.ds.strstart-state.ds.block_start;
		int dcode;
		for (dcode = 0; dcode < D_CODES; dcode++) {
			out_length += (UINT32)state.ts.dyn_dtree[dcode].fc.freq*(5L+extra_dbits[dcode]);
		}
		out_length >>= 3;
		//Trace("\nlast_lit %u, last_dist %u, in %ld, out ~%ld(%ld%%) ",
		//             state.ts.last_lit, state.ts.last_dist, in_length, out_length,
		//               100L - out_length*100L/in_length);
		if (state.ts.last_dist < state.ts.last_lit/2 && out_length < in_length/2) return 1;
	}
	return (state.ts.last_lit == LIT_BUFSIZE-1 || state.ts.last_dist == DIST_BUFSIZE);
	/* We avoid equality with LIT_BUFSIZE because of wraparound at 64K
	* on 16 bit machines and because stored blocks are restricted to
	* 64K-1 bytes.
	*/
}

/* ===========================================================================
* Send the block data compressed using the given Huffman trees
*/
void SubZipEnumator::compress_block(TState &state,ct_data *ltree, ct_data *dtree)
{
	unsigned dist;      /* distance of matched string */
	int lc;             /* match length or unmatched UINT8 (if dist == 0) */
	unsigned lx = 0;    /* running index in l_buf */
	unsigned dx = 0;    /* running index in d_buf */
	unsigned fx = 0;    /* running index in flag_buf */
	UINT8 flag = 0;       /* current flags */
	unsigned code;      /* the code to send */
	int extra;          /* number of extra bits to send */

	if (state.ts.last_lit != 0) do {
		if ((lx & 7) == 0) flag = state.ts.flag_buf[fx++];
		lc = state.ts.l_buf[lx++];
		if ((flag & 1) == 0) {
			send_code(state,lc, ltree); /* send a literal byte */
		} else {
			/* Here, lc is the match length - MIN_MATCH */
			code = state.ts.length_code[lc];
			send_code(state,code+LITERALS+1, ltree); /* send the length code */
			extra = extra_lbits[code];
			if (extra != 0) {
				lc -= state.ts.base_length[code];
				send_bits(state,lc, extra);        /* send the extra length bits */
			}
			dist = state.ts.d_buf[dx++];
			/* Here, dist is the match distance - 1 */
			code = d_code(dist);
			//Assert(state,code < D_CODES, "bad d_code");

			send_code(state,code, dtree);       /* send the distance code */
			extra = extra_dbits[code];
			if (extra != 0) {
				dist -= state.ts.base_dist[code];
				send_bits(state,dist, extra);   /* send the extra distance bits */
			}
		} /* literal or match pair ? */
		flag >>= 1;
	} while (lx < state.ts.last_lit);

	send_code(state,END_BLOCK, ltree);
}

/* ===========================================================================
* Set the file type to ASCII or BINARY, using a crude approximation:
* binary if more than 20% of the bytes are <= 6 or >= 128, ascii otherwise.
* IN assertion: the fields freq of dyn_ltree are set and the total of all
* frequencies does not exceed 64K (to fit in an int on 16 bit machines).
*/
void SubZipEnumator::set_file_type(TState &state)
{
	int n = 0;
	unsigned ascii_freq = 0;
	unsigned bin_freq = 0;
	while (n < 7)        bin_freq += state.ts.dyn_ltree[n++].fc.freq;
	while (n < 128)    ascii_freq += state.ts.dyn_ltree[n++].fc.freq;
	while (n < LITERALS) bin_freq += state.ts.dyn_ltree[n++].fc.freq;
	*state.ts.file_type = (UINT16)(bin_freq > (ascii_freq >> 2) ? BINARY : ASCII);
}


/* ===========================================================================
* Initialize the bit string routines.
*/
void SubZipEnumator::bi_init (TState &state,UINT8 *tgt_buf, unsigned tgt_size, int flsh_allowed)
{
	state.bs.out_buf = tgt_buf;
	state.bs.out_size = tgt_size;
	state.bs.out_offset = 0;
	state.bs.flush_flg = flsh_allowed;

	state.bs.bi_buf = 0;
	state.bs.bi_valid = 0;
	state.bs.bits_sent = 0L;
}

/* ===========================================================================
* Send a value on a given number of bits.
* IN assertion: length <= 16 and value fits in length bits.
*/
void SubZipEnumator::send_bits(TState &state,int value, int length)
{
	//Assert(state,length > 0 && length <= 15, "invalid length");
	state.bs.bits_sent += (UINT32)length;
	/* If not enough room in bi_buf, use (bi_valid) bits from bi_buf and
	* (Buf_size - bi_valid) bits from value to flush the filled bi_buf,
	* then fill in the rest of (value), leaving (length - (Buf_size-bi_valid))
	* unused bits in bi_buf.
	*/
	state.bs.bi_buf |= (value << state.bs.bi_valid);
	state.bs.bi_valid += length;
	if (state.bs.bi_valid > (int)Buf_size) {
		PUTSHORT(state,state.bs.bi_buf);
		state.bs.bi_valid -= Buf_size;
		state.bs.bi_buf = (unsigned)value >> (length - state.bs.bi_valid);
	}
}

/* ===========================================================================
* Reverse the first len bits of a code, using straightforward code (a faster
* method would use a table)
* IN assertion: 1 <= len <= 15
*/
unsigned SubZipEnumator::bi_reverse(unsigned code, int len)
{
	register unsigned res = 0;
	do {
		res |= code & 1;
		code >>= 1, res <<= 1;
	} while (--len > 0);
	return res >> 1;
}

/* ===========================================================================
* Write out any remaining bits in an incomplete byte.
*/
void SubZipEnumator::bi_windup(TState &state)
{
	if (state.bs.bi_valid > 8) {
		PUTSHORT(state,state.bs.bi_buf);
	} else if (state.bs.bi_valid > 0) {
		PUTBYTE(state,state.bs.bi_buf);
	}
	if (state.bs.flush_flg) {
		state.flush_outbuf(state.param,state.bs.out_buf, &state.bs.out_offset);
	}
	state.bs.bi_buf = 0;
	state.bs.bi_valid = 0;
	state.bs.bits_sent = (state.bs.bits_sent+7) & ~7;
}

/* ===========================================================================
* Copy a stored block to the zip file, storing first the length and its
* one's complement if requested.
*/
void SubZipEnumator::copy_block(TState &state, UINT8 *block, unsigned len, int header)
{
	bi_windup(state);              /* align on byte boundary */

	if (header) {
		PUTSHORT(state,(UINT16)len);
		PUTSHORT(state,(UINT16)~len);
		state.bs.bits_sent += 2*16;
	}
	if (state.bs.flush_flg) {
		state.flush_outbuf(state.param,state.bs.out_buf, &state.bs.out_offset);
		state.bs.out_offset = len;
		state.flush_outbuf(state.param,block, &state.bs.out_offset);
	} else if (state.bs.out_offset + len > state.bs.out_size) {
		//Assert(state,false,"output buffer too small for in-memory compression");
	} else {
		memcpy(state.bs.out_buf + state.bs.out_offset, block, len);
		state.bs.out_offset += len;
	}
	state.bs.bits_sent += (UINT32)len<<3;
}

/* ===========================================================================
*  Prototypes for functions.
*/

// void fill_window  (TState &state);
// UINT32 deflate_fast  (TState &state);
// 
// int  longest_match (TState &state,UINT32 cur_match);


/* ===========================================================================
* Update a hash value with the given input byte
* IN  assertion: all calls to to UPDATE_HASH are made with consecutive
*    input characters, so that a running hash key can be computed from the
*    previous key instead of complete recalculation each time.
*/
#define UPDATE_HASH(h,c) (h = (((h)<<H_SHIFT) ^ (c)) & HASH_MASK)

/* ===========================================================================
* Insert string s in the dictionary and set match_head to the previous head
* of the hash chain (the most recent string with same hash key). Return
* the previous length of the hash chain.
* IN  assertion: all calls to to INSERT_STRING are made with consecutive
*    input characters and the first MIN_MATCH bytes of s are valid
*    (except for the last MIN_MATCH-1 bytes of the input file).
*/
#define INSERT_STRING(s, match_head) \
	(UPDATE_HASH(state.ds.ins_h, state.ds.window[(s) + (MIN_MATCH-1)]), \
	state.ds.prev[(s) & WMASK] = match_head = state.ds.head[state.ds.ins_h], \
	state.ds.head[state.ds.ins_h] = (s))

/* ===========================================================================
* Initialize the "longest match" routines for a new file
*
* IN assertion: window_size is > 0 if the input file is already read or
*    mmap'ed in the window[] array, 0 otherwise. In the first case,
*    window_size is sufficient to contain the whole input file plus
*    MIN_LOOKAHEAD bytes (to avoid referencing memory beyond the end
*    of window[] when looking for matches towards the end).
*/
void SubZipEnumator::lm_init (TState &state, int pack_level, UINT16 *flags)
{
	register unsigned j;

	//Assert(state,pack_level>=1 && pack_level<=8,"bad pack level");

	/* Do not slide the window if the whole input is already in memory
	* (window_size > 0)
	*/
	state.ds.sliding = 0;
	if (state.ds.window_size == 0L) {
		state.ds.sliding = 1;
		state.ds.window_size = (UINT32)2L*WSIZE;
	}

	/* Initialize the hash table (avoiding 64K overflow for 16 bit systems).
	* prev[] will be initialized on the fly.
	*/
	state.ds.head[HASH_SIZE-1] = NIL;
	memset((UINT8*)state.ds.head, NIL, (unsigned)(HASH_SIZE-1)*sizeof(*state.ds.head));

	/* Set the default configuration parameters:
	*/
	state.ds.max_lazy_match   = configuration_table[pack_level].max_lazy;
	state.ds.good_match       = configuration_table[pack_level].good_length;
	state.ds.nice_match       = configuration_table[pack_level].nice_length;
	state.ds.max_chain_length = configuration_table[pack_level].max_chain;
	if (pack_level <= 2) {
		*flags |= FAST;
	} else if (pack_level >= 8) {
		*flags |= SLOW;
	}
	/* ??? reduce max_chain_length for binary files */

	state.ds.strstart = 0;
	state.ds.block_start = 0L;

	j = WSIZE;
	j <<= 1; // Can read 64K in one step
	state.ds.lookahead = state.readfunc(state, (UINT8*)state.ds.window, j);

	if (state.ds.lookahead == 0 || state.ds.lookahead == (unsigned)EOF) {
		state.ds.eofile = 1, state.ds.lookahead = 0;
		return;
	}
	state.ds.eofile = 0;
	/* Make sure that we always have enough lookahead. This is important
	* if input comes from a device such as a tty.
	*/
	if (state.ds.lookahead < MIN_LOOKAHEAD) fill_window(state);

	state.ds.ins_h = 0;
	for (j=0; j<MIN_MATCH-1; j++) UPDATE_HASH(state.ds.ins_h, state.ds.window[j]);
	/* If lookahead < MIN_MATCH, ins_h is garbage, but this is
	* not important since only literal bytes will be emitted.
	*/
}


/* ===========================================================================
* Set match_start to the longest match starting at the given string and
* return its length. Matches shorter or equal to prev_length are discarded,
* in which case the result is equal to prev_length and match_start is
* garbage.
* IN assertions: cur_match is the head of the hash chain for the current
*   string (strstart) and its distance is <= MAX_DIST, and prev_length >= 1
*/
// For 80x86 and 680x0 and ARM, an optimized version is in match.asm or
// match.S. The code is functionally equivalent, so you can use the C version
// if desired. Which I do so desire!
int SubZipEnumator::longest_match(TState &state,UINT32 cur_match)
{
	unsigned chain_length = state.ds.max_chain_length;   /* max hash chain length */
	register UINT8 far *scan = state.ds.window + state.ds.strstart; /* current string */
	register UINT8 far *match;                    /* matched string */
	register int len;                           /* length of current match */
	int best_len = state.ds.prev_length;                 /* best match length so far */
	UINT32 limit = state.ds.strstart > (UINT32)MAX_DIST ? state.ds.strstart - (UINT32)MAX_DIST : NIL;
	/* Stop when cur_match becomes <= limit. To simplify the code,
	* we prevent matches with the string of window index 0.
	*/

	// The code is optimized for HASH_BITS >= 8 and MAX_MATCH-2 multiple of 16.
	// It is easy to get rid of this optimization if necessary.
	//Assert(state,HASH_BITS>=8 && MAX_MATCH==258,"Code too clever");



	register UINT8 far *strend = state.ds.window + state.ds.strstart + MAX_MATCH;
	register UINT8 scan_end1  = scan[best_len-1];
	register UINT8 scan_end   = scan[best_len];

	/* Do not waste too much time if we already have a good match: */
	if (state.ds.prev_length >= state.ds.good_match) {
		chain_length >>= 2;
	}

	//Assert(state,state.ds.strstart <= state.ds.window_size-MIN_LOOKAHEAD, "insufficient lookahead");

	do {
		//Assert(state,cur_match < state.ds.strstart, "no future");
		match = state.ds.window + cur_match;

		/* Skip to next match if the match length cannot increase
		* or if the match length is less than 2:
		*/
		if (match[best_len]   != scan_end  ||
			match[best_len-1] != scan_end1 ||
			*match            != *scan     ||
			*++match          != scan[1])      continue;

		/* The check at best_len-1 can be removed because it will be made
		* again later. (This heuristic is not always a win.)
		* It is not necessary to compare scan[2] and match[2] since they
		* are always equal when the other bytes match, given that
		* the hash keys are equal and that HASH_BITS >= 8.
		*/
		scan += 2, match++;

		/* We check for insufficient lookahead only every 8th comparison;
		* the 256th check will be made at strstart+258.
		*/
		do {
		} while (*++scan == *++match && *++scan == *++match &&
			*++scan == *++match && *++scan == *++match &&
			*++scan == *++match && *++scan == *++match &&
			*++scan == *++match && *++scan == *++match &&
			scan < strend);

		//Assert(state,scan <= state.ds.window+(unsigned)(state.ds.window_size-1), "wild scan");

		len = MAX_MATCH - (int)(strend - scan);
		scan = strend - MAX_MATCH;


		if (len > best_len) {
			state.ds.match_start = cur_match;
			best_len = len;
			if (len >= state.ds.nice_match) break;
			scan_end1  = scan[best_len-1];
			scan_end   = scan[best_len];
		}
	} while ((cur_match = state.ds.prev[cur_match & WMASK]) > limit
		&& --chain_length != 0);

	return best_len;
}



#define check_match(state,start, match, length)
// or alternatively...
//void check_match(TState &state,UINT32 start, UINT32 match, int length)
//{ // check that the match is indeed a match
//    if (memcmp((UINT8*)state.ds.window + match,
//                (UINT8*)state.ds.window + start, length) != EQUAL) {
//        fprintf(stderr,
//            " start %d, match %d, length %d\n",
//            start, match, length);
//        error("invalid match");
//    }
//    if (state.verbose > 1) {
//        fprintf(stderr,"\\[%d,%d]", start-match, length);
//        do { fprintf(stdout,"%c",state.ds.window[start++]); } while (--length != 0);
//    }
//}

/* ===========================================================================
* Fill the window when the lookahead becomes insufficient.
* Updates strstart and lookahead, and sets eofile if end of input file.
*
* IN assertion: lookahead < MIN_LOOKAHEAD && strstart + lookahead > 0
* OUT assertions: strstart <= window_size-MIN_LOOKAHEAD
*    At least one byte has been read, or eofile is set; file reads are
*    performed for at least two bytes (required for the translate_eol option).
*/
void SubZipEnumator::fill_window(TState &state)
{
	register unsigned n, m;
	unsigned more;    /* Amount of free space at the end of the window. */

	do {
		more = (unsigned)(state.ds.window_size - (UINT32)state.ds.lookahead - (UINT32)state.ds.strstart);

		/* If the window is almost full and there is insufficient lookahead,
		* move the upper half to the lower one to make room in the upper half.
		*/
		if (more == (unsigned)EOF) {
			/* Very unlikely, but possible on 16 bit machine if strstart == 0
			* and lookahead == 1 (input done one byte at time)
			*/
			more--;

			/* For MMAP or BIG_MEM, the whole input file is already in memory so
			* we must not perform sliding. We must however call (*read_buf)() in
			* order to compute the crc, update lookahead and possibly set eofile.
			*/
		} else if (state.ds.strstart >= WSIZE+MAX_DIST && state.ds.sliding) {

			/* By the IN assertion, the window is not empty so we can't confuse
			* more == 0 with more == 64K on a 16 bit machine.
			*/
			memcpy((UINT8*)state.ds.window, (UINT8*)state.ds.window+WSIZE, (unsigned)WSIZE);
			state.ds.match_start -= WSIZE;
			state.ds.strstart    -= WSIZE; /* we now have strstart >= MAX_DIST: */

			state.ds.block_start -= (long) WSIZE;

			for (n = 0; n < HASH_SIZE; n++) {
				m = state.ds.head[n];
				state.ds.head[n] = (UINT32)(m >= WSIZE ? m-WSIZE : NIL);
			}
			for (n = 0; n < WSIZE; n++) {
				m = state.ds.prev[n];
				state.ds.prev[n] = (UINT32)(m >= WSIZE ? m-WSIZE : NIL);
				/* If n is not on any hash chain, prev[n] is garbage but
				* its value will never be used.
				*/
			}
			more += WSIZE;
		}
		if (state.ds.eofile) return;

		/* If there was no sliding:
		*    strstart <= WSIZE+MAX_DIST-1 && lookahead <= MIN_LOOKAHEAD - 1 &&
		*    more == window_size - lookahead - strstart
		* => more >= window_size - (MIN_LOOKAHEAD-1 + WSIZE + MAX_DIST-1)
		* => more >= window_size - 2*WSIZE + 2
		* In the MMAP or BIG_MEM case (not yet supported in gzip),
		*   window_size == input_size + MIN_LOOKAHEAD  &&
		*   strstart + lookahead <= input_size => more >= MIN_LOOKAHEAD.
		* Otherwise, window_size == 2*WSIZE so more >= 2.
		* If there was sliding, more >= WSIZE. So in all cases, more >= 2.
		*/
		//Assert(state,more >= 2, "more < 2");

		n = state.readfunc(state, (UINT8*)state.ds.window+state.ds.strstart+state.ds.lookahead, more);

		if (n == 0 || n == (unsigned)EOF) {
			state.ds.eofile = 1;
		} else {
			state.ds.lookahead += n;
		}
	} while (state.ds.lookahead < MIN_LOOKAHEAD && !state.ds.eofile);
}

/* ===========================================================================
* Flush the current block, with given end-of-file flag.
* IN assertion: strstart is set to the end of the current match.
*/
#define FLUSH_BLOCK(state,eof) \
	flush_block(state,state.ds.block_start >= 0L ? (UINT8*)&state.ds.window[(unsigned)state.ds.block_start] : \
	(UINT8*)NULL, (long)state.ds.strstart - state.ds.block_start, (eof))

/* ===========================================================================
* Processes a new input file and return its compressed length. This
* function does not perform lazy evaluation of matches and inserts
* new strings in the dictionary only for unmatched strings or for short
* matches. It is used only for the fast compression options.
*/
UINT32 SubZipEnumator::deflate_fast(TState &state)
{
	UINT32 hash_head = NIL;       /* head of the hash chain */
	int flush;                  /* set if current block must be flushed */
	unsigned match_length = 0;  /* length of best match */

	state.ds.prev_length = MIN_MATCH-1;
	while (state.ds.lookahead != 0) {
		/* Insert the string window[strstart .. strstart+2] in the
		* dictionary, and set hash_head to the head of the hash chain:
		*/
		if (state.ds.lookahead >= MIN_MATCH)
			INSERT_STRING(state.ds.strstart, hash_head);

		/* Find the longest match, discarding those <= prev_length.
		* At this point we have always match_length < MIN_MATCH
		*/
		if (hash_head != NIL && state.ds.strstart - hash_head <= MAX_DIST) {
			/* To simplify the code, we prevent matches with the string
			* of window index 0 (in particular we have to avoid a match
			* of the string with itself at the start of the input file).
			*/
			/* Do not look for matches beyond the end of the input.
			* This is necessary to make deflate deterministic.
			*/
			if ((unsigned)state.ds.nice_match > state.ds.lookahead) state.ds.nice_match = (int)state.ds.lookahead;
			match_length = longest_match (state,hash_head);
			/* longest_match() sets match_start */
			if (match_length > state.ds.lookahead) match_length = state.ds.lookahead;
		}
		if (match_length >= MIN_MATCH) {
			check_match(state,state.ds.strstart, state.ds.match_start, match_length);

			flush = ct_tally(state,state.ds.strstart-state.ds.match_start, match_length - MIN_MATCH);

			state.ds.lookahead -= match_length;

			/* Insert new strings in the hash table only if the match length
			* is not too large. This saves time but degrades compression.
			*/
			if (match_length <= state.ds.max_insert_length
				&& state.ds.lookahead >= MIN_MATCH) {
					match_length--; /* string at strstart already in hash table */
					do {
						state.ds.strstart++;
						INSERT_STRING(state.ds.strstart, hash_head);
						/* strstart never exceeds WSIZE-MAX_MATCH, so there are
						* always MIN_MATCH bytes ahead.
						*/
					} while (--match_length != 0);
					state.ds.strstart++;
			} else {
				state.ds.strstart += match_length;
				match_length = 0;
				state.ds.ins_h = state.ds.window[state.ds.strstart];
				UPDATE_HASH(state.ds.ins_h, state.ds.window[state.ds.strstart+1]);
				//Assert(state,MIN_MATCH==3,"Call UPDATE_HASH() MIN_MATCH-3 more times");
			}
		} else {
			/* No match, output a literal byte */
			flush = ct_tally (state,0, state.ds.window[state.ds.strstart]);
			state.ds.lookahead--;
			state.ds.strstart++;
		}
		if (flush) FLUSH_BLOCK(state,0), state.ds.block_start = state.ds.strstart;

		/* Make sure that we always have enough lookahead, except
		* at the end of the input file. We need MAX_MATCH bytes
		* for the next match, plus MIN_MATCH bytes to insert the
		* string following the next match.
		*/
		if (state.ds.lookahead < MIN_LOOKAHEAD) fill_window(state);
	}
	return FLUSH_BLOCK(state,1); /* eof */
}

/* ===========================================================================
* Same as above, but achieves better compression. We use a lazy
* evaluation for matches: a match is finally adopted only if there is
* no better match at the next window position.
*/
UINT32 SubZipEnumator::deflate(TState &state)
{
	UINT32 hash_head = NIL;       /* head of hash chain */
	UINT32 prev_match;            /* previous match */
	int flush;                  /* set if current block must be flushed */
	int match_available = 0;    /* set if previous match exists */
	register unsigned match_length = MIN_MATCH-1; /* length of best match */

	if (state.level <= 3) return deflate_fast(state); /* optimized for speed */

	/* Process the input block. */
	while (state.ds.lookahead != 0) {
		/* Insert the string window[strstart .. strstart+2] in the
		* dictionary, and set hash_head to the head of the hash chain:
		*/
		if (state.ds.lookahead >= MIN_MATCH)
			INSERT_STRING(state.ds.strstart, hash_head);

		/* Find the longest match, discarding those <= prev_length.
		*/
		state.ds.prev_length = match_length, prev_match = state.ds.match_start;
		match_length = MIN_MATCH-1;

		if (hash_head != NIL && state.ds.prev_length < state.ds.max_lazy_match &&
			state.ds.strstart - hash_head <= MAX_DIST) {
				/* To simplify the code, we prevent matches with the string
				* of window index 0 (in particular we have to avoid a match
				* of the string with itself at the start of the input file).
				*/
				/* Do not look for matches beyond the end of the input.
				* This is necessary to make deflate deterministic.
				*/
				if ((unsigned)state.ds.nice_match > state.ds.lookahead) state.ds.nice_match = (int)state.ds.lookahead;
				match_length = longest_match (state,hash_head);
				/* longest_match() sets match_start */
				if (match_length > state.ds.lookahead) match_length = state.ds.lookahead;

				/* Ignore a length 3 match if it is too distant: */
				if (match_length == MIN_MATCH && state.ds.strstart-state.ds.match_start > TOO_FAR){
					/* If prev_match is also MIN_MATCH, match_start is garbage
					* but we will ignore the current match anyway.
					*/
					match_length = MIN_MATCH-1;
				}
		}
		/* If there was a match at the previous step and the current
		* match is not better, output the previous match:
		*/
		if (state.ds.prev_length >= MIN_MATCH && match_length <= state.ds.prev_length) {
			unsigned max_insert = state.ds.strstart + state.ds.lookahead - MIN_MATCH;
			check_match(state,state.ds.strstart-1, prev_match, state.ds.prev_length);
			flush = ct_tally(state,state.ds.strstart-1-prev_match, state.ds.prev_length - MIN_MATCH);

			/* Insert in hash table all strings up to the end of the match.
			* strstart-1 and strstart are already inserted.
			*/
			state.ds.lookahead -= state.ds.prev_length-1;
			state.ds.prev_length -= 2;
			do {
				if (++state.ds.strstart <= max_insert) {
					INSERT_STRING(state.ds.strstart, hash_head);
					/* strstart never exceeds WSIZE-MAX_MATCH, so there are
					* always MIN_MATCH bytes ahead.
					*/
				}
			} while (--state.ds.prev_length != 0);
			state.ds.strstart++;
			match_available = 0;
			match_length = MIN_MATCH-1;

			if (flush) FLUSH_BLOCK(state,0), state.ds.block_start = state.ds.strstart;

		} else if (match_available) {
			/* If there was no match at the previous position, output a
			* single literal. If there was a match but the current match
			* is longer, truncate the previous match to a single literal.
			*/
			if (ct_tally (state,0, state.ds.window[state.ds.strstart-1])) {
				FLUSH_BLOCK(state,0), state.ds.block_start = state.ds.strstart;
			}
			state.ds.strstart++;
			state.ds.lookahead--;
		} else {
			/* There is no previous match to compare with, wait for
			* the next step to decide.
			*/
			match_available = 1;
			state.ds.strstart++;
			state.ds.lookahead--;
		}
		//        //Assert(state,strstart <= isize && lookahead <= isize, "a bit too far");

		/* Make sure that we always have enough lookahead, except
		* at the end of the input file. We need MAX_MATCH bytes
		* for the next match, plus MIN_MATCH bytes to insert the
		* string following the next match.
		*/
		if (state.ds.lookahead < MIN_LOOKAHEAD) fill_window(state);
	}
	if (match_available) ct_tally (state,0, state.ds.window[state.ds.strstart-1]);

	return FLUSH_BLOCK(state,1); /* eof */
}

int SubZipEnumator::putlocal(struct zlist far *z, WRITEFUNC wfunc,void *param)
{ // Write a local header described by *z to file *f.  Return a ZE_ error code.
	PUTLG(LOCSIG, f);
	PUTSH(z->ver, f);
	PUTSH(z->lflg, f);
	PUTSH(z->how, f);
	PUTLG(z->tim, f);
	PUTLG(z->crc, f);
	PUTLG(z->siz, f);
	PUTLG(z->len, f);
	PUTSH(z->nam, f);
	PUTSH(z->ext, f);
	size_t res = (size_t)wfunc(param, (UINT8*)z->iname, (unsigned int)z->nam);
	if (res!=z->nam) return ZE_TEMP;
	if (z->ext)
	{ res = (size_t)wfunc(param, z->extra, (unsigned int)z->ext);
	if (res!=z->ext) return ZE_TEMP;
	}
	return ZE_OK;
}

int SubZipEnumator::putcentral(struct zlist far *z, WRITEFUNC wfunc, void *param)
{ 
	// Write a central header entry of *z to file *f. Returns a ZE_ code.
	osFileInfo.version = z->vem;
	osFileInfo.version_needed = z->ver;
	osFileInfo.flag = z->flg;                 // general purpose bit flag        2 bytes
	osFileInfo.compression_method = z->how;   // compression method              2 bytes
	osFileInfo.dosDate = z->tim;              // last mod file date in Dos fmt   4 bytes
	osFileInfo.crc = z->crc;                  // crc-32                          4 bytes
	osFileInfo.compressed_size = z->siz;      // compressed size                 4 bytes
	osFileInfo.uncompressed_size = z->len;    // uncompressed size               4 bytes
	osFileInfo.size_filename = z->nam;        // filename length                 2 bytes
	osFileInfo.size_file_extra = 0;      // extra field length              2 bytes
	osFileInfo.size_file_comment = 0;    // file comment length             2 bytes
	osFileInfo.disk_num_start = 0;       // disk number start               2 bytes
	osFileInfo.internal_fa = z->att;          // internal file attributes        2 bytes
	osFileInfo.external_fa = z->atx;
	osFileInfo.Offset_curfile = 0;
	//osFileInfo.TempBlock = (UINT8*)z->iname;
 	osFileInfo.TempBlock = new UINT8[z->nam];
 	memcpy(osFileInfo.TempBlock, z->iname, z->nam);
	return ZE_OK;
}

#define CRC32(c, b) (crc_table[((int)(c) ^ (b)) & 0xff] ^ ((c) >> 8))
#define DO1(buf)  crc = CRC32(crc, *buf++)
#define DO2(buf)  DO1(buf); DO1(buf)
#define DO4(buf)  DO2(buf); DO2(buf)
#define DO8(buf)  DO4(buf); DO4(buf)

UINT32 SubZipEnumator::crc32(UINT32 crc, const UINT8 *buf, UINT32 len)
{ 
	if (buf==NULL) return 0L;
	crc = crc ^ 0xffffffffL;
	while (len >= 8) {DO8(buf); len -= 8;}
	if (len) do {DO1(buf);} while (--len);
	return crc ^ 0xffffffffL;  // (instead of ~c for 64-bit machines)
}

lutime_t SubZipEnumator::filetime2timet(const FILETIME ft)
{ 
	__int64 i = *(__int64*)&ft;
	return (lutime_t)((i-116444736000000000)/10000000);
}

void SubZipEnumator::filetime2dosdatetime(const FILETIME ft, WORD *dosdate,WORD *dostime)
{ // date: bits 0-4 are day of month 1-31. Bits 5-8 are month 1..12. Bits 9-15 are year-1980
	// time: bits 0-4 are seconds/2, bits 5-10 are minute 0..59. Bits 11-15 are hour 0..23
	SYSTEMTIME st; FileTimeToSystemTime(&ft,&st); 
	*dosdate = (WORD)(((st.wYear-1980)&0x7f) << 9);
	*dosdate |= (WORD)((st.wMonth&0xf) << 5);
	*dosdate |= (WORD)((st.wDay&0x1f));
	*dostime = (WORD)((st.wHour&0x1f) << 11);
	*dostime |= (WORD)((st.wMinute&0x3f) << 5);
	*dostime |= (WORD)((st.wSecond*2)&0x1f);
}


ZRESULT SubZipEnumator::GetFileInfo(HANDLE hf, UINT32 *attr, long *size, iztimes *times, UINT32 *timestamp)
{ // The handle must be a handle to a file
	// The date and time is returned in a long with the date most significant to allow
	// unsigned integer comparison of absolute times. The attributes have two
	// high bytes unix attr, and two low bytes a mapping of that to DOS attr.
	//struct stat s; int res=stat(fn,&s); if (res!=0) return false;
	// translate windows file attributes into zip ones.
	BY_HANDLE_FILE_INFORMATION bhi; BOOL res=GetFileInformationByHandle(hf,&bhi);
	if (!res) return ZR_NOFILE;
	DWORD fa=bhi.dwFileAttributes; UINT32 a=FILE_ATTRIBUTE_NORMAL;
	a|=0x80000000;  // normal file
	a|=0x01000000;      // readable

	// now just a small heuristic to check if it's an executable:
	DWORD red, hsize=GetFileSize(hf,NULL); 
	if (hsize>40)
	{ 
		SetFilePointer(hf,0,NULL,FILE_BEGIN); unsigned short magic; ReadFile(hf,&magic,sizeof(magic),&red,NULL);
		SetFilePointer(hf,36,NULL,FILE_BEGIN); unsigned long hpos;  ReadFile(hf,&hpos,sizeof(hpos),&red,NULL);
		if (magic==0x54AD && hsize>hpos+4+20+28)
		{ 
			SetFilePointer(hf,hpos,NULL,FILE_BEGIN); unsigned long signature; ReadFile(hf,&signature,sizeof(signature),&red,NULL);
			if (signature==IMAGE_DOS_SIGNATURE || signature==IMAGE_OS2_SIGNATURE
				|| signature==IMAGE_OS2_SIGNATURE_LE || signature==IMAGE_NT_SIGNATURE)
			{ 
				a |= 0x00400000; // executable
			}
		}
	}
	//
	if (attr!=NULL) *attr = a;
	if (size!=NULL) *size = hsize;
	if (times!=NULL)
	{ // lutime_t is 32bit number of seconds elapsed since 0:0:0GMT, Jan1, 1970.
		// but FILETIME is 64bit number of 100-nanosecs since Jan1, 1601
		times->atime = filetime2timet(bhi.ftLastAccessTime);
		times->mtime = filetime2timet(bhi.ftLastWriteTime);
		times->ctime = filetime2timet(bhi.ftCreationTime);
	}
	if (timestamp!=NULL)
	{ WORD dosdate,dostime;
	filetime2dosdatetime(bhi.ftLastWriteTime,&dosdate,&dostime);
	*timestamp = (WORD)dostime | (((DWORD)dosdate)<<16);
	}
	return ZR_OK;
}


ZRESULT SubZipEnumator::CreateMemory(UINT32 u32Len)
{ 
	if (hmapout!=0 || obuf!=0 || writ!=0 || oerr!=ZR_OK)
		return ZR_NOTINITED;

	if (u32Len ==0) 
		return ZR_MEMSIZE;

	hmapout = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, u32Len, NULL);

	if (hmapout==NULL)
		return ZR_NOALLOC;

	obuf = (UINT8*)MapViewOfFile(hmapout, FILE_MAP_ALL_ACCESS, 0, 0, u32Len);
	if (obuf==0) 
	{
		CloseHandle(hmapout); 
		hmapout=0; 
		return ZR_NOALLOC;
	}
	ocanseek = true;
	opos = 0; mapsize = u32Len;
	return ZR_OK;
}

unsigned SubZipEnumator::sflush(void *param,const UINT8 *buf, unsigned *size)
{ // static
	if (*size==0) return 0;
	SubZipEnumator *zip = (SubZipEnumator*)param;
	unsigned int writ = zip->write(buf,*size);
	if (writ!=0) *size=0;
	return writ;
}
unsigned SubZipEnumator::swrite(void *param,const UINT8 *buf, unsigned size)
{ // static
	if (size==0) return 0;
	SubZipEnumator *zip=(SubZipEnumator*)param; return zip->write(buf,size);
}
unsigned int SubZipEnumator::write(const UINT8 *buf,unsigned int size)
{ 
	if (opos+size>=mapsize) {oerr=ZR_MEMSIZE; return 0;}
	memcpy(obuf+opos, buf, size);
	opos+=size;
	return size;
}

bool SubZipEnumator::oseek(unsigned int pos)
{ 
	if (!ocanseek) 
	{
		oerr=ZR_SEEK; return false;
	}
	if (obuf!=0)
	{ 
		if (pos>=mapsize) {oerr=ZR_MEMSIZE; return false;}
		opos=pos;
		return true;
	}	
	oerr=ZR_NOTINITED; return 0;
}

ZRESULT SubZipEnumator::Close()
{ // if the directory hadn't already been added through a call to GetMemory,
	// then we do it now	
	if (obuf!=0 && hmapout!=0) 
	{
		UnmapViewOfFile(obuf); 
		obuf=0;
	}
	if (hmapout!=0) 
	{
		CloseHandle(hmapout); 
		hmapout=0;
	}
	return ZR_OK;
}

ZRESULT SubZipEnumator::open_handle(HANDLE hf,unsigned int len)
{ 
	hfin=0; bufin=0; selfclosehf=false; crc=CRCVAL_INITIAL; isize=0; csize=0; ired=0;
	if (hf==0 || hf==INVALID_HANDLE_VALUE) return ZR_ARGS;
	ZRESULT res = GetFileInfo(hf,&attr,&isize,&times,&timestamp);
	if (res!=ZR_OK) 
		return res;
	SetFilePointer(hf,0,NULL,FILE_BEGIN); // because GetFileInfo will have screwed it up
	iseekable=true; hfin=hf;
	return ZR_OK;
}
unsigned SubZipEnumator::sread(TState &s,UINT8 *buf,unsigned size)
{ // static
	SubZipEnumator *zip = (SubZipEnumator*)s.param;
	return zip->read(buf,size);
}

unsigned SubZipEnumator::read(UINT8 *buf, unsigned size)
{ 
	if (bufin!=0)
	{ 
		if (posin>=lenin) return 0; // end of input
		UINT32 red = lenin-posin;
		if (red>size) red=size;
		memcpy(buf, bufin+posin, red);
		posin += red;
		ired += red;
		crc = crc32(crc, (UINT8*)buf, red);
		return red;
	}
	else if (hfin!=0)
	{ 
		DWORD red;
		BOOL ok = ReadFile(hfin,buf,size,&red,NULL);
		if (!ok) return 0;
		ired += red;
		crc = crc32(crc, (UINT8*)buf, red);
		return red;
	}
	else {oerr=ZR_NOTINITED; return 0;}
}

ZRESULT SubZipEnumator::iclose()
{
	if (selfclosehf && hfin!=0) CloseHandle(hfin); hfin=0;
	bool mismatch = (isize!=-1 && isize!=ired);
	isize=ired; // and crc has been being updated anyway
	if (mismatch) return ZR_MISSIZE;
	else return ZR_OK;
}

ZRESULT SubZipEnumator::ideflate(TZipFileInfo *zfi)
{ 
	if (state==0) state=new TState();
	// It's a very big object! 500k! We allocate it on the heap, because PocketPC's
	// stack breaks if we try to put it all on the stack. It will be deleted lazily
	state->err=0;
	state->readfunc=sread; state->flush_outbuf=sflush;
	state->param=this; state->level=8; state->seekable=iseekable; state->err=NULL;
	// the following line will make ct_init realise it has to perform the init
	state->ts.static_dtree[0].dl.len = 0;
	// Thanks to Alvin77 for this crucial fix:
	state->ds.window_size=0;
	//  I think that covers everything that needs to be initted.
	bi_init(*state,buf, sizeof(buf), TRUE); // it used to be just 1024-size, not 16384 as here
	ct_init(*state,&zfi->att);
	lm_init(*state,state->level, &zfi->flg);
	UINT32 sz = deflate(*state);
	csize=sz;
	ZRESULT r=ZR_OK; if (state->err!=NULL) r=ZR_FLATE;
	return r;
}

ZRESULT SubZipEnumator::istore()
{ 
	UINT32 size=0;
	for (;;)
	{ unsigned int cin=read(buf,16384); if (cin<=0 || cin==(unsigned int)EOF) break;
	unsigned int cout = write(buf,cin); if (cout!=cin) return ZR_MISSIZE;
	size += cin;
	}
	csize=size;
	return ZR_OK;
}

ZRESULT SubZipEnumator::Add(const TCHAR *odstzn, void *hFileHandle, unsigned int len, UINT32 u32Method)
{ 
	// zip has its own notion of what its names should look like: i.e. dir/file.stuff
 	//TCHAR dstzn[MAX_PATH]; 
	//_tcscpy(dstzn,odstzn);
// 	if (*dstzn==0) return ZR_ARGS;  

	// now open whatever was our input source:
	ZRESULT openres;
	openres = open_handle((HANDLE)hFileHandle, len);

	if (openres!=ZR_OK) return openres;

	// Initialize the local header
	
	ZeroMemory(&zfi, sizeof(TZipFileInfo));
	zfi.nxt=NULL;
	
	strcpy_s(zfi.name, MAX_PATH, "");
	
	//MultiByteToWideChar (CP_OEMCP, 0, zfi.iname, MAX_PATH, dstzn , MAX_PATH );
	CPINFO osCPINFO;
	GetCPInfo(CP_ACP, &osCPINFO);
	WideCharToMultiByte(CP_ACP, 0, odstzn, -1, zfi.iname, MAX_PATH, (LPCSTR)&osCPINFO.DefaultChar, 0);
	
	zfi.nam=strlen(zfi.iname);
	strcpy_s(zfi.zname, MAX_PATH, "");
	zfi.extra=NULL; zfi.ext=0;   // extra header to go after this compressed data, and its length
	zfi.cextra=NULL; zfi.cext=0; // extra header to go in the central end-of-zip directory, and its length
	zfi.comment=NULL; zfi.com=0; // comment, and its length
	zfi.mark = 1;
	zfi.dosflag = 0;
	zfi.att = (UINT16)BINARY;
	zfi.vem = (UINT16)0x17; // 0xB00 is win32 os-code. 0x17 is 23 in decimal: zip 2.3
	zfi.ver = (UINT16)20;    // Needs PKUNZIP 2.0 to unzip it
	zfi.tim = timestamp;
	// Even though we write the header now, it will have to be rewritten, since we don't know compressed size or crc.
	zfi.crc = 0;            // to be updated later
	zfi.flg = 8;            // 8 means 'there is an extra header'. Assume for the moment that we need it.
	zfi.lflg = zfi.flg;     // to be updated later
	zfi.how = (UINT16)u32Method;  // to be updated later
	zfi.siz = (UINT32)(u32Method==STORE && isize>=0 ? isize : 0); // to be updated later
	zfi.len = (UINT32)(isize);  // to be updated later
	zfi.dsk = 0;
	zfi.atx = attr;
	zfi.off = writ+ooffset;         // offset within file of the start of this local record

	// (1) Start by writing the local header:
	if (putlocal(&zfi, swrite, this) != ZE_OK) {iclose(); return ZR_WRITE;}
	writ += 4 + LOCHEAD + (unsigned int)zfi.nam + (unsigned int)zfi.ext;
	if (oerr!=ZR_OK) {iclose(); return oerr;}

	//(2) Write deflated/stored file to zip file
	ZRESULT writeres=ZR_OK;
	if (u32Method==DEFLATE) writeres=ideflate(&zfi);
	else if (u32Method==STORE) writeres=istore();
	//encwriting = false;
	iclose();
	writ += csize;

	// (3) Either rewrite the local header with correct information...
	bool first_header_has_size_right = (zfi.siz==csize);
	zfi.crc = crc;
	zfi.siz = csize;
	zfi.len = isize;
	zfi.how = (UINT16)u32Method;
	if ((zfi.flg & 1) == 0) 
		zfi.flg &= ~8; // clear the extended local header flag
	zfi.lflg = zfi.flg;
	// rewrite the local header:
	if (!oseek(zfi.off-ooffset)) return ZR_SEEK;
	if (putlocal(&zfi, swrite,this) != ZE_OK) return ZR_WRITE;
	if (!oseek(writ)) return ZR_SEEK;
	if (putcentral(&zfi, swrite,this) != ZE_OK) return ZR_WRITE;

	return ZR_OK;
}