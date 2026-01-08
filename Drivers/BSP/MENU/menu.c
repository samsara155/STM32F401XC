#include "./BSP/MENU/menu.h"
#include "./BSP/GUI/gui.h"
#include "./BSP/LCD/lcd.h"
//#include "key.h"
//#include "IIC.h"

__weak void FUN1 (void)
{
	HAL_Delay(1000);
}
__weak void FUN2 (void)
{
	HAL_Delay(2000);
}
__weak void FUN3 (void)
{
	HAL_Delay(3000);
}
__weak void FUN4 (void)
{
	HAL_Delay(4000);
}
__weak void FUN5 (void)
{
	HAL_Delay(5000);
}

uint8_t params1_p=0,params2_p=0,params3_p=0,params4_p=0,params5_p=0;

Menu menu1_main[1];
Menu menu2_setting1[5];
Menu menu2_1_setting1[2];
Menu menu2_2_setting2[3];
Menu menu2_3_setting3[3];
Menu menu2_4_setting4[3];
Menu menu2_5_setting5[1];

Menu menu1_main[1]=
{
	{1,"Main","setting",TYPE_SUBMENU,NO_params,NULL,menu2_setting1,NULL}
};

Menu menu2_setting1[5]=
{
	{5,"setting"	 ,"setting1",TYPE_SUBMENU,NO_params,NULL,menu2_1_setting1,menu1_main},
	{5,		""		 ,"setting2",TYPE_SUBMENU,NO_params,NULL,menu2_2_setting2,menu1_main},
	{5,		""		 ,"setting3",TYPE_SUBMENU,NO_params,NULL,menu2_3_setting3,menu1_main},
	{5,		""		 ,"setting4",TYPE_SUBMENU,NO_params,NULL,menu2_4_setting4,menu1_main},
	{5,		""		 ,"setting5",TYPE_SUBMENU,NO_params,NULL,menu2_5_setting5,menu1_main}
};

Menu menu2_1_setting1[2]=
{
	{2,"setting1","params1",TYPE_PARAM,params1,NULL,NULL,menu2_setting1},
	{2,		""	 ,"params2",TYPE_PARAM,params2,NULL,NULL,menu2_setting1}
};

Menu menu2_2_setting2[3]=
{
	{3,"setting2","params3",TYPE_PARAM,params3,NULL,NULL,menu2_setting1},
	{3,		""	 ,"params4",TYPE_PARAM,params4,NULL,NULL,menu2_setting1},
	{3,		""	 ,"FUN1"   ,TYPE_FUN,NO_params,(*FUN1),NULL,menu2_setting1}
};

Menu menu2_3_setting3[3]=
{
	{3,"setting3","FUN2",TYPE_FUN,NO_params,(*FUN2),NULL,menu2_setting1},
	{3,		""		 		 ,"FUN3",TYPE_FUN,NO_params,(*FUN3),NULL,menu2_setting1},
	{3,		""		 		 ,"FUN4",TYPE_FUN,NO_params,(*FUN4),NULL,menu2_setting1}
};

Menu menu2_4_setting4[3]=
{
	{3,"setting4","params1",TYPE_PARAM,params1,NULL,NULL,menu2_setting1},
	{3,"",			"params2",TYPE_PARAM,params2,NULL,NULL,menu2_setting1},
	{3,"",			"params3",TYPE_PARAM,params3,NULL,NULL,menu2_setting1}
};

Menu menu2_5_setting5[1]=
{
	{1,"setting5","FUN5",TYPE_FUN,NO_params,(*FUN5),NULL,menu2_setting1},
};

