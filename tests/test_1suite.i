#line 1 "test_1suite.c"















#line 1 "..\\include\\nut.h"

















#line 19 "..\\include\\nut.h"

#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"















#pragma once
#line 18 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"






#line 25 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"















#line 41 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
#line 42 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"





#line 48 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"








#line 57 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
#line 58 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"



typedef unsigned int size_t;

#line 64 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"




typedef unsigned short wchar_t;

#line 71 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
#line 72 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"




#line 77 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"








#line 86 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
#line 87 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"














        void *  __cdecl memcpy(void *, const void *, size_t);
        int     __cdecl memcmp(const void *, const void *, size_t);
        void *  __cdecl memset(void *, int, size_t);
        char *  __cdecl _strset(char *, int);
        char *  __cdecl strcpy(char *, const char *);
        char *  __cdecl strcat(char *, const char *);
        int     __cdecl strcmp(const char *, const char *);
        size_t  __cdecl strlen(const char *);
#line 110 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
 void *  __cdecl _memccpy(void *, const void *, int, unsigned int);
 void *  __cdecl memchr(const void *, int, size_t);
 int     __cdecl _memicmp(const void *, const void *, unsigned int);





 void *  __cdecl memmove(void *, const void *, size_t);
#line 120 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"


 char *  __cdecl strchr(const char *, int);
 int     __cdecl _strcmpi(const char *, const char *);
 int     __cdecl _stricmp(const char *, const char *);
 int     __cdecl strcoll(const char *, const char *);
 int     __cdecl _stricoll(const char *, const char *);
 int     __cdecl _strncoll(const char *, const char *, size_t);
 int     __cdecl _strnicoll(const char *, const char *, size_t);
 size_t  __cdecl strcspn(const char *, const char *);
 char *  __cdecl _strdup(const char *);
 char *  __cdecl _strerror(const char *);
 char *  __cdecl strerror(int);
 char *  __cdecl _strlwr(char *);
 char *  __cdecl strncat(char *, const char *, size_t);
 int     __cdecl strncmp(const char *, const char *, size_t);
 int     __cdecl _strnicmp(const char *, const char *, size_t);
 char *  __cdecl strncpy(char *, const char *, size_t);
 char *  __cdecl _strnset(char *, int, size_t);
 char *  __cdecl strpbrk(const char *, const char *);
 char *  __cdecl strrchr(const char *, int);
 char *  __cdecl _strrev(char *);
 size_t  __cdecl strspn(const char *, const char *);
 char *  __cdecl strstr(const char *, const char *);
 char *  __cdecl strtok(char *, const char *);
 char *  __cdecl _strupr(char *);
 size_t  __cdecl strxfrm (char *, const char *, size_t);














 void * __cdecl memccpy(void *, const void *, int, unsigned int);
 int __cdecl memicmp(const void *, const void *, unsigned int);
 int __cdecl strcmpi(const char *, const char *);
 int __cdecl stricmp(const char *, const char *);
 char * __cdecl strdup(const char *);
 char * __cdecl strlwr(char *);
 int __cdecl strnicmp(const char *, const char *, size_t);
 char * __cdecl strnset(char *, int, size_t);
 char * __cdecl strrev(char *);
        char * __cdecl strset(char *, int);
 char * __cdecl strupr(char *);

