# define TRUE 1
# define FALSE 0

typedef struct {
	int (*canHandle) (char *);
	int (*drawImage)(char *);
	int (*savefile)(char *);
}imageHandler;

extern imageHandler *imagehandlers[];
//extern imageHandler tifhandler; // not required
//extern imageHandler gifhandler; // not required
