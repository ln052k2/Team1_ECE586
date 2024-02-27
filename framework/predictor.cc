/* Author: Mark Faust;
 * Description: This file defines the two required functions for the branch predictor.
*/

#include "predictor.h"



    bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os)
        {
			
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
