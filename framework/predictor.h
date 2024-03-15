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

	// 10 bit branch history register
	unint16_t bhr;
	// 1024 x 2 bit pattern history table
	uint8_t pht[1024];
	// 1024 x 16 bit tag array
	uint16_t tags[1024];
	// 1024 x 1 bit bias array
	bool biases[1024];
};

#endif // PREDICTOR_H_SEEN
