/* Author: Mark Faust;
 * Description: This file defines the two required functions for the branch predictor.
*/

#include "predictor.h"



    bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os)
        {

		// true = predicting taken, false = predicting not taken
		bool local_prediction;		// local prediction result
		bool global_prediction;		// global prediction result
		bool choice_prediction; 	// tournament choice (false = local, true = global)

		// Get local history for the current branch and make sure the history is only 10 bits wide
		uint16_t curr_local_history = local_history_table[((br->instruction_addr & 0xFFF) >> 2)];
		curr_local_history &= 0x3FF;

		// Get local prediction
		if ((local_predictor[curr_local_history] & 0x4) > 0) {
			local_prediction = true;
		}
		else {
			local_prediction = false;
		}

		// Get global prediction
		if ((global_predictor[(path_history_table & 0xFFF)] & 0x2) > 0) {
			global_prediction = true;
		}
		else {
			global_prediction = false;
		}

		// Get choice prediction
		if ((choice_predictor[(path_history_table & 0xFFF)] & 0x2) > 0){
			choice_prediction = true;
		}
		else {
			choice_prediction = false;
		}

		// Get branch prediction
		if (choice_prediction) {
			return global_prediction;
		}
		else {
			return local_prediction;
		}

		//void init();		 	// init the branch record
		//void debug_print(); 		// print info in branch record (for debugging)
		//uint instruction_addr; 	// the branch's PC (program counter)
		//uint branch_target; 		// target of branch if it's taken; unconditional are always taken
		//uint instruction_next_addr;	// PC of the static instruction following the branch
		//bool is_indirect; 		// true if target is computed; false if it's PC-rel; returns are also considered indirect
		//bool is_conditional; 		// true if branch is conditional; false otherwise
		//bool is_call; 		// true if branch is a call; false otherwise
		//bool is_return; 		// true if branch is a return; false otherwise
        }











    // Update the predictor after a prediction has been made.  This should accept
    // the branch record (br) and architectural state (os), as well as a third
    // argument (taken) indicating whether or not the branch was taken.
    void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken)
        {
		/* replace this code with your own */
			printf("%1d\n",taken);

        }
