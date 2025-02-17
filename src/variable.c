#include "variable.h"

bool output_friendly(variable v) {
    return (v.type == OUTPUT || v.type == DISCARD || v.type == TEMP);
}

bool input_friendly(variable v) {
    return (v.type == INPUT || v.type == CONST || v.type == TEMP);
}


const char* variable_type_to_char(var_type type) {
    switch(type) {
        case INPUT:
            return "INPUT";
        case OUTPUT:
            return "OUTPUT";
        case TEMP:   
            return "TEMP";
        case DISCARD:
            return "DISCARD";
        case CONST:
            return "CONST";
        default:
            return "UNKNOWN";
    }
}

void print_var(FILE* file,variable* v) {
    if(v != NULL) {
        fprintf(file,"[%s, ", v->letter);
        switch(v->value) {
            case var_true:
                fprintf(file, "true (%p)",(void*)v);
                break;
            case var_false:
                fprintf(file, "false (%p)",(void*)v);
                break;
            case var_uneval:
                fprintf(file, "unevaluated (%p)",(void*)v);
                break;
            default:
                fprintf(file, "error value (%p)",(void*)v);
        }
        fprintf(file,", %s",variable_type_to_char(v->type));
        fprintf(file,"]");
    } else {
        fprintf(file, "[NULL]");
    }
}

void print_bool(FILE* file,bool* v) {
    fprintf(file,"[");
    if(*v) {
            fprintf(file, "true (%p)]",(void*)v);
    } else {
            fprintf(file, "false (%p)]",(void*)v);
    }
}
