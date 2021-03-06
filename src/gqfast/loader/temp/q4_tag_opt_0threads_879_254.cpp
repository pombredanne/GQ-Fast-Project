#ifndef q4_tag_opt_0threads_879_254_
#define q4_tag_opt_0threads_879_254_

#include "../fastr_index.hpp"
#include "../global_vars.hpp"

#define NUM_THREADS 1
#define BUFFER_POOL_SIZE 2

using namespace std;

static int* R;
static int* RC;

static uint64_t* q4_tag_opt_0threads_879_254_intersection_buffer;

static int* term1_col1_huffman_tree_array;
static bool* term1_col1_huffman_terminator_array;

extern inline void q4_tag_opt_0threads_879_254_doc1_col0_intersection0_decode_BB(unsigned char* doc1_col0_intersection_ptr_0, uint32_t doc1_col0_bytes_intersection0, uint32_t & doc1_intersection0_fragment_size) __attribute__((always_inline));

extern inline void q4_tag_opt_0threads_879_254_doc1_col0_intersection1_decode_BB(unsigned char* doc1_col0_intersection_ptr_1, uint32_t doc1_col0_bytes_intersection1, uint32_t & doc1_intersection1_fragment_size) __attribute__((always_inline));

extern inline void q4_tag_opt_0threads_879_254_intersection(uint32_t doc1_intersection0_fragment_size, uint32_t doc1_intersection1_fragment_size, uint32_t & q4_tag_opt_0threads_879_254_intersection_size) __attribute__((always_inline));

extern inline void q4_tag_opt_0threads_879_254_term1_col0_decode_BB(unsigned char* term1_col0_ptr, uint32_t term1_col0_bytes, uint32_t & term1_fragment_size) __attribute__((always_inline));

extern inline void q4_tag_opt_0threads_879_254_term1_col1_decode_Huffman(unsigned char* term1_col1_ptr, uint32_t term1_fragment_size) __attribute__((always_inline));

void q4_tag_opt_0threads_879_254_doc1_col0_intersection0_decode_BB(unsigned char* doc1_col0_intersection_ptr_0, uint32_t doc1_col0_bytes_intersection0, uint32_t & doc1_intersection0_fragment_size) {

	buffer_arrays[3][0][0][0][0] = 0;

	int shiftbits = 0;
	do { 
		doc1_col0_bytes_intersection0--;
		uint32_t next_seven_bits = *doc1_col0_intersection_ptr_0 & 127;
		next_seven_bits = next_seven_bits << shiftbits;
		buffer_arrays[3][0][0][0][0] |= next_seven_bits;
		shiftbits += 7;
	} while (!(*doc1_col0_intersection_ptr_0++ & 128));
	doc1_intersection0_fragment_size++;

	while (doc1_col0_bytes_intersection0 > 0) {
		shiftbits = 0;
		uint32_t result = 0;

		do {

			doc1_col0_bytes_intersection0--;
			uint32_t next_seven_bits = *doc1_col0_intersection_ptr_0 & 127;
			next_seven_bits = next_seven_bits << shiftbits;
			result |= next_seven_bits;
			shiftbits += 7;

		} while (!(*doc1_col0_intersection_ptr_0++ & 128));
		buffer_arrays[3][0][0][0][doc1_intersection0_fragment_size] = buffer_arrays[3][0][0][0][doc1_intersection0_fragment_size-1]+1+result;
		doc1_intersection0_fragment_size++;
	}
}

