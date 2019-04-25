#include "lex.yy.c"

/*
extern struct {char data[BUFF];int flag;}yylval;
extern struct {char label[BUFF];int position;int lineno;}entry;
extern struct {struct entry entry[TABSIZE];int label_count}symtab;
extern int pass,started,error;
*/

void Initialize (void);
void Executeoneinstr (int);
int Find(char*);
void Operanderror(char*,int);

main(int argc,char **argv)
{
	int instr;
	Initialize();
	if(argc < 2)
	{
		printf("<ERROR> Format is sim [filename]\n");
		exit(0);
	}
	yyin = fopen(argv[1],"r");
	if(yyin == NULL)
	{
		printf("File %s doesn't exist\n",argv[1]);
		exit(0);
	}
	pass = 1;
	yylex();
	if(started == -1)
	{
		printf("<ERROR> start missing\n");
		exit(0);
	}
	if(error == 1)
	{
		printf("\nAborting pass 2");
		exit(0);
	}
	pass = 2;
	line_count = started;
	fseek(yyin,start_offset,0);
	YY_FLUSH_BUFFER;
	while(1)
	{
		instr = yylex();
		Executeoneinstr(instr);
//		printf("%d %d\n",line_count,ftell(yyin));
//		fflush(stdout);
	}

}

void Initialize()
{
	started = -1;
	error = 0;
	line_count = 1;
	symtab.label_count = 0;
	top = 0;
}

