/*
GROUP NO. = 46
2017A7PS0006P PIKLU PAUL
2017A7PS0007P RAJABABU SAIKIA
2017A7PS0090P SAURAV VIRMANI
2017A7PS0111P SIDDHANT KHARBANDA
2017A7PS0275P SREYAS RAVICHANDRAN
*/
#define MAX_RHS 10

typedef struct error_list{
	struct error_list* next;
	Token* tk;
}error_list;

error_list* errors;

error_list* parseTree();

