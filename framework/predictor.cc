/* Author: Mark Faust;
 * Description: This file defines the two required functions for the branch predictor.
*/
// #define DEBUG
#include "predictor.h"


    bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os)
        {
		// Variable Declarations
		uint16_t branchAddr = (br->instruction_addr >> 2) & 0x3FF;
		uint16_t hash = (bhr ^ branchAddr) & 0x3FF;
		bool phtResult;
		bool biasResult;

		// Gather PHT prediction on if bias bit is correct
		if ((pht[hash] & 0x3) > 1) {
			phtResult = true;
		}
		else {
			phtResult = false;
		}

		// Gather what the bias bit's branch prediction
		biasResult = biases[branchAddr];

		//
		if (biasResult != phtResult) {
			return false;
		}
		else {
			return true;
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

			// Variable Declarations
			uint16_t branchAddr = (br->instruction_addr >> 2) & 0x3FF;
			uint16_t hash = (bhr ^ branchAddr) & 0x3FF;
			uint16_t tag = (br->instruction_addr >> 12) & 0xFFFF;

			// Update BTB table
			if (tags[branchAddr] != tag) {
				tags[branchAddr] = tag;
				biases[branchAddr] = taken;
			}

			// if (!accessed[branchAddr]) {
			// 	accessed[branchAddr] = 1;
			// 	biases[branchAddr] = taken;
			// }

			// Update branch history register
			bhr <<= 1;
			if (taken) {
				bhr |= 1;
			} else {
				bhr &= ~1;
			}

			// Update pattern history table
			if ((taken == biases[branchAddr]) && (pht[hash] < 3)){
				pht[hash]++;
			}
			else if ((taken != biases[branchAddr]) && (pht[hash] > 0)) {
				pht[hash]--;
			}
        }