void Executeoneinstr(int instr)
{
	int opnd1,opnd2,flag1,flag2,oper,result;
	char label[BUFF];
	switch(instr)
	{
		case MOV:opnd1 = yylex();
			 flag1 = yylval.flag;
			 opnd2 = yylex();
			 flag2 = yylval.flag;
			 switch(flag2)
			 {
				 case REG:result = reg[opnd2];
					  break;
				 case SP: result = sp;
					  break;
				 case BP: result = bp;
					  break;
				 case IP: result = ip;
					  break;
				 case NUM:result = opnd2;
					  break;
				 case MEM_REG:result = mem[reg[opnd2]];
					      break;
				 case MEM_SP:result = mem[sp];
					     break;
				 case MEM_BP:result = mem[bp];
					     break;
				 case MEM_IP:result = mem[ip];
					     break;
				 case MEM_DIR:if(flag2!=REG)
						result = mem[opnd2];
					      else
					      {
						printf("<ERROR:%d:>Invalid instruction format\n",line_count);
						exit(1);
					      }
					      break;
				 default:Operanderror("MOV",2);
					 break;
			}
			switch(flag1)
			{
				case REG:reg[opnd1] = result;
					 break;
				case SP: sp = result;
					 break;
				case BP: bp = result;
					 break;
				case IP: ip = result;
					 break;
				case MEM_REG:mem[reg[opnd1]] = result;
					     break;
				case MEM_SP:mem[sp] = result;
					    break;
				case MEM_BP:mem[bp] = result;
					    break;
			 	case MEM_IP:mem[ip] = result;
					    break;
				case MEM_DIR:if(flag1!=REG)
					   	mem[opnd1] = result;
					      else
					      {
						printf("<ERROR:%d:>Invalid instruction format\n",line_count);
						exit(1);
					      }
					      break;
				default:Operanderror("MOV",1);
					break;
			}
			break;
		case ARITH:
			oper = yylval.flag;
			opnd1 = yylex();
			if(yylval.flag != REG)
				Operanderror("ARITH",1);
			if(oper!= INR && oper!=DCR)
			{
				opnd2 = yylex();
				if(yylval.flag != REG)
					Operanderror("ARITH",2);
			}
			switch(oper)
			{
				case ADD:reg[opnd1]=reg[opnd1]+reg[opnd2];
					 break;			
				case SUB:reg[opnd1]=reg[opnd1]-reg[opnd2];
					 break;
				case MUL:reg[opnd1]=reg[opnd1]*reg[opnd2];
					 break;
				case DIV:reg[opnd1]=reg[opnd1]/reg[opnd2];
					 break;
				case MOD:reg[opnd1]=reg[opnd1]%reg[opnd2];
					 break;
				case INR:reg[opnd1]++;
					 break;
				case DCR:reg[opnd1]--;
					 break;
				default:printf("<ERROR> Illegal ARITH\n");
					break;
			}
			break;
		case LOGIC:
			oper = yylval.flag;
			opnd1 = yylex();
			if(yylval.flag != REG)
				Operanderror("LOGIC",1);
			opnd2 = yylex();
			if(yylval.flag != REG)
				Operanderror("LOGIC",2);
			switch(oper)
			{
			       case LT:reg[opnd1]=(reg[opnd1]<reg[opnd2])?1:0;
					break;
			       case GT:reg[opnd1]=(reg[opnd1]>reg[opnd2])?1:0;
					break;	
			       case EQ:reg[opnd1]=(reg[opnd1]==reg[opnd2])?1:0;
					break;
			       case NE:reg[opnd1]=(reg[opnd1]!=reg[opnd2])?1:0;
					break;	
			       case LE:reg[opnd1]=(reg[opnd1]<=reg[opnd2])?1:0;
					break;
			       case GE:reg[opnd1]=(reg[opnd1]>=reg[opnd2])?1:0;
					break;	
			       default:printf("<ERROR> Illegal LOGIC\n");
				       break;
			}
			break;
		case BRANCH:
			oper = yylval.flag;
			switch(oper)
			{
				case JZ:opnd1 = yylex();
					if(yylval.flag != REG)
						Operanderror("JZ",1);
					opnd2 = yylex();
					if(opnd2 != LABEL)
						Operanderror("JZ",2);
					if((result = Find(yylval.data))<0)
					{
						printf("<ERROR:%d:> Label not found",line_count);
						exit(0);
					}
					if(reg[opnd1] == 0)
					{
						fseek(yyin,result,0);
						YY_FLUSH_BUFFER;
					}
					break;
				case JNZ:opnd1 = yylex();
					if(yylval.flag != REG)
						Operanderror("JNZ",1);
					opnd2 = yylex();
					if(opnd2 != LABEL)
						Operanderror("JNZ",2);
					if((result = Find(yylval.data))<0)
					{
						printf("<ERROR:%d:> Label not found",line_count);
						exit(0);
					}
					if(reg[opnd1] != 0)
					{
						fseek(yyin,result,0);
						YY_FLUSH_BUFFER;
					}
					break;
				case JMP:opnd1 = yylex();
					 if(opnd1 != LABEL)
						 Operanderror("JMP",1);
					 if((result = Find(yylval.data))<0)
					 {
						 printf("<ERROR:%d:> Label not found",line_count);
						 exit(0);
					}
					fseek(yyin,result,0);
					YY_FLUSH_BUFFER;
					break;
				default:printf("<ERROR> Illegal BRANCH");
					break;
			}
			break;

		case PUSH:opnd1 = yylex();
			  switch(yylval.flag)
			  {
				  case REG:mem[++sp]=reg[opnd1];
					   break;
				  case SP:mem[++sp]=sp;
					  break;
				  case BP:mem[++sp]=bp;
					  break;
				  case IP:mem[++sp]=ip;
					  break;
				  default:Operanderror("PUSH",1);
					  break;
			  }
			  break;
		case POP:opnd1 = yylex();
			 switch(yylval.flag)
			 {
				  case REG:reg[opnd1]=mem[sp--];
					   break;
				  case SP:sp=mem[sp--];
					  break;
				  case BP:bp=mem[sp--];
					  break;
				  case IP:ip=mem[sp--];
					  break;
				  default:Operanderror("POP",1);
					  break;
			 }
			 break;
		case CALL:opnd1 = yylex();
			  if(opnd1 != LABEL)
				  Operanderror("CALL",1);
			  mem[++sp] = ftell(yyin)-1;
			  stack[++top] = line_count;
			  if((result = Find(yylval.data))<0)
			  {
				printf("<ERROR:%d:Label not found");
			  	exit(0);
			  }
			  fseek(yyin,result,0);
			  YY_FLUSH_BUFFER;
			  break;
		case RET:
			 if(top==0)
			 { 
				printf("<ERROR:%d:>Stack Underflow\n",line_count);
				exit(0);
			 }
			 else
			 {
				fseek(yyin,mem[sp--],0);
				 YY_FLUSH_BUFFER;
				 line_count = stack[top--];
			 }
			 break;
		case IN:opnd1 = yylex();
			if(yylval.flag != REG)
				Operanderror("IN",1);
			scanf("%d",&reg[opnd1]);
			break;
		case OUT:opnd1 = yylex();
			 if(yylval.flag != REG)
				 Operanderror("OUT",1);
			 printf("%d\n",reg[opnd1]);
			 break;
		case HALT:printf("\nHALTING MACHINE\n");
			  exit(0);
		default:printf("<ERROR:%d:>Illegal instruction\n");
			exit(0);
	}
}

int Find(char str[BUFF])
{
	int i;
	for(i=0; i<=symtab.label_count; i++)
	{
		if(strcmp(symtab.entry[i].label,str) == 0)
		{
			line_count = symtab.entry[i].lineno;
			return symtab.entry[i].position;
		}
	}
	return -1;
}

void Operanderror(char str[BUFF],int no)
{	
	printf("<ERROR:%d:> Unexpected operand %d for %s instruction\n",line_count,no,str);
	exit(0);
}
