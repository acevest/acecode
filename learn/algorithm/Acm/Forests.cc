/*
 *--------------------------------------------------------------------------
 *   File Name:	Forests.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Jun 17 16:53:21 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
/*
 * 			Forests
 * Description
 *
 * If a tree falls in the forest, and there's nobody there to hear, does it make a sound? This classic conundrum was coined by George Berkeley (1685-1753), the Bishop and influential Irish philosopher whose primary philosophical achievement is the advancement of what has come to be called subjective idealism. He wrote a number of works, of which the most widely-read are Treatise Concerning the Principles of Human Knowledge (1710) and Three Dialogues between Hylas and Philonous (1713) (Philonous, the "lover of the mind," representing Berkeley himself).
 *
 * Input
 *
 * A forest contains T trees numbered from 1 to T and P people numbered from 1 to P. Standard input consists of a line containing P and T followed by several lines, containing a pair of integers i and j, indicating that person i has heard tree j fall. People may have different opinions as to which trees, according to Berkeley, have made a sound.
 *
 * Input contains multiple test cases. Subsequent test cases are separated with a single blank line.
 *
 * Output
 *
 * How many different opinions are represented in the input? Two people hold the same opinion only if they hear exactly the same set of trees. You may assume that P < 100 and T < 100.
 *
 * Sample Input
 *
 * 3 4
 * 1 2
 * 3 3
 * 1 3
 * 2 2
 * 3 2
 * 2 4
 *
 * Sample Output
 *
 * 2
 */

#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int main()
{
	unsigned int	P, T;
	bool		flag[100];
	unsigned char	map[100][100];
	char		buf[256];
	int		i, j, k;


	while(true)
	{
		memset(map, 0, 100*100*sizeof(unsigned char));
		for(i=0; i<100; i++)
			flag[i] = false;

		if(gets(buf) == NULL)
			break;

		sscanf(buf, "%d%d", &P, &T);

		while(true)
		{
			if(gets(buf) == NULL)
				break;

			if(buf[0] == 0)
				break;

			sscanf(buf, "%d%d", &i, &j);


			map[i-1][j-1] = 1;
		}

		i=0;
		int count = 0;
		while(true)
		{

			flag[i] = true;

			for(j=0; j<P; j++)
			{
				if(flag[j] == true)
					continue;


				for(k=0; k<T; k++)
					if(map[i][k] != map[j][k])
						break;
	

				if(k == T)
				{
					flag[j] = true;
				}
			}


			count++;

			for(k=1; i<P; k++)
				if(flag[k] != true)
					break;


			if(k == P)
				break;


			i = k;
		}
	


		cout<<count<<endl;
	}


	return 0;
}
