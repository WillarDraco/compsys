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

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string translation;
    string reg;

    if (segment == "this") {
        reg = "THIS";
    } else if(segment == "that") {
        reg = "THAT";

    } else if(segment == "argument") {
        reg = "ARG";

    } else if(segment == "local") {
        reg = "LCL";

    } else if(segment == "static") {
        reg = to_string(16 + offset);

    } else if(segment == "pointer") {
        reg = "R" + to_string(3 + offset);

    } else if(segment == "temp") {
        reg = "R" + to_string(5 + offset);

    } else if(segment == "constant") {
        reg = to_string(offset);
    } else {
        reg = "";
    }

    string ofs = to_string(offset);

    if (segment == "constant" || segment == "static" || segment == "pointer" || segment == "temp") {
        translation.append("@" + reg + "\n");
        translation.append("push " + segment + " " + ofs + "\n");
        (segment == "constant") ? translation.append("D=A") : translation.append("D=M");
    } else if (segment == "local" || segment == "this" || segment == "that" || segment == "argument") {
        translation.append("@" + reg);
        translation.append("push " + segment + " " + ofs + "\n");
        translation.append("D=M\n");
        translation.append("@" + ofs + "\n");
        translation.append("A=D+A\n");
        translation.append("D=M\n");
    }

    translation.append("@SP\n");
    translation.append("A=M\n");
    translation.append("M=D\n");
    translation.append("@SP\n");
    translation.append("M=M+1");

    return translation;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
    string translation;
    string reg;

    if (segment == "this") {
        reg = "THIS";
    } else if(segment == "that") {
        reg = "THAT";

    } else if(segment == "argument") {
        reg = "ARG";

    } else if(segment == "local") {
        reg = "LCL";

    } else if(segment == "static") {
        reg = to_string(16 + offset);

    } else if(segment == "pointer") {
        reg = "R" + to_string(3 + offset);

    } else if(segment == "temp") {
        reg = "R" + to_string(5 + offset);

    } else if(segment == "constant") {
        reg = to_string(offset);
    } else {
        reg = "";
    }

    string ofs = to_string(offset);

    if (segment == "constant") {
        return "";
    }

    if (segment == "static" || segment == "pointer" || segment == "temp") {
        translation.append("D=A\n");
    } else if (segment == "local" || segment == "this" || segment == "that" || segment == "argument") {
        translation.append("D=M\n");
        translation.append("@" + ofs + "\n");
        translation.append("D=D+A\n");
    }

    translation.append("@R13\n");
    translation.append("M=D\n");
    translation.append("@SP\n");
    translation.append("AM=M-1\n");
    translation.append("D=M\n");
    translation.append("@R13\n");
    translation.append("A=M\n");
    translation.append("M=D");

    return translation;
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