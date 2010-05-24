#ifndef F1WAE_H
#define F1WAE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define F1WAENUM(x)  ((F1WAENum *) (x))
#define F1WAEID(x)   ((F1WAEId *) (x))
#define F1WAEADD(x)  ((F1WAEAdd *) (x))
#define F1WAEWITH(x) ((F1WAEWith *) (x))
#define F1WAEAPP(x)  ((F1WAEApp *) (x))
#define F1WAEFUN(x)  ((F1WAEFun *) (x))

typedef unsigned long Expr;
typedef struct FunList FunList;

// node types
typedef enum {
  F1WAE_NUM,
  F1WAE_ADD,
  F1WAE_ID,
  F1WAE_WITH,
  F1WAE_APP,
  F1WAE_FUN
} F1WAEType;

// base node
typedef struct {
  F1WAEType type;
} F1WAE;

// number
typedef struct {
  F1WAEType type;
  int       val;
} F1WAENum;

// + operation
typedef struct {
  F1WAEType type;
  F1WAE     *lhs;
  F1WAE     *rhs;
} F1WAEAdd;

// id
typedef struct {
  F1WAEType type;
  char      *name;
} F1WAEId;

// with operation
typedef struct {
  F1WAEType type;
  F1WAEId   *id;
  F1WAE     *expr;
  F1WAE     *body;
} F1WAEWith;

// application
typedef struct {
  F1WAEType type;
  F1WAEId   *id;
  F1WAE     *expr;
} F1WAEApp;

// function
typedef struct {
  F1WAEType type;
  char      *name;
  char      *arg;
  F1WAE     *body;
} F1WAEFun;

inline F1WAENum  *F1WAENum_new(int);
inline F1WAEAdd  *F1WAEAdd_new(F1WAE*, F1WAE*);
inline F1WAEId   *F1WAEId_new(char*);
inline F1WAEWith *F1WAEWith_new(F1WAEId*, F1WAE*, F1WAE*);
inline F1WAEApp  *F1WAEApp_new(F1WAEId*, F1WAE*);
inline F1WAEFun  *F1WAEFun_new(char*, char*, F1WAE*);

F1WAE *F1WAE_clone(F1WAE*);

F1WAE   *F1WAE_parse(char*);
F1WAE   *F1WAE_subst(F1WAE*, char*, F1WAENum*);
int     F1WAE_interp(F1WAE*, FunList*);
char    *F1WAE_print(F1WAE*);
void    F1WAE_free(F1WAE*);


// function definitions linked list
struct FunList {
  F1WAEFun       *fun;
  struct FunList *next;
};

FunList  *FunList_new();
FunList  *FunList_addFun(FunList*, F1WAEFun*);
F1WAEFun *FunList_lookup(FunList*, char*);
void      FunList_free(FunList*);

#endif
