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

    //Convention 1?: LSB is history tables are the most recent bit added to the history
    //Convention 2?: Predictor counter state values are in the least significant bits

    // 1024 x 10 bit local history table
    uint16_t local_history_table[1024];
    // 1024 x 3 bit local predictor (3 bit saturating counter)
    uint8_t local_predictor[1024];
    // 1 x 12 bit path history table
    uint16_t path_history_table;
    // 4096 x 2 bit global predictor (2 bit saturating counter)
    uint8_t global_predictor[4096];
    // 4096 x 2 bit choice predictor (2 bit saturating counter)
    uint8_t choice_predictor[4096];
};

#endif // PREDICTOR_H_SEEN
