#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>
void printFullInfo (struct passwd *userinfo, struct group *groupinfo, 
		    struct stat st, struct dirent *dent)
{
    if (dent->d_name[0] == '.') //do not show hidden files or dirs
      return;
    //printf("%-10lo ", st.st_mode);
    if (dent->d_type & DT_DIR)
        putchar('d'); else putchar('-');
    if((st.st_mode&S_IRUSR) != 0)
        putchar('r'); else putchar('-');
    if((st.st_mode&S_IWUSR) != 0)
        putchar('w'); else putchar('-');
    if((st.st_mode&S_IXUSR) != 0)
        putchar('x'); else putchar('-');
    if((st.st_mode&S_IRGRP) != 0)
        putchar('r'); else putchar('-');
    if((st.st_mode&S_IWGRP) != 0)
        putchar('w'); else putchar('-');
    if((st.st_mode&S_IXGRP) != 0)
        putchar('x'); else putchar('-');
    if((st.st_mode&S_IROTH) != 0)
        putchar('r'); else putchar('-');
    if((st.st_mode&S_IWOTH) != 0)
        putchar('w'); else putchar('-');
    if((st.st_mode&S_IXOTH) != 0)
        putchar('x'); else putchar('-');
    putchar('\t');
    printf("%4d ", st.st_nlink);
    printf("%-10s ", userinfo->pw_name); 
    printf("%-10s ", groupinfo->gr_name); 
    printf("%10lld ", st.st_size); 
    //printf("%s ", ctime(&st.st_mtime)); //time works correct, but printing
    printf("%s \n", dent->d_name);	//is not good with it. i dont know why
}
void printName (struct dirent *dent)
{
  if (dent->d_name[0] == '.') //do not show hidden files or dirs
    return;
  printf("%s ", dent->d_name);
}
int getFullInfo (char *fullPath, struct dirent *dent) 
{
  struct stat st;
  //printf("dent->d_name is %s \n",dent->d_name);
  if (stat(fullPath, &st)!=0) 
  {
   printf("%s \n","stat-error"); 
  }
  struct passwd *userinfo = getpwuid(st.st_uid);
  struct group *groupinfo = getgrgid(st.st_gid); 
  printFullInfo(userinfo, groupinfo, st, dent);    
}
bool isKey_l (int arc, char **argv) 
{
  bool key_l = false;
  int i;
  for (i=1; i<=arc-1; ++i)
  {
    if (argv[i][0] == '-' && argv[i][1] == 'l')
    {
      key_l = true;
      break;
    }
  }
  return key_l;
}
char ** getPath (int arc, char ** argv)
{
  const int n = 10;
  if (arc > n+1)
  {
    printf ("%s \n", "error");
    return NULL;
  }
  char **dir = (char **)malloc(arc*sizeof(char *));
  int i;
  for (i=0; i<n; ++i)
  {
    dir[i] = (char *)malloc(255*sizeof(char));
    dir[i][0] = '\0';
  }
  bool b = false;
  int j = 0;
  for (i=1; i<arc; ++i)
    if(!(argv[i][0] == '-' && argv[i][1] == 'l'))
    {
      dir[j++] = argv[i];
      b=true;
    }
  if (!b)
    dir[0] = ".";
  return dir;
}
int getPathCount (int arc, char **argv) 
{
  int i, count = 0;
  for (i=1; i<arc; ++i)
    if(!(argv[i][0] == '-' && argv[i][1] == 'l'))
    {
      count++;
    }
    if (count == 0)
      count++;
    return count;
}
void ls (DIR *directory) 
{
  struct dirent *dent;
  while ((dent=readdir(directory))!=NULL) 
	printName(dent);
  printf("\n");
}
void ls_l (DIR *directory, char *path) 
{
  struct dirent *dent;
  while ((dent=readdir(directory))!=NULL) 
  {
    char *fullPath = malloc( (strlen(dent->d_name) +
    strlen(path) + 2)*sizeof(char) );
    fullPath[0]='\0';
    strcat(fullPath, path);
    if (fullPath[strlen(fullPath)-1]!='/')
      strcat(fullPath, "/");
    strcat(fullPath, dent->d_name);
    getFullInfo(fullPath, dent);
  }
}

int main (int arc, char **argv) 
{
  bool key_l = isKey_l(arc, argv);
  char **path = getPath(arc, argv);
  int pathCount = getPathCount(arc, argv);
  bool isFewPathes = false;
  if (pathCount > 1)
    isFewPathes = true;
  int i;
  for (i=0; i<pathCount; ++i)
  {
    //printf("key_l is %d, dir is \"%s\" \n", key_l, path[i]);
    DIR *directory = opendir(path[i]);
    if (directory == NULL)
    {
     printf("\"%s\" is file or does not exist \n",path[i]); 
     continue;
    }
    if (isFewPathes)
      printf("%s:\n",path[i]);
    if (key_l == false) 
      ls(directory);
    else 
      ls_l(directory, path[i]);
    if (isFewPathes && i!=pathCount-1)
      printf("%s", "\n");
    closedir(directory);
  }
  return 0;
}