void q4_tag_opt_0threads_879_254_doc1_col0_intersection1_decode_BB(unsigned char* doc1_col0_intersection_ptr_1, uint32_t doc1_col0_bytes_intersection1, uint32_t & doc1_intersection1_fragment_size) {

	buffer_arrays[3][0][0][1][0] = 0;

	int shiftbits = 0;
	do { 
		doc1_col0_bytes_intersection1--;
		uint32_t next_seven_bits = *doc1_col0_intersection_ptr_1 & 127;
		next_seven_bits = next_seven_bits << shiftbits;
		buffer_arrays[3][0][0][1][0] |= next_seven_bits;
		shiftbits += 7;
	} while (!(*doc1_col0_intersection_ptr_1++ & 128));
	doc1_intersection1_fragment_size++;

	while (doc1_col0_bytes_intersection1 > 0) {
		shiftbits = 0;
		uint32_t result = 0;

		do {

			doc1_col0_bytes_intersection1--;
			uint32_t next_seven_bits = *doc1_col0_intersection_ptr_1 & 127;
			next_seven_bits = next_seven_bits << shiftbits;
			result |= next_seven_bits;
			shiftbits += 7;

		} while (!(*doc1_col0_intersection_ptr_1++ & 128));
		buffer_arrays[3][0][0][1][doc1_intersection1_fragment_size] = buffer_arrays[3][0][0][1][doc1_intersection1_fragment_size-1]+1+result;
		doc1_intersection1_fragment_size++;
	}
}
void q4_tag_opt_0threads_879_254_intersection(uint32_t doc1_intersection0_fragment_size, uint32_t doc1_intersection1_fragment_size, uint32_t & q4_tag_opt_0threads_879_254_intersection_size) { 

	if (doc1_intersection0_fragment_size == 0) { return; }

	if (doc1_intersection1_fragment_size == 0) { return; }

	uint32_t intersection_index = 0;
	uint32_t* its = new uint32_t[2]();
	bool end = false;

	while(!end) {

		bool match = true;
		while (1) {
			if (buffer_arrays[3][0][0][0][its[0]]  != buffer_arrays[3][0][0][1][its[1]]) {
				match = false;
				break;
			}

			break;
		}

		if (match) {
			q4_tag_opt_0threads_879_254_intersection_buffer[intersection_index++] = buffer_arrays[3][0][0][0][its[0]];
			while(1) {
				if (++its[0] == doc1_intersection0_fragment_size) {
					end = true;
					break;
				}
				if (++its[1] == doc1_intersection1_fragment_size) {
					end = true;
					break;
				}

				break;
			}
		}
		else {

			uint64_t smallest = buffer_arrays[3][0][0][0][its[0]];
			int index_of_smallest = 0;
			uint32_t fragment_size_of_smallest = doc1_intersection0_fragment_size;

			if (smallest > buffer_arrays[3][0][0][1][its[1]]) {
				smallest = buffer_arrays[3][0][0][1][its[1]];
				index_of_smallest = 1;
				fragment_size_of_smallest = doc1_intersection1_fragment_size;
			}

			if (++its[index_of_smallest] == fragment_size_of_smallest) {
				end = true;
			}
		}
	}

	delete[] its;
	q4_tag_opt_0threads_879_254_intersection_size = intersection_index;
}

void q4_tag_opt_0threads_879_254_term1_col0_decode_BB(unsigned char* term1_col0_ptr, uint32_t term1_col0_bytes, uint32_t & term1_fragment_size) {

	buffer_arrays[2][0][0][0][0] = 0;

	int shiftbits = 0;
	do { 
		term1_col0_bytes--;
		uint32_t next_seven_bits = *term1_col0_ptr & 127;
		next_seven_bits = next_seven_bits << shiftbits;
		buffer_arrays[2][0][0][0][0] |= next_seven_bits;
		shiftbits += 7;
	} while (!(*term1_col0_ptr++ & 128));
	term1_fragment_size++;

	while (term1_col0_bytes > 0) {
		shiftbits = 0;
		uint32_t result = 0;

		do {

			term1_col0_bytes--;
			uint32_t next_seven_bits = *term1_col0_ptr & 127;
			next_seven_bits = next_seven_bits << shiftbits;
			result |= next_seven_bits;
			shiftbits += 7;

		} while (!(*term1_col0_ptr++ & 128));
		buffer_arrays[2][0][0][0][term1_fragment_size] = buffer_arrays[2][0][0][0][term1_fragment_size-1]+1+result;
		term1_fragment_size++;
	}
}

void q4_tag_opt_0threads_879_254_term1_col1_decode_Huffman(unsigned char* term1_col1_ptr, uint32_t term1_fragment_size) {

	bool* terminate_start = &(term1_col1_huffman_terminator_array[0]);
	int* tree_array_start = &(term1_col1_huffman_tree_array[0]);

	int mask = 0x100;

	for (uint32_t i=0; i<term1_fragment_size; i++) {

		bool* terminator_array = terminate_start;
		int* tree_array = tree_array_start;

		while(!*terminator_array) { 

			char direction = *term1_col1_ptr & (mask >>= 1);

			if (mask == 1) { 
				mask = 0x100;
				term1_col1_ptr++;
			}

			terminator_array += *tree_array;
			tree_array += *tree_array;

			if (direction) {
				terminator_array++;
				tree_array++;
			}
		}

		buffer_arrays[2][1][0][0][i] = *tree_array;
	}
}

