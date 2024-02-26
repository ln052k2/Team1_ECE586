/* Author: Mark Faust;
 * Description: This file defines the two required functions for the branch predictor.
*/

#include "predictor.h"
// #define DEBUG

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
			// Get current local history
			uint16_t curr_local_history = local_history_table[((br->instruction_addr & 0xFFF) >> 2)];
			#ifdef DEBUG
			printf("\n%1d\n",taken);
			printf("Instruction address: %x\n", br->instruction_addr);
			printf("Index: %x\n", ((br->instruction_addr & 0xFFF) >> 2));
			printf("Curr_local_history: %x\n", curr_local_history);
			printf("Path_history: %x\n", path_history_table);
			printf("Choice predictor state: %x\n", choice_predictor[(path_history_table & 0xFFF)]);
			printf("Local predictor state: %x\n", local_predictor[curr_local_history]);
			printf("Global predictor state: %x\n", global_predictor[path_history_table & 0xFFF]);
			#endif

			// Update choice predictor
			bool local_prediction = (local_predictor[curr_local_history] & 0x4) >> 2;
			bool global_prediction = (global_predictor[path_history_table & 0xFFF] & 0x2) >> 1;
			if (global_prediction != local_prediction) // only update choice predictor if local and global differ
			{
				if ((global_prediction == taken) & (choice_predictor[(path_history_table & 0xFFF)] < 3)) {
					choice_predictor[(path_history_table & 0xFFF)]++;
				}
				else if ((global_prediction != taken) & (choice_predictor[(path_history_table & 0xFFF)] > 0)) {
					choice_predictor[(path_history_table & 0xFFF)]--;
				}
			}
			#ifdef DEBUG
			printf("Global: %d, Local: %d\n", global_prediction, local_prediction);
			printf("Updated choice predictor state: %x\n", choice_predictor[(path_history_table & 0xFFF)]);
			#endif

			// Update local predictor
			if ((taken) && (local_predictor[curr_local_history] < 7)) {
				local_predictor[curr_local_history]++;
			}
			else if ((!taken) && (local_predictor[curr_local_history] > 0)) {
				local_predictor[curr_local_history]--;
			}
			#ifdef DEBUG
			printf("Updated local predictor state: %x\n", local_predictor[curr_local_history]);
			#endif
		
			// Update global predictor
			if ((taken) && (global_predictor[path_history_table & 0xFFF] < 3)) {
				global_predictor[path_history_table]++;
			}
			else if ((!taken) && (global_predictor[path_history_table & 0xFFF] > 0)) {
				global_predictor[path_history_table]--;
			}
			#ifdef DEBUG
			printf("Updated global predictor state: %x\n", global_predictor[path_history_table & 0xFFF]);
			#endif

			// Update global and local history
			path_history_table <<= 1;
			curr_local_history <<= 1;
			if (taken) {
				path_history_table |= 1;
				curr_local_history |= 1;
			}
			else { // might not be necessary since left shift fills 0
				path_history_table &= ~1;
				curr_local_history &= ~1;
			}

			path_history_table &= 0xFFF; // make sure global history is only 12 bits wide
			curr_local_history &= 0x3FF; // make sure local history is only 10 bits wide
			local_history_table[((br->instruction_addr & 0xFFF) >> 2)] = curr_local_history;			
			#ifdef DEBUG
			printf("Updated local history: %x\n", curr_local_history);
			printf("Updated global history: %x\n", path_history_table);
			#endif

        }
