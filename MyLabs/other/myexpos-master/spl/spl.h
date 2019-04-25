#include<string.h>
#include "data.h"
#include "node.h"
#define LEGAL 0

#define PAGE_PER_INTERRUPT      2
#define PAGE_SIZE               512

#define CONSTANT_NAME_MAX_LEN    30

extern int linecount;
extern unsigned long temp_pos; //temporary lseek
extern int out_linecount; //no of lines of code generated
extern int flag_break;
extern int regcount;


extern FILE *fp;
                        ///start constants and aliasing
struct define
{
    char name[CONSTANT_NAME_MAX_LEN];
    int value;
    struct define *next;
};

extern struct define *root_define;
struct define* lookup_constant(char *name);
extern int depth;

struct alias
{
    char name[CONSTANT_NAME_MAX_LEN];
    int reg, depth;
    struct alias *next;
};
extern struct alias *root_alias;

struct alias * lookup_alias(char *name);
struct alias * lookup_alias_reg(int no);
void push_alias(char *name, int no);
void pop_alias();
void insert_constant(char *name, int value);
void add_predefined_constants();

node * substitute_id(node *id);
                            ///end of constants and alias
                            ///end tree create fns
void getreg(node *root, char reg[]);

void codegen(node * root);

void expandpath(char *path); // To expand environment variables in path

void remfilename(char *pathname);
