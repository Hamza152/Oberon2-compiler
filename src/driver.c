#include "parser.h"
#include <stdio.h>
#include <stdarg.h>
#include "utils.h"
#include "symbol_table.h"
#include "semantizer.h"
#include "error.h"
#include "bytecode.h"
#include "vmware.h"

int main( int argc, char **argv )
{
	++argv, --argc;
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;

	stderr=stdout;

	AST_Module* mod=(AST_Module*)malloc(sizeof(AST_Module));

	if(!module(&mod))
		return 1;


	//print_module(mod);

	semantizer(mod);
	print_errors();
	if(num_errors)
		return 1;

	Byte_Code* bytecode=gen_bytecode(mod);


	db_tree_lvl=0;
	//printf("\nGenerated Bytecode : \n\n");
	//print_bytecode(bytecode);

	//interpret_bytecode(bytecode);
	//printf("\n Results:  \n\n");
	//st_print();




	//db_tree_lvl=0;
	//printf("\nGenerated Bytecode : \n\n");
	//print_bytecode(bytecode);
	
	if(argc>1 && !strcmp(argv[1],"-inter"))
	{
		interpret_bytecode(bytecode);
		//st_print();
	}
	//printf("\n Results:  \n\n");

	

	save_bytecode_file(bytecode,argv[0]);


	return 0;
}