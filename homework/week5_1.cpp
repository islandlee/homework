/*
2013011302 李奕昕
2013011356 董豪宇
用户输入的内容有：
访问时间限制（total_time）、总页面数（members_num）、
页面初始状态（初始时间，初始时是否在工作集中）
接下来是访问过程，每次输入想访问的页编号，输出是当前工作集
输入-1时表示访问结束
*/

#include <iostream>
#include <cstring>
#define NUMBERS 100

struct member
{
	int own_time;
	bool if_in_table;
	/* data */
} members[NUMBERS];

int main()
{
	memset(members,0,sizeof(members));
	//初始化过程
	int current_time = 0;
	int total_time;
	printf("Please input total_time:\n");
	scanf("%d",&total_time);
	//输入限制时间，超时淘汰
	int members_num;
	printf("Please input the amount of your members:\n");
	scanf("%d",&members_num);
	//输入有几个页面，不超过100个
	printf("Please init your members' own_time and if they exist in work table :\n");
	for (int i = 0; i < members_num; i++)
	{
		scanf("%d", &members[i].own_time);
		scanf("%d", &members[i].if_in_table);
	}
	//依次输入每个页面的初始状态
	//初始化结束，所有页的初始时间、初始是否在工作表中都已经标明

	int visit_num;
	while (1)
	{
		printf("Please input which page you want to visit:\n");
		scanf("%d",&visit_num);
		if (visit_num == -1)
			break;
		//退出访问
		current_time++;
		members[visit_num].own_time = current_time;
		members[visit_num].if_in_table = 1;
		for (int i = 0; i < members_num; i++)
		{
			if (current_time - members[i].own_time >= total_time)
			{
				members[i].if_in_table = 0;//把超时的页淘汰出去
			}
			if (members[i].if_in_table == 1)
			{
				printf("page %d\n", i);
			}
		}
	}

	return 0;
}