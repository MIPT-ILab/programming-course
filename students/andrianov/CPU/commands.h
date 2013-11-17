

SET_CMD_( PUSH   , 1 , { cpu->position++; CPU_push ( cpu, cpu->code[cpu->position] ); cpu->position++;} )
SET_CMD_( PUSH_AX, 2 , { float ax = cpu->ax; CPU_push ( cpu, ax ); cpu->position++;} )
SET_CMD_( POP    , 3 , { CPU_pop ( cpu ); cpu->position++;})

SET_CMD_( ADD    , 4 , { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu );\
                         CPU_push ( cpu, a + b ); cpu->position++;} )
SET_CMD_( SUB    , 5 , { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu );\
                         CPU_push ( cpu, b - a ); cpu->position++; } )
SET_CMD_( DIV    , 6 , { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu );\
                         CPU_push ( cpu, b / a ); cpu->position++; } )

SET_CMD_( MUL    , 7 , { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu );\
                         CPU_push ( cpu, a * b ); cpu->position++; } )
SET_CMD_( SIN    , 8 , { float a = CPU_pop ( cpu );\
                         CPU_push ( cpu, sin ( a ) ); cpu->position++; } )
SET_CMD_( COS    , 9 , { float a = CPU_pop ( cpu );\
                         CPU_push ( cpu, cos ( a ) ); cpu->position++; } )

SET_CMD_( TAN    , 10, { float a = CPU_pop ( cpu );\
                         CPU_push ( cpu, tan ( a ) );cpu->position++; } )
SET_CMD_( POW    , 11, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu );\
                         CPU_push ( cpu, pow ( a, b ) ); cpu->position++; } )
SET_CMD_( END    , 12, { } )

SET_CMD_( POP_AX , 13, { float ax = CPU_pop ( cpu ); CPU_mov_ax ( cpu, ax ); cpu->position++; } )
SET_CMD_( OUT    , 14, { float a = CPU_pop (cpu ); printf( "%f\n", a ); cpu->position++; })
SET_CMD_( JMP    , 15, { cpu->position = (int)cpu->code [ cpu->position + 1 ] ; })

SET_CMD_( JE     , 16, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a == b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ]; } \
                         else { cpu->position = cpu->position + 2 ;} })
SET_CMD_( JNE    , 17, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a != b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ] ; } \
                         else { cpu->position = cpu->position + 2 ;} })
SET_CMD_( JA     , 18, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a > b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ] ; } \
                         else { cpu->position = cpu->position + 2 ;} })

SET_CMD_( JAE    , 19, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a >= b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ]; } \
                         else { cpu->position = cpu->position + 2 ;} })
SET_CMD_( JB     , 20, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a < b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ] ; } \
                         else { cpu->position = cpu->position + 2 ;} })
SET_CMD_( JBE    , 21, { float a = CPU_pop ( cpu ); float b = CPU_pop ( cpu ); \
                         if ( a <= b ){ cpu->position = (int)cpu->code [ cpu->position + 1 ] ; } \
                         else { cpu->position = cpu->position + 2 ;} })

SET_CMD_( PUSH_BX, 22, { float bx = cpu->bx; CPU_push ( cpu, bx ); cpu->position++;} )
SET_CMD_( POP_BX , 23, { float bx = CPU_pop ( cpu ); CPU_mov_bx ( cpu, bx ); cpu->position++; } )
SET_CMD_( PUSH_CX, 24, { float cx = cpu->cx; CPU_push ( cpu, cx ); cpu->position++;} )

SET_CMD_( POP_CX , 25, { float cx = CPU_pop ( cpu ); CPU_mov_cx ( cpu, cx ); cpu->position++; } )
SET_CMD_( SQRT   , 26, { float a = CPU_pop ( cpu ); CPU_push ( cpu, sqrt(a) ); cpu->position++ ;} )
SET_CMD_( IN     , 27, { float a = 0; scanf ( "%f", &a ); CPU_push ( cpu, a); cpu->position++ ;} )

SET_CMD_( CALL   , 28, { CPU_push_ret ( cpu, cpu->position + 2 ); cpu->position = (int)cpu->code [ cpu->position + 1 ]; })
SET_CMD_( RET    , 29, { cpu->position = (int)CPU_pop_ret ( cpu ); })


















