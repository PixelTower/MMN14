#ifndef DATA_STRCT_H
#define DATA_STRCT_H

/*  AST Node structure  */
typedef struct ASTNode
{
    char *opcode;
    struct ASTNode *next;
} ASTNode;

/*  Macro Node structure  */
typedef struct node
{
    char *name;
    char *content;
    struct node *next;
} node;

/*  Label structure for symbol table  */
<<<<<<< HEAD
typedef struct label_struct
{
    char name[32]; /* Label name */
    int address;   /* Address of the label */
    int type;      /* 0 = code, 1 = data, 2 = external, etc. */
=======
typedef struct label_struct {
    char name[32];  
    int address;    
    int type;       
>>>>>>> 99d8934 (21:03)
} label_struct;

#endif