//定义菜单操作需要的全局变量
Menu *cur_item = menu1_main;  //初始化当前菜单为第一级(main_menu)
Menu *prev_item = NULL;	    //初始化上一级菜单为空
uint8_t item_index = 0;//当前菜单项索引
void add_or_Reduce_param_Nowline(uint8_t choose)
{
	if(choose==0)
	{
		if(cur_item[item_index].type==TYPE_PARAM)
		{
				switch (cur_item[item_index].params)
				{
					case params1:
						params1_p++;
						break;
					case params2:
						params2_p++;
						break;
					case params3:
						params3_p++;
						break;
					case params4:
						params4_p++;
						break;
					case params5:
						params5_p++;
						break;
					default:
						break;
				}
		}
	}
	else
	{
		if(cur_item[item_index].type==TYPE_PARAM)
		{
				switch (cur_item[item_index].params)
				{
					case params1:
						params1_p--;
						break;
					case params2:
						params2_p--;
						break;
					case params3:
						params3_p--;
						break;
					case params4:
						params4_p--;
						break;
					case params5:
						params5_p--;
						break;
					default:
						break;
				}
		}
	}
}
void DispCrt_param_Nowline(uint8_t choose,uint8_t i,uint8_t Now_line)
{
	if(choose==0)
	{
		if(cur_item[Now_line].type==TYPE_PARAM)
		{
			switch (cur_item[Now_line].params)
			{
				case params1:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params1_p,3,BLUE,LGRAY,font_size);
					break;
				case params2:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params2_p,3,BLUE,LGRAY,font_size);
					break;
				case params3:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params3_p,3,BLUE,LGRAY,font_size);
					break;
				case params4:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params4_p,3,BLUE,LGRAY,font_size);
					break;
				case params5:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params5_p,3,BLUE,LGRAY,font_size);
					break;
				default:
					Show_Str(LCD_W/2,(LCD_H/8)*(i+1),BLUE,LGRAY,"error",font_size,0);
					break;
			}
		}
	}
	else
	{
		if(cur_item[Now_line].type==TYPE_PARAM)
		{
			switch (cur_item[Now_line].params)
			{
				case params1:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params1_p,3,WHITE,BLACK,font_size);
					break;
				case params2:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params2_p,3,WHITE,BLACK,font_size);
					break;
				case params3:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params3_p,3,WHITE,BLACK,font_size);
					break;
				case params4:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params4_p,3,WHITE,BLACK,font_size);
					break;
				case params5:
					LCD_ShowNum(LCD_W/2,(LCD_H/8)*(i+1),params5_p,3,WHITE,BLACK,font_size);
					break;
				default:
					Show_Str(LCD_W/2,(LCD_H/8)*(i+1),WHITE,BLACK,"error",font_size,0);
					break;
			}
		}
	}
}
void DispCrtMenu(void)//绘制当前菜单项
{
	LCD_Clear(BLACK);
	uint8_t menu_num = cur_item[0].num;//获取当前菜单的项目数量 
	uint8_t i;//绘制数量不能超过每一屏的最大绘制数量
	
	Show_Str(0,0,WHITE,BLACK,(uint8_t *)cur_item[0].title,16,0);
	for (i=0; i<menu_num; i++)//绘制某一级菜单下的功能键 
	{
		if(i==0)
		{
			Show_Str(0,(LCD_H/8)*(i+1),BLUE,LGRAY,(uint8_t *)cur_item[i].label,font_size,0);
		}
		else
		{
			Show_Str(0,(LCD_H/8)*(i+1),WHITE,BLACK,(uint8_t *)cur_item[i].label,font_size,0);
		}
		DispCrt_param_Nowline(i,i,i);
	}
}

/**
 * @brief   处理按键输入
 * @param   key_value: 按键值指针 (1-确认, 2-返回, 3-下, 4-上, 5-增加, 6-减少)
 * @retval  无
 */
void Display(uint8_t *key_value)
{
    if(key_value == NULL)  // 安全检查
		return;
	switch(*key_value)
	{
		case 1:

			switch(cur_item[item_index].type)//检测功能项的类型，进入相应动作
			{
				case TYPE_SUBMENU: //具有子菜单的菜单项
					if(cur_item[item_index].next1 != NULL)
					{ 
						prev_item = cur_item;//此级菜单变成了上一级菜单 
						cur_item = cur_item[item_index].next1;//将指向的下一级菜单设置为当前菜单 
						item_index = 0;//重置子菜单项索引 
						DispCrtMenu();
					}
					else
					{
					}
					break; 
				case TYPE_PARAM:  //具有参数设置的菜单项
					break; 
				case TYPE_FUN:  
					cur_item[item_index].Function();
					break; 
				default: 
					break;
			}
			*key_value=0;
			break;
			
		case 2:
			
			if (prev_item != NULL)//返回上一级菜单的操作 
			{
				cur_item = prev_item;  //设置上一级菜单为当前菜单 
				prev_item = cur_item[0].prev;  //设置当前菜单的上一级菜单 
				item_index = 0;  //重置子菜单项索引
//				if(prev_item != NULL)
//				{
//					DispCrtMenu();
//				}
//				else
//				{
//					home();
//				}
				DispCrtMenu();
			} 
			else
			{
			}
			*key_value=0;
			break;
		case 3:
			if(item_index==(cur_item[0].num-1))
			{
				Show_Str(0,(LCD_H/8)*(item_index+1),WHITE,BLACK,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(1,item_index,item_index);
				item_index=0;
				Show_Str(0,(LCD_H/8)*(item_index+1),BLUE,LGRAY,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(0,item_index,item_index);
			}
			else
			{
				Show_Str(0,(LCD_H/8)*(item_index+1),WHITE,BLACK,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(1,item_index,item_index);
				item_index++;
				Show_Str(0,(LCD_H/8)*(item_index+1),BLUE,LGRAY,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(0,item_index,item_index);

			}
			*key_value=0;
			break;
		case 4:
			if(item_index==0)
			{
				Show_Str(0,(LCD_H/8)*(item_index+1),WHITE,BLACK,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(1,item_index,item_index);
				item_index=(cur_item[0].num-1);
				Show_Str(0,(LCD_H/8)*(item_index+1),BLUE,LGRAY,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(0,item_index,item_index);
			}
			else
			{
				Show_Str(0,(LCD_H/8)*(item_index+1),WHITE,BLACK,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(1,item_index,item_index);
				item_index--;
				Show_Str(0,(LCD_H/8)*(item_index+1),BLUE,LGRAY,(uint8_t *)cur_item[item_index].label,font_size,0);
				DispCrt_param_Nowline(0,item_index,item_index);
			}
			*key_value=0;
			break;
		case 5:
			add_or_Reduce_param_Nowline(0);
			DispCrt_param_Nowline(0,item_index,item_index);
			*key_value = 0;
			break;
		case 6:
			add_or_Reduce_param_Nowline(1);
			DispCrt_param_Nowline(0,item_index,item_index);
			*key_value = 0;
			break;
		default:
			break;
	}

}



