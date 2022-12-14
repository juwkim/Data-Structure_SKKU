#ifndef __MEMBER_H__
#define __MEMBER_H__

#define WIDTH "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n"


void alignCenter(char txt[]);
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName);
void textColor(char txt[], int color);
void printBox(char txt[]);

void menu1_member_view(Tree *tree);
void menu2_member_add(Tree *tree, Tree *treeForName);
void menu3_member_modify(Tree *tree, Tree *treeForName);
void menu4_member_delete(Tree *tree, Tree *treeForName);
void menu5_member_search(Tree *tree, Tree *treeForName);
void menu6_data_save(Tree *tree);
void menu0_close();

int isValidName(char txt[]);
int isValidAddr(char txt[]);
int isValidPhone(char txt[]);

#endif