extern "C" int* q4_tag_opt_0threads_879_254(int** null_checks) {

	benchmark_t1 = chrono::steady_clock::now();

	int max_frag;

	max_frag = metadata.idx_max_fragment_sizes[2];
	for(int i=0; i<metadata.idx_num_encodings[2]; i++) {
		for (int j=0; j<NUM_THREADS; j++) {
			buffer_arrays[2][i][j] = new uint64_t*[BUFFER_POOL_SIZE];
			for (int k=0; k<BUFFER_POOL_SIZE; k++) {
				buffer_arrays[2][i][j][k] = new uint64_t[max_frag];
			}
		}
	}

	max_frag = metadata.idx_max_fragment_sizes[3];
	for(int i=0; i<metadata.idx_num_encodings[3]; i++) {
		for (int j=0; j<NUM_THREADS; j++) {
			buffer_arrays[3][i][j] = new uint64_t*[BUFFER_POOL_SIZE];
			for (int k=0; k<BUFFER_POOL_SIZE; k++) {
				buffer_arrays[3][i][j][k] = new uint64_t[max_frag];
			}
		}
	}

	RC = new int[metadata.idx_domains[2][0]]();
	R = new int[metadata.idx_domains[2][0]]();


	q4_tag_opt_0threads_879_254_intersection_buffer = new uint64_t[metadata.idx_max_fragment_sizes[3]];

	term1_col1_huffman_tree_array = idx[2]->huffman_tree_array[1];
	term1_col1_huffman_terminator_array = idx[2]->huffman_terminator_array[1];

	uint32_t* row_doc1_intersection0 = idx[3]->index_map[879];
	uint32_t doc1_col0_bytes_intersection0 = idx[3]->index_map[879+1][0] - row_doc1_intersection0[0];
	unsigned char* doc1_col0_intersection_ptr_0 = &(idx[3]->fragment_data[0][row_doc1_intersection0[0]]);
	uint32_t doc1_intersection0_fragment_size = 0;
	q4_tag_opt_0threads_879_254_doc1_col0_intersection0_decode_BB(doc1_col0_intersection_ptr_0, doc1_col0_bytes_intersection0, doc1_intersection0_fragment_size);

	uint32_t* row_doc1_intersection1 = idx[3]->index_map[254];
	uint32_t doc1_col0_bytes_intersection1 = idx[3]->index_map[254+1][0] - row_doc1_intersection1[0];
	unsigned char* doc1_col0_intersection_ptr_1 = &(idx[3]->fragment_data[0][row_doc1_intersection1[0]]);
	uint32_t doc1_intersection1_fragment_size = 0;
	q4_tag_opt_0threads_879_254_doc1_col0_intersection1_decode_BB(doc1_col0_intersection_ptr_1, doc1_col0_bytes_intersection1, doc1_intersection1_fragment_size);

	uint32_t q4_tag_opt_0threads_879_254_intersection_size = 0;
	q4_tag_opt_0threads_879_254_intersection(doc1_intersection0_fragment_size, doc1_intersection1_fragment_size, q4_tag_opt_0threads_879_254_intersection_size);

	for (uint32_t q4_tag_opt_0threads_879_254_intersection_it= 0; q4_tag_opt_0threads_879_254_intersection_it<q4_tag_opt_0threads_879_254_intersection_size; q4_tag_opt_0threads_879_254_intersection_it++) {

		uint32_t* row_term1 = idx[2]->index_map[q4_tag_opt_0threads_879_254_intersection_buffer[q4_tag_opt_0threads_879_254_intersection_it]];
		uint32_t term1_col0_bytes = idx[2]->index_map[q4_tag_opt_0threads_879_254_intersection_buffer[q4_tag_opt_0threads_879_254_intersection_it]+1][0] - row_term1[0];
		if(term1_col0_bytes) {

			unsigned char* term1_col0_ptr = &(idx[2]->fragment_data[0][row_term1[0]]);
			uint32_t term1_fragment_size = 0;
			q4_tag_opt_0threads_879_254_term1_col0_decode_BB(term1_col0_ptr, term1_col0_bytes, term1_fragment_size);

			unsigned char* term1_col1_ptr = &(idx[2]->fragment_data[1][row_term1[1]]);
			q4_tag_opt_0threads_879_254_term1_col1_decode_Huffman(term1_col1_ptr, term1_fragment_size);

			for (uint32_t term1_it = 0; term1_it < term1_fragment_size; term1_it++) {
				uint32_t term1_col0_element = buffer_arrays[2][0][0][0][term1_it];
				unsigned char term1_col1_element = buffer_arrays[2][1][0][0][term1_it];

				RC[term1_col0_element] = 1;
				R[term1_col0_element] += term1_col1_element;
			}
		}
	}


	for (int j=0; j<metadata.idx_num_encodings[2]; j++) {
		for (int k=0; k<NUM_THREADS; k++) {
			for (int l=0; l<BUFFER_POOL_SIZE; l++) {
				delete[] buffer_arrays[2][j][k][l];
			}
			delete[] buffer_arrays[2][j][k];
		}
	}
	for (int j=0; j<metadata.idx_num_encodings[3]; j++) {
		for (int k=0; k<NUM_THREADS; k++) {
			for (int l=0; l<BUFFER_POOL_SIZE; l++) {
				delete[] buffer_arrays[3][j][k][l];
			}
			delete[] buffer_arrays[3][j][k];
		}
	}
	delete[] q4_tag_opt_0threads_879_254_intersection_buffer;


	*null_checks = RC;
	return R;

}

#endif