#line 174 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"







 wchar_t * __cdecl wcscat(wchar_t *, const wchar_t *);
 wchar_t * __cdecl wcschr(const wchar_t *, wchar_t);
 int __cdecl wcscmp(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl wcscpy(wchar_t *, const wchar_t *);
 size_t __cdecl wcscspn(const wchar_t *, const wchar_t *);
 size_t __cdecl wcslen(const wchar_t *);
 wchar_t * __cdecl wcsncat(wchar_t *, const wchar_t *, size_t);
 int __cdecl wcsncmp(const wchar_t *, const wchar_t *, size_t);
 wchar_t * __cdecl wcsncpy(wchar_t *, const wchar_t *, size_t);
 wchar_t * __cdecl wcspbrk(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl wcsrchr(const wchar_t *, wchar_t);
 size_t __cdecl wcsspn(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl wcsstr(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl wcstok(wchar_t *, const wchar_t *);

 wchar_t * __cdecl _wcsdup(const wchar_t *);
 int __cdecl _wcsicmp(const wchar_t *, const wchar_t *);
 int __cdecl _wcsnicmp(const wchar_t *, const wchar_t *, size_t);
 wchar_t * __cdecl _wcsnset(wchar_t *, wchar_t, size_t);
 wchar_t * __cdecl _wcsrev(wchar_t *);
 wchar_t * __cdecl _wcsset(wchar_t *, wchar_t);

 wchar_t * __cdecl _wcslwr(wchar_t *);
 wchar_t * __cdecl _wcsupr(wchar_t *);
 size_t __cdecl wcsxfrm(wchar_t *, const wchar_t *, size_t);
 int __cdecl wcscoll(const wchar_t *, const wchar_t *);
 int __cdecl _wcsicoll(const wchar_t *, const wchar_t *);
 int __cdecl _wcsncoll(const wchar_t *, const wchar_t *, size_t);
 int __cdecl _wcsnicoll(const wchar_t *, const wchar_t *, size_t);







 wchar_t * __cdecl wcsdup(const wchar_t *);
 int __cdecl wcsicmp(const wchar_t *, const wchar_t *);
 int __cdecl wcsnicmp(const wchar_t *, const wchar_t *, size_t);
 wchar_t * __cdecl wcsnset(wchar_t *, wchar_t, size_t);
 wchar_t * __cdecl wcsrev(wchar_t *);
 wchar_t * __cdecl wcsset(wchar_t *, wchar_t);
 wchar_t * __cdecl wcslwr(wchar_t *);
 wchar_t * __cdecl wcsupr(wchar_t *);
 int __cdecl wcsicoll(const wchar_t *, const wchar_t *);

#line 228 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"


#line 231 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"

#line 233 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"





#line 239 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\string.h"
#line 21 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\assert.h"















#line 17 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\assert.h"



















#line 37 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\assert.h"























 void __cdecl _assert(void *, void *, unsigned);







#line 69 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\assert.h"
#line 22 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"















#pragma once
#line 18 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"






#line 25 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"







#pragma pack(push,8)
#line 34 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"














typedef char *  va_list;
#line 50 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"

#line 52 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"




































































































#line 153 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"







#pragma pack(pop)
#line 162 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"

#line 164 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdarg.h"
#line 23 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
















#pragma once
#line 19 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"






#line 26 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"







#pragma pack(push,8)
#line 35 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"






















#line 58 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"










































typedef int (__cdecl * _onexit_t)(void);



#line 105 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

#line 107 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"






typedef struct _div_t {
        int quot;
        int rem;
} div_t;

typedef struct _ldiv_t {
        long quot;
        long rem;
} ldiv_t;


#line 125 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"












 extern int __mb_cur_max;
#line 139 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"





















#line 161 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

















#line 179 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
 extern int errno;               
 extern unsigned long _doserrno; 
#line 182 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"







 extern char * _sys_errlist[];   
 extern int _sys_nerr;           





























#line 221 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

 extern int __argc;          
 extern char ** __argv;      

 extern wchar_t ** __wargv;  
#line 227 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"




 extern char ** _environ;    

 extern wchar_t ** _wenviron;    
#line 235 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
#line 236 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

 extern char * _pgmptr;      

 extern wchar_t * _wpgmptr;  
#line 241 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

#line 243 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"


 extern int _fmode;          
 extern int _fileinfo;       




 extern unsigned int _osver;
 extern unsigned int _winver;
 extern unsigned int _winmajor;
 extern unsigned int _winminor;





 __declspec(noreturn) void   __cdecl abort(void);
 __declspec(noreturn) void   __cdecl exit(int);



#line 266 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"



#line 270 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
        int    __cdecl abs(int);
#line 272 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
        int    __cdecl atexit(void (__cdecl *)(void));
 double __cdecl atof(const char *);
 int    __cdecl atoi(const char *);
 long   __cdecl atol(const char *);



 void * __cdecl bsearch(const void *, const void *, size_t, size_t,
        int (__cdecl *)(const void *, const void *));
 void * __cdecl calloc(size_t, size_t);
 div_t  __cdecl div(int, int);
 void   __cdecl free(void *);
 char * __cdecl getenv(const char *);
 char * __cdecl _itoa(int, char *, int);

 char * __cdecl _i64toa(__int64, char *, int);
 char * __cdecl _ui64toa(unsigned __int64, char *, int);
 __int64 __cdecl _atoi64(const char *);
#line 291 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"


#line 294 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
        long __cdecl labs(long);
#line 296 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
 ldiv_t __cdecl ldiv(long, long);
 char * __cdecl _ltoa(long, char *, int);
 void * __cdecl malloc(size_t);
 int    __cdecl mblen(const char *, size_t);
 size_t __cdecl _mbstrlen(const char *s);
 int    __cdecl mbtowc(wchar_t *, const char *, size_t);
 size_t __cdecl mbstowcs(wchar_t *, const char *, size_t);
 void   __cdecl qsort(void *, size_t, size_t, int (__cdecl *)
        (const void *, const void *));
 int    __cdecl rand(void);
 void * __cdecl realloc(void *, size_t);
 int    __cdecl _set_error_mode(int);
 void   __cdecl srand(unsigned int);
 double __cdecl strtod(const char *, char **);
 long   __cdecl strtol(const char *, char **, int);



 unsigned long __cdecl strtoul(const char *, char **, int);

 int    __cdecl system(const char *);
#line 318 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
 char * __cdecl _ultoa(unsigned long, char *, int);
 int    __cdecl wctomb(char *, wchar_t);
 size_t __cdecl wcstombs(char *, const wchar_t *, size_t);







 wchar_t * __cdecl _itow (int, wchar_t *, int);
 wchar_t * __cdecl _ltow (long, wchar_t *, int);
 wchar_t * __cdecl _ultow (unsigned long, wchar_t *, int);
 double __cdecl wcstod(const wchar_t *, wchar_t **);
 long   __cdecl wcstol(const wchar_t *, wchar_t **, int);
 unsigned long __cdecl wcstoul(const wchar_t *, wchar_t **, int);
 wchar_t * __cdecl _wgetenv(const wchar_t *);
 int    __cdecl _wsystem(const wchar_t *);
 int __cdecl _wtoi(const wchar_t *);
 long __cdecl _wtol(const wchar_t *);

 wchar_t * __cdecl _i64tow(__int64, wchar_t *, int);
 wchar_t * __cdecl _ui64tow(unsigned __int64, wchar_t *, int);
 __int64   __cdecl _wtoi64(const wchar_t *);
#line 343 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"


#line 346 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
#line 347 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"




 char * __cdecl _ecvt(double, int, int *, int *);

 __declspec(noreturn) void   __cdecl _exit(int);


#line 357 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
 char * __cdecl _fcvt(double, int, int *, int *);
 char * __cdecl _fullpath(char *, const char *, size_t);
 char * __cdecl _gcvt(double, int, char *);
        unsigned long __cdecl _lrotl(unsigned long, int);
        unsigned long __cdecl _lrotr(unsigned long, int);

 void   __cdecl _makepath(char *, const char *, const char *, const char *,
        const char *);
#line 366 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
        _onexit_t __cdecl _onexit(_onexit_t);
 void   __cdecl perror(const char *);
 int    __cdecl _putenv(const char *);
        unsigned int __cdecl _rotl(unsigned int, int);
        unsigned int __cdecl _rotr(unsigned int, int);
 void   __cdecl _searchenv(const char *, const char *, char *);

 void   __cdecl _splitpath(const char *, char *, char *, char *, char *);
#line 375 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
 void   __cdecl _swab(char *, char *, int);






 wchar_t * __cdecl _wfullpath(wchar_t *, const wchar_t *, size_t);
 void   __cdecl _wmakepath(wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *,
        const wchar_t *);
 void   __cdecl _wperror(const wchar_t *);
 int    __cdecl _wputenv(const wchar_t *);
 void   __cdecl _wsearchenv(const wchar_t *, const wchar_t *, wchar_t *);
 void   __cdecl _wsplitpath(const wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);


#line 392 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
#line 393 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"




 void __cdecl _seterrormode(int);
 void __cdecl _beep(unsigned, unsigned);
 void __cdecl _sleep(unsigned long);
#line 401 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"


#line 404 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"







 int __cdecl tolower(int);
#line 413 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

 int __cdecl toupper(int);
#line 416 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

#line 418 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"











#line 430 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"





 char * __cdecl ecvt(double, int, int *, int *);
 char * __cdecl fcvt(double, int, int *, int *);
 char * __cdecl gcvt(double, int, char *);
 char * __cdecl itoa(int, char *, int);
 char * __cdecl ltoa(long, char *, int);
        _onexit_t __cdecl onexit(_onexit_t);
 int    __cdecl putenv(const char *);
 void   __cdecl swab(char *, char *, int);
 char * __cdecl ultoa(unsigned long, char *, int);

#line 446 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

#line 448 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"







#pragma pack(pop)
#line 457 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"

#line 459 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdlib.h"
#line 24 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"















#pragma once
#line 18 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"






#line 25 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"







#pragma pack(push,8)
#line 34 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"






















#line 57 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"


























typedef wchar_t wint_t;
typedef wchar_t wctype_t;

#line 87 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"
#line 88 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"



















#line 108 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

#line 110 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"






























#line 141 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"





struct _iobuf {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;
        int   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _iobuf FILE;

#line 159 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"












#line 172 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"












#line 185 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"



































 extern FILE _iob[];
#line 222 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"









#line 232 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"


typedef __int64 fpos_t;







#line 243 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"
#line 244 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"


#line 247 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"




























 int __cdecl _filbuf(FILE *);
 int __cdecl _flsbuf(int, FILE *);




 FILE * __cdecl _fsopen(const char *, const char *, int);
#line 283 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

 void __cdecl clearerr(FILE *);
 int __cdecl fclose(FILE *);
 int __cdecl _fcloseall(void);




 FILE * __cdecl _fdopen(int, const char *);
#line 293 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

 int __cdecl feof(FILE *);
 int __cdecl ferror(FILE *);
 int __cdecl fflush(FILE *);
 int __cdecl fgetc(FILE *);
 int __cdecl _fgetchar(void);
 int __cdecl fgetpos(FILE *, fpos_t *);
 char * __cdecl fgets(char *, int, FILE *);




 int __cdecl _fileno(FILE *);
#line 307 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

 int __cdecl _flushall(void);
 FILE * __cdecl fopen(const char *, const char *);
 int __cdecl fprintf(FILE *, const char *, ...);
 int __cdecl fputc(int, FILE *);
 int __cdecl _fputchar(int);
 int __cdecl fputs(const char *, FILE *);
 size_t __cdecl fread(void *, size_t, size_t, FILE *);
 FILE * __cdecl freopen(const char *, const char *, FILE *);
 int __cdecl fscanf(FILE *, const char *, ...);
 int __cdecl fsetpos(FILE *, const fpos_t *);
 int __cdecl fseek(FILE *, long, int);
 long __cdecl ftell(FILE *);
 size_t __cdecl fwrite(const void *, size_t, size_t, FILE *);
 int __cdecl getc(FILE *);
 int __cdecl getchar(void);
 int __cdecl _getmaxstdio(void);
 char * __cdecl gets(char *);
 int __cdecl _getw(FILE *);
 void __cdecl perror(const char *);
 int __cdecl _pclose(FILE *);
 FILE * __cdecl _popen(const char *, const char *);
 int __cdecl printf(const char *, ...);
 int __cdecl putc(int, FILE *);
 int __cdecl putchar(int);
 int __cdecl puts(const char *);
 int __cdecl _putw(int, FILE *);
 int __cdecl remove(const char *);
 int __cdecl rename(const char *, const char *);
 void __cdecl rewind(FILE *);
 int __cdecl _rmtmp(void);
 int __cdecl scanf(const char *, ...);
 void __cdecl setbuf(FILE *, char *);
 int __cdecl _setmaxstdio(int);
 int __cdecl setvbuf(FILE *, char *, int, size_t);
 int __cdecl _snprintf(char *, size_t, const char *, ...);
 int __cdecl sprintf(char *, const char *, ...);
 int __cdecl sscanf(const char *, const char *, ...);
 char * __cdecl _tempnam(const char *, const char *);
 FILE * __cdecl tmpfile(void);
 char * __cdecl tmpnam(char *);
 int __cdecl ungetc(int, FILE *);
 int __cdecl _unlink(const char *);
 int __cdecl vfprintf(FILE *, const char *, va_list);
 int __cdecl vprintf(const char *, va_list);
 int __cdecl _vsnprintf(char *, size_t, const char *, va_list);
 int __cdecl vsprintf(char *, const char *, va_list);








#line 363 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"




 FILE * __cdecl _wfsopen(const wchar_t *, const wchar_t *, int);
#line 369 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

 wint_t __cdecl fgetwc(FILE *);
 wint_t __cdecl _fgetwchar(void);
 wint_t __cdecl fputwc(wint_t, FILE *);
 wint_t __cdecl _fputwchar(wint_t);
 wint_t __cdecl getwc(FILE *);
 wint_t __cdecl getwchar(void);
 wint_t __cdecl putwc(wint_t, FILE *);
 wint_t __cdecl putwchar(wint_t);
 wint_t __cdecl ungetwc(wint_t, FILE *);

 wchar_t * __cdecl fgetws(wchar_t *, int, FILE *);
 int __cdecl fputws(const wchar_t *, FILE *);
 wchar_t * __cdecl _getws(wchar_t *);
 int __cdecl _putws(const wchar_t *);

 int __cdecl fwprintf(FILE *, const wchar_t *, ...);
 int __cdecl wprintf(const wchar_t *, ...);
 int __cdecl _snwprintf(wchar_t *, size_t, const wchar_t *, ...);
 int __cdecl swprintf(wchar_t *, const wchar_t *, ...);
 int __cdecl vfwprintf(FILE *, const wchar_t *, va_list);
 int __cdecl vwprintf(const wchar_t *, va_list);
 int __cdecl _vsnwprintf(wchar_t *, size_t, const wchar_t *, va_list);
 int __cdecl vswprintf(wchar_t *, const wchar_t *, va_list);
 int __cdecl fwscanf(FILE *, const wchar_t *, ...);
 int __cdecl swscanf(const wchar_t *, const wchar_t *, ...);
 int __cdecl wscanf(const wchar_t *, ...);






 FILE * __cdecl _wfdopen(int, const wchar_t *);
 FILE * __cdecl _wfopen(const wchar_t *, const wchar_t *);
 FILE * __cdecl _wfreopen(const wchar_t *, const wchar_t *, FILE *);
 void __cdecl _wperror(const wchar_t *);
 FILE * __cdecl _wpopen(const wchar_t *, const wchar_t *);
 int __cdecl _wremove(const wchar_t *);
 wchar_t * __cdecl _wtempnam(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl _wtmpnam(wchar_t *);



#line 414 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"
#line 415 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"


#line 418 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"
































 int __cdecl fcloseall(void);
 FILE * __cdecl fdopen(int, const char *);
 int __cdecl fgetchar(void);
 int __cdecl fileno(FILE *);
 int __cdecl flushall(void);
 int __cdecl fputchar(int);
 int __cdecl getw(FILE *);
 int __cdecl putw(int, FILE *);
 int __cdecl rmtmp(void);
 char * __cdecl tempnam(const char *, const char *);
 int __cdecl unlink(const char *);

#line 463 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"






#pragma pack(pop)
#line 471 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"

#line 473 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\stdio.h"
#line 25 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"
















#pragma once
#line 19 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"






#line 26 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"







#pragma pack(push,8)
#line 35 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"






















#line 58 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"
















#line 75 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"




typedef long time_t;        

#line 82 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"


typedef long clock_t;

#line 87 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"



















struct tm {
        int tm_sec;     
        int tm_min;     
        int tm_hour;    
        int tm_mday;    
        int tm_mon;     
        int tm_year;    
        int tm_wday;    
        int tm_yday;    
        int tm_isdst;   
        };

#line 119 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"












 extern int _daylight;


 extern long _dstbias;


 extern long _timezone;


 extern char * _tzname[2];




 char * __cdecl asctime(const struct tm *);
 char * __cdecl ctime(const time_t *);
 clock_t __cdecl clock(void);
 double __cdecl difftime(time_t, time_t);
 struct tm * __cdecl gmtime(const time_t *);
 struct tm * __cdecl localtime(const time_t *);
 time_t __cdecl mktime(struct tm *);
 size_t __cdecl strftime(char *, size_t, const char *,
        const struct tm *);
 char * __cdecl _strdate(char *);
 char * __cdecl _strtime(char *);
 time_t __cdecl time(time_t *);




 void __cdecl _tzset(void);
#line 163 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"



unsigned __cdecl _getsystime(struct tm *);
unsigned __cdecl _setsystime(struct tm *, unsigned);












 
 wchar_t * __cdecl _wasctime(const struct tm *);
 wchar_t * __cdecl _wctime(const time_t *);
 size_t __cdecl wcsftime(wchar_t *, size_t, const wchar_t *,
        const struct tm *);
 wchar_t * __cdecl _wstrdate(wchar_t *);
 wchar_t * __cdecl _wstrtime(wchar_t *);


#line 190 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"
#line 191 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"








 extern int daylight;
 extern long timezone;
 extern char * tzname[2];

 void __cdecl tzset(void);

#line 206 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"







#pragma pack(pop)
#line 215 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"

#line 217 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\time.h"
#line 26 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"
















#pragma once
#line 19 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"






#line 26 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"























#line 50 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"





























































#line 112 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"



 unsigned int __cdecl _clearfp(void);
 unsigned int __cdecl _controlfp(unsigned int,unsigned int);
 unsigned int __cdecl _statusfp(void);
 void __cdecl _fpreset(void);




#line 124 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"








#line 133 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"






































#line 172 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"










 unsigned int __cdecl _control87(unsigned int,unsigned int);



























#line 211 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"






#line 218 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"
extern int _fpecode;
#line 220 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"



























 double __cdecl _copysign (double, double);
 double __cdecl _chgsign (double);
 double __cdecl _scalb(double, long);
 double __cdecl _logb(double);
 double __cdecl _nextafter(double, double);
 int    __cdecl _finite(double);
 int    __cdecl _isnan(double);
 int    __cdecl _fpclass(double);





















#line 277 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"

 void __cdecl fpreset(void);


























































#line 338 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"





#line 344 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\float.h"
#line 27 "..\\include\\nut.h"
#line 1 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"















#pragma once
#line 18 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"






#line 25 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"







#pragma pack(push,8)
#line 34 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"






















#line 57 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"

















struct _exception {
        int type;       
        char *name;     
        double arg1;    
        double arg2;    
        double retval;  
        } ;


#line 84 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"







struct _complex {
        double x,y; 
        } ;




#line 99 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"


#line 102 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
#line 103 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"





















 extern double _HUGE;
#line 126 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"



























#line 154 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
        int     __cdecl abs(int);
        double  __cdecl acos(double);
        double  __cdecl asin(double);
        double  __cdecl atan(double);
        double  __cdecl atan2(double, double);
        double  __cdecl cos(double);
        double  __cdecl cosh(double);
        double  __cdecl exp(double);
        double  __cdecl fabs(double);
        double  __cdecl fmod(double, double);
        long    __cdecl labs(long);
        double  __cdecl log(double);
        double  __cdecl log10(double);
        double  __cdecl pow(double, double);
        double  __cdecl sin(double);
        double  __cdecl sinh(double);
        double  __cdecl tan(double);
        double  __cdecl tanh(double);
        double  __cdecl sqrt(double);
#line 174 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
 double  __cdecl atof(const char *);
 double  __cdecl _cabs(struct _complex);



#line 180 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
 double  __cdecl ceil(double);
 double  __cdecl floor(double);
#line 183 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
 double  __cdecl frexp(double, int *);
 double  __cdecl _hypot(double, double);
 double  __cdecl _j0(double);
 double  __cdecl _j1(double);
 double  __cdecl _jn(int, double);
 double  __cdecl ldexp(double, int);
        int     __cdecl _matherr(struct _exception *);
 double  __cdecl modf(double, double *);

 double  __cdecl _y0(double);
 double  __cdecl _y1(double);
 double  __cdecl _yn(int, double);








































#line 236 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"







































#line 276 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"

































































































































#line 406 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
#line 407 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
#line 408 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"














#line 423 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"



 extern double HUGE;

 double  __cdecl cabs(struct _complex);
 double  __cdecl hypot(double, double);
 double  __cdecl j0(double);
 double  __cdecl j1(double);
 double  __cdecl jn(int, double);
        int     __cdecl _matherr(struct _exception *);
 double  __cdecl y0(double);
 double  __cdecl y1(double);
 double  __cdecl yn(int, double);

#line 439 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"

#line 441 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"






































































































































































































#pragma pack(pop)
#line 641 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"

#line 643 "F:\\Program Files\\Microsoft Visual Studio\\VC98\\include\\math.h"
#line 28 "..\\include\\nut.h"



















#line 48 "..\\include\\nut.h"

#line 50 "..\\include\\nut.h"












static void
_safe_str_cpy(char *dst, char const *src, size_t num)
{
   (void)( (dst != ((void *)0)) || (_assert("dst != NULL", "..\\include\\nut.h", 65), 0) );
   (void)( (src != ((void *)0)) || (_assert("src != NULL", "..\\include\\nut.h", 66), 0) );
   (void)( (num > 0) || (_assert("num > 0", "..\\include\\nut.h", 67), 0) );
   strncpy(dst, src, num);
   dst[num-1] = '\0';
}


int 
nut_snprintf(char *buffer, size_t buffer_len, char *format, ...)
{
   int count =0;
   va_list args;
   ( args = (va_list)&format + ( (sizeof(format) + sizeof(int) - 1) & ~(sizeof(int) - 1) ) );
   count =vsnprintf(buffer, buffer_len, format, args);
   ( args = (va_list)0 );
   return count;
}





static int
nut_filter_pass(char const *prefix, char const *test_str)
{
   int is_match = 0;
   char const *prefix_p;
   char const *test_str_p;

   
   (void)( (test_str != ((void *)0)) || (_assert("test_str != NULL", "..\\include\\nut.h", 96), 0) );

   
   if ( prefix == ((void *)0)  || prefix[0] == '\0' ) 
   { 
      return 1;
   }
     
   

   for ( prefix_p = prefix, test_str_p = test_str; 
         *prefix_p != '\0' && *test_str_p != '\0'; 
         ++prefix_p, ++test_str_p )
   {
      is_match = *prefix_p == *test_str_p;
      if ( !is_match ) 
      {
         break;   
      }
   }
   
   



   if ( *test_str_p == '\0' && *prefix_p != '\0' )
   {
      return 0;
   }

   


   return is_match;
}


int 
nut_real_eq(double v1, double v2)
{
   return (int)(fabs(v1 - v2) < 2.2204460492503131e-016);
}







































typedef struct _nlist_t nlist_t;
struct _nlist_t
{ 
   
   void **itm_list;
   
   
   size_t avail_itm_num;

   
   size_t used_itm_num;
};

static nlist_t *
nlist_new(void)
{
   nlist_t *list = calloc(1, sizeof(nlist_t));
   (void)( (list != ((void *)0) && "memory check") || (_assert("list != NULL && \"memory check\"", "..\\include\\nut.h", 194), 0) );

   list->itm_list = malloc(sizeof(void*)*4);
   (void)( (list->itm_list != ((void *)0) && "memory check") || (_assert("list->itm_list != NULL && \"memory check\"", "..\\include\\nut.h", 197), 0) );

   list->avail_itm_num =4;
   list->used_itm_num =0;
   return list;
}




static void
nlist__del(nlist_t *list, void (*on_del)(void*))
{
   size_t itm_i =0;

   if ( list == ((void *)0) ) { return; }

   

   if ( on_del != ((void *)0) )
   {
      for ( itm_i =0; itm_i != list->used_itm_num; ++itm_i )
      {
         on_del(list->itm_list[itm_i]);
      }
   }

   free(list->itm_list);
   free(list);
}

static size_t
nlist__size(nlist_t const *list)
{
   (void)( (list != ((void *)0)) || (_assert("list != NULL", "..\\include\\nut.h", 231), 0) );
   return list->used_itm_num;
}


static void*
nlist__at(nlist_t const *list, size_t idx)
{
   (void)( (list != ((void *)0)) || (_assert("list != NULL", "..\\include\\nut.h", 239), 0) );
   (void)( (idx < list->used_itm_num) || (_assert("idx < list->used_itm_num", "..\\include\\nut.h", 240), 0) );
   return list->itm_list[idx];
}

static void
nlist__append(nlist_t *list, void *itm)
{
   (void)( (list != ((void *)0)) || (_assert("list != NULL", "..\\include\\nut.h", 247), 0) );
   (void)( (list->itm_list != ((void *)0)) || (_assert("list->itm_list != NULL", "..\\include\\nut.h", 248), 0) );
   (void)( (list->avail_itm_num != 0) || (_assert("list->avail_itm_num != 0", "..\\include\\nut.h", 249), 0) );

   

   if ( list->used_itm_num == list->avail_itm_num )
   {
      list->avail_itm_num = list->avail_itm_num*2;
      list->itm_list = realloc(
         list->itm_list, sizeof(void*)*list->avail_itm_num
         );
      (void)( (list->itm_list != ((void *)0) && "memory check") || (_assert("list->itm_list != NULL && \"memory check\"", "..\\include\\nut.h", 259), 0) );
   }

   list->itm_list[list->used_itm_num] = itm;
   ++(list->used_itm_num);
}














typedef struct _nut_logger_i nut_logger_i;
typedef void (*nut_logger_on_cndtn_fn)(nut_logger_i *self,
                                       char const* cndtn, 
                                       char const *file, 
                                       int lineno);










struct _nut_logger_i {
   nut_logger_on_cndtn_fn on_cndtn_pass; nut_logger_on_cndtn_fn on_cndtn_fail; void (*on_test_start)(nut_logger_i *logger, char const* test_name); void (*on_test_end)(nut_logger_i *logger, char const* test_name, int is_pass); void (*on_test_suite_start)(nut_logger_i *logger, char const *suite_name); void (*on_test_suite_end)(nut_logger_i *logger, char const *suite_name); void (*on_nut_end)(nut_logger_i *logger); void (*on_delete)(nut_logger_i *logger);
};

static void
nut_logger__del(nut_logger_i *logger)
{
   if ( logger == ((void *)0) ) { return; }
   if ( logger->on_delete) { logger->on_delete(logger); }
}

static void
nut_logger__on_test_start(nut_logger_i *logger, char const *test_name)
{
   (void)( (logger != ((void *)0) && "invalid arg") || (_assert("logger != NULL && \"invalid arg\"", "..\\include\\nut.h", 308), 0) );
   (void)( (test_name != ((void *)0) && "invalid arg") || (_assert("test_name != NULL && \"invalid arg\"", "..\\include\\nut.h", 309), 0) );
   (void)( (strlen(test_name) > 0 && "invalid arg") || (_assert("strlen(test_name) > 0 && \"invalid arg\"", "..\\include\\nut.h", 310), 0) );

   if ( logger->on_test_start != ((void *)0) )
   {
      logger->on_test_start(logger, test_name);
   }
}

static void
nut_logger__on_test_end(nut_logger_i *logger, 
                        char const *test_name, 
                        int is_pass)
{
   (void)( (logger != ((void *)0) && "invalid arg") || (_assert("logger != NULL && \"invalid arg\"", "..\\include\\nut.h", 323), 0) );
   (void)( (test_name != ((void *)0) && "invalid arg") || (_assert("test_name != NULL && \"invalid arg\"", "..\\include\\nut.h", 324), 0) );
   (void)( (strlen(test_name) > 0 && "invalid arg") || (_assert("strlen(test_name) > 0 && \"invalid arg\"", "..\\include\\nut.h", 325), 0) );
   if ( logger->on_test_end != ((void *)0) )
   {
      logger->on_test_end(logger, test_name, is_pass);
   }
}

static void
nut_logger__on_test_suite_start(nut_logger_i *logger, char const *suite_name)
{
   (void)( (suite_name != ((void *)0)) || (_assert("suite_name != NULL", "..\\include\\nut.h", 335), 0) );
   (void)( (strlen(suite_name) > 0) || (_assert("strlen(suite_name) > 0", "..\\include\\nut.h", 336), 0) );
   (void)( (logger != ((void *)0)) || (_assert("logger != NULL", "..\\include\\nut.h", 337), 0) );

   if ( logger->on_test_suite_start != ((void *)0) )
   {
      logger->on_test_suite_start(logger, suite_name);
   }
}

static void
nut_logger__on_test_suite_end(nut_logger_i *logger, char const *suite_name)
{
   (void)( (suite_name != ((void *)0)) || (_assert("suite_name != NULL", "..\\include\\nut.h", 348), 0) );
   (void)( (strlen(suite_name) > 0) || (_assert("strlen(suite_name) > 0", "..\\include\\nut.h", 349), 0) );
   (void)( (logger != ((void *)0)) || (_assert("logger != NULL", "..\\include\\nut.h", 350), 0) );

   if ( logger->on_test_suite_end != ((void *)0) )
   {
      logger->on_test_suite_end(logger, suite_name);
   }
}

static void
nut_logger__on_cndtn_pass(nut_logger_i *self,
                              char const *cndtn,
                              char const *file,
                              int lineno)
{
   (void)( (self != ((void *)0)) || (_assert("self != NULL", "..\\include\\nut.h", 364), 0) );
   (void)( (cndtn != ((void *)0)) || (_assert("cndtn != NULL", "..\\include\\nut.h", 365), 0) );
   (void)( (strlen(cndtn) > 0) || (_assert("strlen(cndtn) > 0", "..\\include\\nut.h", 366), 0) );
   (void)( (file != ((void *)0)) || (_assert("file != NULL", "..\\include\\nut.h", 367), 0) );
   (void)( (strlen(file) > 0) || (_assert("strlen(file) > 0", "..\\include\\nut.h", 368), 0) );
   (void)( (lineno > 0) || (_assert("lineno > 0", "..\\include\\nut.h", 369), 0) );
   if ( self->on_cndtn_pass != ((void *)0) )
   {
      self->on_cndtn_pass(self, cndtn, file, lineno);
   }
}

static void
nut_logger__on_cndtn_fail(nut_logger_i *self,
                              char const *cndtn,
                              char const *file,
                              int lineno)
{
   (void)( (self != ((void *)0)) || (_assert("self != NULL", "..\\include\\nut.h", 382), 0) );
   (void)( (cndtn != ((void *)0)) || (_assert("cndtn != NULL", "..\\include\\nut.h", 383), 0) );
   (void)( (strlen(cndtn) > 0) || (_assert("strlen(cndtn) > 0", "..\\include\\nut.h", 384), 0) );
   (void)( (file != ((void *)0)) || (_assert("file != NULL", "..\\include\\nut.h", 385), 0) );
   (void)( (strlen(file) > 0) || (_assert("strlen(file) > 0", "..\\include\\nut.h", 386), 0) );
   (void)( (lineno > 0) || (_assert("lineno > 0", "..\\include\\nut.h", 387), 0) );
   if ( self->on_cndtn_fail != ((void *)0) )
   {
      self->on_cndtn_fail(self, cndtn, file, lineno);
   }
}



static void
nut_logger__on_cndtn(nut_logger_i *logger,
                     int is_pass,
                     char const *cndtn,
                     char const *file,
                     int lineno)
{
   (void)( (logger != ((void *)0)) || (_assert("logger != NULL", "..\\include\\nut.h", 403), 0) );
   (void)( (cndtn != ((void *)0)) || (_assert("cndtn != NULL", "..\\include\\nut.h", 404), 0) );
   (void)( (strlen(cndtn) > 0) || (_assert("strlen(cndtn) > 0", "..\\include\\nut.h", 405), 0) );
   (void)( (file != ((void *)0)) || (_assert("file != NULL", "..\\include\\nut.h", 406), 0) );
   (void)( (strlen(file) > 0) || (_assert("strlen(file) > 0", "..\\include\\nut.h", 407), 0) );
   (void)( (lineno > 0) || (_assert("lineno > 0", "..\\include\\nut.h", 408), 0) );
   if ( is_pass )
   {
      nut_logger__on_cndtn_pass(logger, cndtn, file, lineno);
   }
   else
   {
      nut_logger__on_cndtn_fail(logger, cndtn, file, lineno);
   }
}                        


static void
nut_logger__on_nut_end(nut_logger_i *logger)
{
   (void)( (logger != ((void *)0)) || (_assert("logger != NULL", "..\\include\\nut.h", 423), 0) );
   if ( logger->on_nut_end )
   {
      logger->on_nut_end(logger);
   }
}









typedef struct _nut_minimal_logger_t nut_minimal_logger_t;
struct _nut_minimal_logger_t {
   nut_logger_on_cndtn_fn on_cndtn_pass; nut_logger_on_cndtn_fn on_cndtn_fail; void (*on_test_start)(nut_logger_i *logger, char const* test_name); void (*on_test_end)(nut_logger_i *logger, char const* test_name, int is_pass); void (*on_test_suite_start)(nut_logger_i *logger, char const *suite_name); void (*on_test_suite_end)(nut_logger_i *logger, char const *suite_name); void (*on_nut_end)(nut_logger_i *logger); void (*on_delete)(nut_logger_i *logger);
};

static void 
nut_minimal_logger__on_cndtn_fail(nut_logger_i *self, 
                                  char const* cndtn, 
                                  char const *file,
                                  int lineno)
{
   
   self; cndtn; file; lineno; 
   printf("!", file, lineno, cndtn);
}

static void 
nut_minimal_logger__on_cndtn_pass(nut_logger_i *self, 
                                      char const* cndtn, 
                                      char const *file,
                                      int lineno)
{
   
   self; cndtn; file; lineno;
   printf(".");
}

static void
nut_minimal_logger__del(nut_logger_i *self)
{
   free(self);
}

static nut_minimal_logger_t *
nut_minimal_logger__new(void)
{
   nut_minimal_logger_t *self = calloc(1,sizeof(nut_minimal_logger_t));
   if ( self == ((void *)0) ) { return ((void *)0); }
   self->on_cndtn_fail = nut_minimal_logger__on_cndtn_fail;
   self->on_cndtn_pass = nut_minimal_logger__on_cndtn_pass;
   self->on_delete = nut_minimal_logger__del;
   return self;
}







typedef struct _nut_standard_logger_t nut_standard_logger_t;
struct _nut_standard_logger_t {
   nut_logger_on_cndtn_fn on_cndtn_pass; nut_logger_on_cndtn_fn on_cndtn_fail; void (*on_test_start)(nut_logger_i *logger, char const* test_name); void (*on_test_end)(nut_logger_i *logger, char const* test_name, int is_pass); void (*on_test_suite_start)(nut_logger_i *logger, char const *suite_name); void (*on_test_suite_end)(nut_logger_i *logger, char const *suite_name); void (*on_nut_end)(nut_logger_i *logger); void (*on_delete)(nut_logger_i *logger);

   
   nlist_t *failed_cndtns_list;
};



static void
nut_standard_logger__on_cndtn_fail(
   nut_logger_i *logger_, 
   char const* cndtn, 
   char const *file,
   int lineno
   )
{
   nut_standard_logger_t *logger = (nut_standard_logger_t*)logger_;
   char *str =((void *)0);
   
   (void)( (logger != ((void *)0)) || (_assert("logger != NULL", "..\\include\\nut.h", 509), 0) );

   

   str = malloc(sizeof(char)*256);
   (void)( (str != ((void *)0)) || (_assert("str != NULL", "..\\include\\nut.h", 514), 0) );
   
   nut_snprintf(
      str, 256, "%s(%d): %s", file, lineno, cndtn
      );

   
   nlist__append(logger->failed_cndtns_list, (void*)str);
}

static void
nut_standard_logger__on_test_start(
   nut_logger_i *logger_, 
   char const *test
   )
{
   (logger_);;
   printf("%s ... ", test);
}

static void
nut_standard_logger__on_test_end(
   nut_logger_i *logger_, 
   char const *test,
   int is_pass
   )
{
   (logger_);;
   (test);;
   printf("%s\n", (is_pass) ? "PASS" : "FAIL" );
}

static void
nut_standard_logger__del(nut_logger_i *logger_)
{
   nut_standard_logger_t *logger = (nut_standard_logger_t*)logger_;

   { if ( logger->failed_cndtns_list != ((void *)0) ) { size_t item_icndtn_str; size_t num_itemscndtn_str = nlist__size(logger->failed_cndtns_list); for( item_icndtn_str =0; item_icndtn_str != num_itemscndtn_str; ++item_icndtn_str ) { char * cndtn_str = (char *) nlist__at((logger->failed_cndtns_list), item_icndtn_str);
   {
      free(cndtn_str);
   }
   }}};

   free(logger);
   logger_ =((void *)0);
}

static void
nut_standard_logger__on_nut_end(nut_logger_i *logger_)
{
   (logger_);;



































#line 601 "..\\include\\nut.h"
}

static nut_standard_logger_t *
nut_standard_logger__new(void)
{
   nut_standard_logger_t *logger = calloc(1, sizeof(nut_standard_logger_t));
   if ( logger == ((void *)0) ) 
   { 
      return ((void *)0); 
   }
   logger->on_cndtn_fail = nut_standard_logger__on_cndtn_fail;
   logger->on_cndtn_pass = ((void *)0);
   logger->on_test_start = nut_standard_logger__on_test_start;
   logger->on_test_end = nut_standard_logger__on_test_end;
   logger->on_test_suite_start = ((void *)0);
   logger->on_test_suite_end = ((void *)0);
   logger->on_nut_end = nut_standard_logger__on_nut_end;
   logger->on_delete = nut_standard_logger__del;

   logger->failed_cndtns_list = nlist_new();
   (void)( (logger->failed_cndtns_list != ((void *)0)) || (_assert("logger->failed_cndtns_list != NULL", "..\\include\\nut.h", 621), 0) );

   return logger;
}
























    
enum ts_mode {
   ts_mode_cnt,       
   ts_mode_setup,       
   ts_mode_teardown,    
   ts_mode_test,        
   ts_mode_ending       
};





typedef enum {
   nut_test_status_SUCCESS,
   nut_test_status_FAILURE
} nut_test_status;

typedef struct _nut_ts_t nut_ts_t;
struct _nut_ts_t {
   

   int  curr_test_num;
   int  total_test_num;

   enum ts_mode mode;
};









static void
nut_ts__inc_total_test_num(nut_ts_t *ts)
{
   (void)( (ts != ((void *)0)) || (_assert("ts != NULL", "..\\include\\nut.h", 688), 0) );
   (void)( (((ts)->mode == ts_mode_cnt)) || (_assert("nut_ts__is_cnt_mode(ts)", "..\\include\\nut.h", 689), 0) );
   ++(ts->total_test_num);
}

static int
nut_ts__is_more_tests(nut_ts_t const *self)
{
   (void)( (self != ((void *)0)) || (_assert("self != NULL", "..\\include\\nut.h", 696), 0) );
   return self->curr_test_num < self->total_test_num;
}



static void
nut_ts__setup_end(nut_ts_t *ts)
{
   (void)( (((ts)->mode == ts_mode_setup)) || (_assert("nut_ts__is_setup_mode(ts)", "..\\include\\nut.h", 705), 0) );
   ts->mode = ts_mode_test;
}



static void
nut_ts__ending(nut_ts_t *ts)
{
   
   (void)( (((ts)->mode == ts_mode_test)) || (_assert("nut_ts__is_test_mode(ts)", "..\\include\\nut.h", 715), 0) );
   ts->mode = ts_mode_ending;
}



static void
nut_ts__teardown_end(nut_ts_t *ts)
{
   (void)( (((ts)->mode == ts_mode_teardown)) || (_assert("nut_ts__is_teardown_mode(ts)", "..\\include\\nut.h", 724), 0) );
   ts->mode = ts_mode_setup;
}





static void
nut_ts__cnt_end(nut_ts_t *ts)
{
   (void)( (ts != ((void *)0)) || (_assert("ts != NULL", "..\\include\\nut.h", 735), 0) );
   (void)( (((ts)->mode == ts_mode_cnt)) || (_assert("nut_ts__is_cnt_mode(ts)", "..\\include\\nut.h", 736), 0) );
   if (ts->total_test_num == 0  ) {
      ts->mode = ts_mode_ending;
   }
   else {
      ts->mode = ts_mode_setup;
   }
}

static int
nut_ts__is_test_cnt(nut_ts_t const *ts, int test_num)
{
   (void)( (ts != ((void *)0)) || (_assert("ts != NULL", "..\\include\\nut.h", 748), 0) );
   (void)( (0 <= test_num) || (_assert("0 <= test_num", "..\\include\\nut.h", 749), 0) );
   (void)( (test_num < ts->total_test_num) || (_assert("test_num < ts->total_test_num", "..\\include\\nut.h", 750), 0) );

   

   return test_num == ts->curr_test_num;
}










typedef struct _nutkern_t nutkern_t;
struct _nutkern_t
{
   

   nlist_t *logger_list;

   

   nlist_t *prefix_list;

};



static void
nut__cnt_chk(nutkern_t *nut, int is_pass);
static void 
nut__cnt_tst(nutkern_t *nut, int is_pass);


static void
nutkearn__add_logger(nutkern_t *nut, nut_logger_i *logger_owns)
{
   (void)( (nut != ((void *)0) && "invalid arg") || (_assert("nut != NULL && \"invalid arg\"", "..\\include\\nut.h", 790), 0) );
   (void)( (logger_owns != ((void *)0) && "invalid arg") || (_assert("logger_owns != NULL && \"invalid arg\"", "..\\include\\nut.h", 791), 0) );
   nlist__append(nut->logger_list, logger_owns);
   (void)( (nut->logger_list != ((void *)0) && "memory check") || (_assert("nut->logger_list != NULL && \"memory check\"", "..\\include\\nut.h", 793), 0) );
}





static void
nutkearn__add_prefix_filter(nutkern_t const *nut, char const *prefix_filter)
{
   char *filter =((void *)0);
   int filter_len =0;

   (void)( (nut != ((void *)0) && "invalid arg") || (_assert("nut != NULL && \"invalid arg\"", "..\\include\\nut.h", 806), 0) );
   (void)( (prefix_filter != ((void *)0) && "invalid arg") || (_assert("prefix_filter != NULL && \"invalid arg\"", "..\\include\\nut.h", 807), 0) );
   (void)( (strlen(prefix_filter) > 0 && "invalid arg") || (_assert("strlen(prefix_filter) > 0 && \"invalid arg\"", "..\\include\\nut.h", 808), 0) );

   

   filter_len = strlen(prefix_filter);
   filter = malloc(sizeof(char)*(filter_len+1));
   strncpy(filter, prefix_filter, filter_len);
   filter[filter_len] = '\0';

   nlist__append(nut->prefix_list, (void*)filter);
}



static void
nutkearn_init(nutkern_t *nk, int argc, char *argv[])
{
   nut_logger_i *minimal_logger = ((void *)0);
   int arg_i =0;

   (void)( (nk != ((void *)0)) || (_assert("nk != NULL", "..\\include\\nut.h", 828), 0) );

   memset(nk, 0, sizeof(nutkern_t));

   nk->logger_list = nlist_new();
   nk->prefix_list = nlist_new();

   minimal_logger = (nut_logger_i*) nut_standard_logger__new();
   (void)( (minimal_logger != ((void *)0)) || (_assert("minimal_logger != NULL", "..\\include\\nut.h", 836), 0) );

   

   nutkearn__add_logger(nk, minimal_logger);   
   minimal_logger = ((void *)0);   

   


   for ( arg_i =1; arg_i < argc; ++arg_i )
   {
      nutkearn__add_prefix_filter(nk, argv[arg_i]);
   }
}


static void
nutkearn__end(nutkern_t *nut)
{
   (nut);;
}

static void
nutkearn__final(nutkern_t *nut) 
{
   if ( nut == ((void *)0) ) { return; }

   nlist__del(nut->logger_list, nut_logger__del);

   
   nlist__del(nut->prefix_list, free);
}



















































































































      




















#line 1006 "..\\include\\nut.h"


#line 17 "test_1suite.c"

int main(int argc, char *argv[]){ nutkern_t nutkearn__; nutkearn_init((&nutkearn__), argc, argv); {
} nutkearn__end((&nutkearn__)); nutkearn__final((&nutkearn__)); return 0;};


