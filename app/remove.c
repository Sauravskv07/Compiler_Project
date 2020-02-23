#include <stdio.h>

void removeComments() 
{
    FILE *sc = fopen("src.c", "r");//char *src,char *dst
    FILE *cc = fopen("dst.c", "w");
    char c,c2;
    int flag=0;
	while (!feof(sc)&&(c= fgetc(sc))){
		if(c == EOF)
		{break;}
		if (c =='*') {
			if(feof(sc)){break;}
			c2= fgetc(sc);
			if (c2 =='*')//a comment starts
				flag=1;
			else
				{fputc(c,cc);fputc(c2,cc);}

			 while (flag==1)
				{ if(feof(sc)){break;}
					c= fgetc(sc);
					if(c =='\n')
					{fputc(c,cc);}
					else if (c =='*')
						{if(feof(sc)){break;}c= fgetc(sc);
						if (c =='*')//a comment starts
							break;
						}
					else{}
				}
				
		}
		else
		fputc(c,cc);
	}
  fclose(sc);
  fclose(cc);
}
