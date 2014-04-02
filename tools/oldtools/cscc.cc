// By Zhao Yanbai
// 2008.12.10
// Version 1.0
#include<cstdio>
#include<ctime>
#include<cstring>
#include<iostream>
#include<string>
using namespace std;
void usage()
{
	printf("usage...\n");
}

int main(int argc, char *argv[])
{
	FILE *fp;
	time_t now = time(NULL);
	int len = strlen(argv[1]);
	string project;
	string hstr;

	if(argc != 2)
	{
		usage();
		return 1;
	}

	if((fp = fopen(argv[1],"w+")) == NULL)
	{
		printf("cannot create file\n");
		return 1;
	}
	fprintf(fp,"/*\n");
	fprintf(fp," *--------------------------------------------------------------------------\n");
	fprintf(fp," *   File Name:\t%s\n",argv[1]);
	fprintf(fp," * \n");
	fprintf(fp," * Create Date: %s",ctime(&now));
	fprintf(fp," * \n");
	fprintf(fp," *      Author:\tZhao Yanbai [zhaoyanbai@126.com]\n");
	fprintf(fp," * \t\tInformation Security Research Center Of\n");
	fprintf(fp," * \t\tHarbin Engineering University\n");
	fprintf(fp," * \n");
	fprintf(fp," * Description:\tnone\n");
	fprintf(fp," * \n");
	fprintf(fp," *--------------------------------------------------------------------------\n");
	fprintf(fp," */\n\n");

	if(argv[1][len-1] == 'h' && argv[1][len-2] == '.')
	{

		cout<<"Project Name:";
		cin>>project;

		hstr += project;
		hstr += "_";
		hstr += argv[1];

		for(int i=0; i<hstr.length(); i++)
		{
			if(hstr[i] == '.')
				hstr[i] = '_';
			else
				hstr[i] = toupper(hstr[i]);
		}
		hstr += "_";

		fprintf(fp,"#ifndef\t%s\n",hstr.c_str());
		fprintf(fp,"#define\t%s\n\n\n\n",hstr.c_str());
		fprintf(fp,"#endif //%s",hstr.c_str());
	}

	fclose(fp);
	return 0;
}
