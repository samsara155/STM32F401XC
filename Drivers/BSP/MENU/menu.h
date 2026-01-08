#ifndef __MENU_H__
#define __MENU_H__
#include "./SYSTEM/sys/sys.h"

///////////////////////menu///////////////////////
#define TYPE_SUBMENU 101   //子菜单定义
#define TYPE_PARAM   102   //参数定义
#define TYPE_FUN     103   //功能定义

#define font_size    12

enum params {
	NO_params,
	params1,
	params2,
	params3,
	params4,
	params5
};




typedef void (*MENU_FUN)(void);

typedef struct menu
{
	uint8_t num;
	char * title;
	char * label;
	uint8_t type;
	uint8_t params;
	MENU_FUN Function;
	
	struct menu* next1;
	struct menu* prev;
}Menu;





void Display(uint8_t *key_value);
void DispCrtMenu(void);


#endif
