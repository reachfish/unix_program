
#define PATH_MAX  30

char *px_ipc_name(const char* name){
	char *dir, *dst, *slash;
	if((dst=malloc(PATH_MAX))==nullptr){
		return nullptr;
	}

#ifdef POSIX_IPC_PREFIX
	dir = POSIX_IPC_PREFIX
#else
	dir = "/tmp"
#endif

	slash = dir[strlen(dir)-1] == '/' ? "" : "/";
	snprintf(dst, PATH_MAX, "%s%s%s", dir, slash, name);

	return dst;
}
