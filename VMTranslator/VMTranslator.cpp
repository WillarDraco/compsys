#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

string regDecode(string segment, int offset) {
    if (segment == "this") {
        return "THIS";
    } else if(segment == "that") {
        return "THAT";

    } else if(segment == "argument") {
        return "ARG";

    } else if(segment == "local") {
        return "LCL";

    } else if(segment == "static") {
        return to_string(16 + offset);

    } else if(segment == "pointer") {
        return "R" + to_string(3 + offset);

    } else if(segment == "temp") {
        return "R" + to_string(5 + offset);

    } else if(segment == "constant") {
        return to_string(offset);
    } else {
        return "";
    }
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    Filestr translation;
    string reg = regDecode(segment, offset);
    string ofs = to_string(offset);

    if (segment == "constant" || segment == "static" || segment == "pointer" || segment == "temp") {
        translation.ins("@" + reg, "push " + segment + " " + ofs);
        (segment == "constant") ? translation.ins("D=A") : translation.ins("D=M");
    } else if (segment == "local" || segment == "this" || segment == "that" || segment == "argument") {
        translation.ins("@" + reg, "push " + segment + " " + ofs);
        translation.ins("D=M");
        translation.ins("@" + ofs);
        translation.ins("A=D+A");
        translation.ins("D=M");
    }

    translation.ins("@sp");
    translation.ins("A=M");
    translation.ins("M=D");
    translation.ins("@SP");
    translation.ins("M=M+1");

    return translation.str();
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
    Filestr translation;
    string reg = regDecode(segment, offset);
    string ofs = to_string(offset);

    if (segment == "constant") {
        return "";
    }

    if (segment == "static" || segment == "pointer" || segment == "temp") {
        translation.ins("D=A");
    } else if (segment == "local" || segment == "this" || segment == "that" || segment == "argument") {
        translation.ins("D=M");
        translation.ins("@" + ofs);
        translation.ins("D=D+A");
    }

    translation.ins("R13");
    translation.ins("M=D");
    translation.ins("@SP");
    translation.ins("AM=M-1");
    translation.ins("D=M");
    translation.ins("@R13");
    translation.ins("A=M");
    translation.ins("M=D");

    return translation.str();
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}