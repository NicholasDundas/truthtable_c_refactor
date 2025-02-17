#ifndef GATE_H
#define GATE_H

#include <stdlib.h>
#include <stdio.h>

#include "variable.h"
typedef struct Circuit circuit;

typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER, CIR_PTR } gate_type; //Defines the types of gates

// Struct gate
//
// gate_type kind is an enum that defines the type of gate we are looking at
// size is used for either the decoder or multiplexer to determine its size
// params holds pointers to integers so that mutliple Gates may point to the same variable
//
// MEMORY LAYOUT OF GATES
// - index i refers to *param[i] where that represents a variable of an appropiate type
// - Always follows inputs first followed by outputs
//
// NOT, PASS
// index 0 is input
// index 1 is output
//
// AND, OR, XOR, NAND, NOR
// index 0,1 is input
// index 2 is output
//
// DECODER
// 
// MULTIPLEXER
//
typedef struct {
    gate_type kind; //type of gate
    size_t size; // indicates size of inputs
    size_t total_size; //total size of params

    size_t depth; //depth of circuit determined by MAX(i1,i2,i3...) where i is an input param
    variable** params; // length determined by kind and size;
    // includes inputs and outputs, indicated by variable numbers
    circuit* cir_ptr;
} gate;

#define GATE_PARAM_BOOL(GATE_PTR,INDEX) (GATE_PTR)->params[(INDEX)]->value


//returns true if all inputs have been evaluated before otherwise false
bool is_evaluable(gate g);

const char* gate_type_to_char(gate_type type);


typedef enum { GATE_RUN_SUCCESS, INVALID_GATE_PASSED, NULL_GATE_PASSED  } gate_return_err;

//Debug printing of a gate
//Example:
//GATE: AND
//  INPUT
//  - [NAME: Variable1, true (0xA421F412), INPUT]
//  - [NAME: Variable2, false (0xA421F412), INPUT]
//  OUTPUT
//  - [NAME: Variable3, false (0xA421F412), OUTPUT]
void print_gate(FILE* file,gate g);

//Preforms gate action on the gate pointed. returns the result 
gate_return_err gate_return(gate* g);
#endif
