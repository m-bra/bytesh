#include "main.h"

#ifndef HTMLUTILH 
#define HTMLUTILH

#define REJECTTAGS "Local Job", "Photography", "Sewing", "House Cleaning", "Housework", "Handyman", "Painting", "CAD/CAM", "Videography", "Removal Services", "Plumbing", "Interior Design", "Electric Repair", "Baking", "Trucking"
#define CURRENTPAGE 12

#define scanhtmlh printf("Found in : $ htmlutilh%c", *NLS);
int scanhtml(char *filename)
{
iff errno
thn { perror(mf("%s:%d", __FILE__, __LINE__)); return 0; }    
	
    char *filenameaccept = mf("%s%s", filename, ".accept.txt");
	char *filenamereject = mf("%s%s", filename, ".reject.txt");
	char *filenames[3] = {filenameaccept, filenamereject, 0};
for (char **f = filenames; *f; ++f)
iff access(*f, F_OK) == 0
thn { printf("%s %s \n", *f, "already exists."); return 0;}

	errno = 0;

	FILE *f = fopen(filename, "r");
cen FILE *outreject = fopen(mf("%s%s", filename, ".reject.txt"), "w");
cen FILE *outaccept = fopen(mf("%s%s", filename, ".accept.txt"), "w");
cen	
    char *entrydbuf = mallocaddpagebuf; //[pagebuf_tn];
    char *entrybuf = mallocaddpagebuf;//[pagebuf_tn];
	entrybuf[0] = 0;
	entrydbuf[0] = 0;



	struct entryctxt {
		int reject;
		int buildingentry;
	} entryctxt;

	entryctxt.buildingentry = 0;

	char pageline[linebuf_tn];

	char line[linebuf_tn];
	while (fgets(line, linebuf_tn, f))
	{
		int wasbuildingentry = entryctxt.buildingentry;

		if (strstr(line, "# # PAGE"))
		{
			strcpy(pageline, line);
		}

		if (strstr(line, "href=\"/project"))
		{
			snprintf(asstr entrybuf, pagebuf_tn, "%s%c%s", entrydbuf, *NLS, line + strspn(line, " "));
			strcpy(entrydbuf, entrybuf);
		}

		if (strstr(line, "bids"))
		{
			snprintf(asstr entrybuf, pagebuf_tn, "%s%s", entrydbuf, line + strspn(line, " "));
			strcpy(entrydbuf, entrybuf);
		}
		
		if (strstr(line, "class=\"Title\""))
		{
		    entryctxt.buildingentry = 1;
			
			char title[linebuf_tn * 20];
			for (int i = 0; i < 17; ++i)
			fgets(title, linebuf_tn * 20, f);

            snprintf(asstr entrybuf, pagebuf_tn, "%s----", entrydbuf);
            strcpy(entrydbuf, entrybuf);
				
		    rep {
		    	fgets(title, linebuf_tn * 20, f);
		    iff strstr(title, "<!--")
		    thn break;
				strrpl(title, ' ', *NLS);
				snprintf(asstr entrybuf, pagebuf_tn, "%s%s", entrydbuf, title + strspn(title, " "));
				strcpy(entrydbuf, entrybuf);
		    }
		    snprintf(asstr entrybuf, pagebuf_tn, "%s%c", entrydbuf, *NLS);
		    strcpy(entrydbuf, entrybuf);
	    }


	    if (strstr(line, "max-height: 80.08px;"))
	    {
	    	entryctxt.buildingentry = 1;

	    	char desc[linebuf_tn * 4];
	    	for (int i = 0; i < 15; ++i)
	    	fgets(desc, linebuf_tn * 4, f);

			snprintf(asstr entrybuf, pagebuf_tn, "%s****%c", entrydbuf, *NLS);
			strcpy(entrydbuf, entrybuf);

	    	rep {
	    		fgets(desc, linebuf_tn * 4, f);	
	    	iff strstr(desc, "<!--")
	    	thn break;
				strrpl(desc, ' ', *NLS);
	    		snprintf(asstr entrybuf, pagebuf_tn, "%s%s", entrydbuf, desc + strspn(desc, " "));
	    		strcpy(entrydbuf, entrybuf);
	    	}
	        snprintf(asstr entrybuf, pagebuf_tn, "%s%c****%c", entrydbuf, *NLS, *NLS);
	        strcpy(entrydbuf, entrybuf);
	    }

	    iff !wasbuildingentry && entryctxt.buildingentry
	    thn entryctxt.reject = 0;
	
	    if (strstr(line, "data-max-lines=\"1\""))
	    {
		     int ngstarinserted = 0;

			 rep {
			     char innerline [linebuf_tn];
		     ifn fgets(innerline, linebuf_tn, f)
		     thn break;
		     
		     iff strstr(innerline, "ng-star-inserted")
		     thn ++ngstarinserted;

		     iff ngstarinserted < 2
		     thn continue;
		       
	             char buf[linebuf_tn * 10];                                                                                  fgets(buf, linebuf_tn * 10, f);
	 		     fgets(buf, linebuf_tn * 10, f);
	 		     //es(buf);

			     int j = strspn(buf, " ");

			     char *rejecttags[] = {REJECTTAGS};
                 int nrejecttags = sizeof(rejecttags) / sizeof(char *);
				 for (int i = 0; i < nrejecttags; ++i)
			 	 iff strstr(buf, rejecttags[i])
			 	 thn entryctxt.reject = 1;

			 	 //es(buf);
			 	 //ed(entryctxt.reject);

	             snprintf(asstr entrybuf, pagebuf_tn, "%s%s", entrydbuf, buf + j);
	             strcpy(entrydbuf, entrybuf);

	             for (int i = 0; i < 13; ++i)
		         fgets(buf, linebuf_tn, f);
	         
			     if (strstr(buf, "Footer")) 
			     {
			         FILE *out = entryctxt.reject ? outreject : outaccept;
			         fprintf(out, "%s\n%s%c", pageline, entrybuf, *NLS);
			         entrybuf[0] = 0;
			         entryctxt.buildingentry = 0;	
			     }
		     	 //ed(entryctxt.reject);
		     	 //ed(entryctxt.buildingentry);
		         strcpy(entrydbuf, entrybuf);
		         break;
			 }

	   }
	
 }	
 
  return 1;

err:
  perror(mf("%s:%d", __FILE__, __LINE__));
  return 0;
}
#define prettierah printf("%s", "Found in: $ htmlutilh\n")
#define prettiera prettier, "*.html", endsh

#define htmlutilh edit, ROOTC("/run/htmlutil.h"), endsh
#define htmlutilhadd hadd("htmlutil")
#define htmlutilhaddfn(ident) haddfn("htmlutil", ident)
#define htmlutilhadddef(ident) hadditem("htmlutil", ident, 1)

#endif
