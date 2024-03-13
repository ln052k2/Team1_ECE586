/* Author: Mark Faust
 *
 * C version of predictor file
*/

#ifndef PREDICTOR_H_SEEN
#define PREDICTOR_H_SEEN

#include <cstddef>
#include <cstring>
#include <inttypes.h>
#include <vector>
#include "op_state.h"   // defines op_state_c (architectural state) class
#include "tread.h"      // defines branch_record_c class

class PREDICTOR
{
public:
    	bool get_prediction(const branch_record_c* br, const op_state_c* os);

    	void update_predictor(const branch_record_c* br, const op_state_c* os, bool taken);

				/* ----- Paper equations ---- */
	// optimal global path history length (h bits) to threshold value (theta) equation
	// theta = floor(1.93 * h + 14)
	//
	// Note: The paper suggests that the global path histry be 28 bits wide and that the
	// threshold value should be 68 for a 4KB budget predictor. To meet requirements,
	// the global path history width is 32 bits (to be a power of 2) and thus the
	// threshold value is 75.

	// 32 bit global path history
	uint32_t globalPathH;
	// threshold value
	uint8_t threshold = 75;
	// 8 bit x 256 perceptron entry x 8 weight perceptron table (2KB total)
	// 8 PC bits --> 256 entries, one 8-bit weight for each bit taken from PC (8 x 8 bit)
	int8_t perceptron[256][8];
};

#endif // PREDICTOR_H_SEEN
