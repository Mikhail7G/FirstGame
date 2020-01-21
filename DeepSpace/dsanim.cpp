#include "dsanim.h"


HANIM::HANIM(char *_name)
{
	loadmode=2;
	wight=0;
	height=0;
	numframes=0;
	name=_name;

	if ((f = fopen(name, "rb")) == NULL) {
		hge->System_Shutdown();
		exit(1);
	}
	else
	{


		int y = 0;
		fread(&numframes, sizeof(int), 1, f);//кадры
		fread(&wight, sizeof(int), 1, f);//ширина
		fread(&height, sizeof(int), 1, f);//высота

		/*for(int i=1;i<numframes;i++)
		{
		tex[i] = hge->Texture_Create(wight,height);
		};*/

		/*if(loadmode==1)
		{
		for(int fr=1;fr<numframes;fr++)
		{
		hgeU32 *pixels = hge->Texture_Lock(tex[fr], false);

		for(int i=0;i<(wight*height);i++)
		{
		fread( &tz, sizeof(int),1 , f );
		blue=tz;
		fread( &tz, sizeof(int),1 , f );
		green=tz;
		fread( &tz, sizeof(int),1 , f );
		red=tz;
		fread( &tz, sizeof(int),1 , f );
		a=tz;
		pixels[i]=ARGB(a,red,green,blue);

		};



		y=0;
		hge->Texture_Unlock(tex[fr]);
		};

		};*/


		if (loadmode == 2)//сжатые файлы
		{
			unsigned long ff;
			ff = 0;
			unsigned long d1;
			unsigned long d2;
			//fread( &d1, sizeof(int),1 , f );//несжат
			//fread( &d2, sizeof(int),1 , f );//сжат
			fread(&d1, sizeof(unsigned long), 1, f);//несжат
			fread(&d2, sizeof(unsigned long), 1, f);//сжат
			unsigned char *newmass = new  unsigned char[d2];
			unsigned char *newmassu = new  unsigned char[d1];


			for (unsigned int i = 0; i < d2; i++)
			{
				fread(&newmass[i], sizeof(unsigned char), 1, f);//высота
			};

			if (Z_OK == uncompress(newmassu, &d1, newmass, d2))
			{

				for (int fr = 0; fr < numframes; fr++)
				{
					tex.push_back(hge->Texture_Create(wight, height));

					hgeU32 *pixels = hge->Texture_Lock(tex.at(fr), false);
					for (int i = 0; i < (wight*height); i++)
					{
						pixels[i] = ARGB(newmassu[ff + 3], newmassu[ff + 2], newmassu[ff + 1], newmassu[ff]);
						ff = ff + 4;
					};
					hge->Texture_Unlock(tex.at(fr));

				};
			};
			newmass = 0;
			newmassu = 0;
			delete[] newmass;
			delete[] newmassu;
		};
		fclose(f);
	};





			
};
HANIM::~HANIM()
{
  
}