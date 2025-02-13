#define ln ;printf("\n");


char *fgetsclose(char *s, int n, FILE *f)
{
	char *result = s;
	while ((n > 0) && fgets(s, n, f))
	{
		n-= strlen(s);
		s+= strlen(s);
	}
	fclose(f);
	return result;
}

#define LOADBUFN 2048
char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}
