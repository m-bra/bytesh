
#define scanfsh edit, ROOTC("run/scanfs.h"), endsh

// BEGIN

inline
void    scanfs()
#define scanfs   scanfs()
{
	int nchars = 26 + 26 + 10 + 1;
	char chars[nchars];\
	int i = 0;\
	for (char a = 'a'; a <= 'z'; ++a)\
	   chars[i++] = a;\
	for (char a = 'A'; a <= 'Z'; ++a)\
	   chars[i++] = a;\
	for (char a = '0'; a <= '9'; ++a)\
	   chars[i++] = a;\
	chars[i++] = '\0';

	for (int i = 0; i < nchars; ++i)
	stm ; // printf("%c.", chars[i]);
	ln;

	int nindices = 5;
	int indices[nindices];
	for (int i = 0; i < nindices; ++i)
	stm indices[i] = 0;

	rep {
		stm indices[nindices - 1]++;
		for (int i = nindices - 1; i >= 0; --i)
		iff indices[i] >= nchars
		thn { 
		    stm indices[i] = 0;  
		    iff i > 0
		    thn {
		        stm indices[i - 1]++; 
		        iff i < 3 
		        thn {
		            for (int i = 1; i < 3; ++i)
		            stm printf("%c", chars[indices[i]]);
		            ln;
		            } 
		        }
		    els return;
		    }

		iff chars[indices[0]] == '\0'
		thn continue;

		stm char filename[1 + nindices + 1];
		stm filename[1 + nindices] = 0;
		stm filename[0] = '/';
		for (int i = 0; i < nindices; ++i)
		stm filename[1 + i] = chars[indices[i]];

		stm // printf("%s\n", filename);

		iff access(filename, F_OK) == 0
		thn printf("\"%s\" exists\n", filename); 
	}
}
