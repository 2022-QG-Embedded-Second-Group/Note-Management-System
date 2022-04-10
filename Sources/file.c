#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "file.h"
//#include <Windows.h>

//去除第一个字符和最后一个字符
//返回0  表失败
//返回1  表成功
int removechar(char* str, char ch)
{
    int num = 0;
    char* temp = str;
    while (*temp)
    {
        num++;
        temp++;
    }
    int i;
    for (i = 0; i < num -1; i++)
    {
        str[i] = str[i + 1];
    }
    if (str[i-1] != ch)
        return 0;
    str[i-1] = '\0';
    return 1;
}


void ShowInfo()
{
    //printf("  ******************************************************\n\n");
    //printf("  *                欢迎使用文件模拟系统                 *\n \n");
    //printf("  ******************************************************\n\n");
    printf("  该系统目前支持如下功能：\n");
    printf("  1. ls : 显示当前目录下所有的笔记文件\n");
    printf("  2. ls -a : 按照树状结构显示所有的笔记文件夹以及笔记文件\n");
    printf("  3. ls <文件夹路径> : 显示命令指定文件下所有的内容\n");
    printf("  4. ls <笔记文件夹路径> grep “搜索内容 : 显示命令指定文件下所有的带有搜索内容的文件夹名及文件名”\n");

    printf("  5. cd .. : 切换到当前路径的上级文件夹\n");
    printf("  6. cd <笔记文件夹路径> : 将路径切换为命令中输入的文件夹路径\n");

    printf("  7. mv <笔记文件名> <笔记文件夹目录> : 将笔记文件移动到指定的文件夹目录下\n");
    printf("  8. mv <笔记原文件名> <笔记目标文件名> : 将笔记文件进行重命名，从原文件名改为目标文件名\n");
    printf("  9. mv -r <被移动的文件夹> <目标文件夹>: 将指定的笔记文件夹移动到目标文件夹目录下\n");

    printf("  10. rm <笔记文件名> : 对笔记文件进行删除\n");
    printf("  11. rm -r <笔记文件夹名称> : 删除指定文件夹以及其内部所有内容\n");

    printf("  12. mkdir <文件名> : 在当前路径下新建文件\n");
    printf("  13. mkdir -r <文件夹名> : 在当前路径下新建文件夹\n");

    printf("  14. sort <笔记文件夹名> : 对指定文件夹内的笔记文件按文件名首字母进行排序\n");

    printf("  15. tag <笔记文件名/笔记文件夹名> : 显示指定笔记/文件夹的标签\n");
    printf("  16. tag -add <笔记文件名/笔记文件夹名> “标签内容” : 为指定笔记/笔记文件夹增加标签\n");
    printf("  17. tag -del <笔记文件名/笔记文件夹名> “标签内容” : 删除指定笔记/文件夹的指定标签\n");
    printf("  18. tag -s “标签内容” : 在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名\n");
    printf("  19. tag -sa “标签内容” : 对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径\n");
    printf("  20. help 显示帮助文档\n");
    printf("  21. cls  清屏\n");
    printf("  22. exit 返回\n");
    printf("  \n");
    //printf("  请输入指令: ");
    //system("pause");
}

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char* getDateTime()
{
    static char cur_time[20]; // 返回局部变量，故加static
    time_t t;
    struct tm* lt;
    time(&t);
    lt = localtime(&t); //转为时间结构
    sprintf(cur_time, "%04d/%02d/%02d %02d:%02d:%02d", lt->tm_year + 1900, (lt->tm_mon+1), lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    return cur_time;
}

/**
 * @brief 将保存树数据的数组保存到文件中去
 *
 * @param file 储存数据的数组
 * @param n 数组的数量
 * @param filename 用户文件名称
 */
void SaveFile(FileType file[], int n, char* filename)
{
    int i;
    FILE* fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("数据文件无法打开");
        return;
    }
    for (i = 0; i < n; i++)
    {
        fwrite(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief 从文件中读取保存树数据的数组
 *
 * @param file
 * @param n 数字（表示数组的长度）的地址值
 * @param filename 用户文件名称
 */
void ReadFile(FileType file[], int* n, char* filename)
{
    FILE* fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        *n = 0;
        printf("  ");
        return;
    }
    fseek(fp, 0, SEEK_END);         // 重定位流上的文件指针,把fp指针退回到离文件结尾0字节处
    long length = ftell(fp);        // 调用函数ftell()获得当前位置相对于文件首的位移，该位移值等于文件所含字节数
    rewind(fp);                     // 将位置指针重新指向文件的开头
    *n = length / sizeof(FileType); // 得到一共有多少个结构数据
    for (int i = 0; i < *n; i++)
    {
        fread(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief Create a File Tree object
 *
 * @param root 根节点传入"Root"
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char* root, FileType file[], int n)
{
    FileTree bt = (FileTree)malloc(sizeof(FileNode));
    if (bt == NULL)
    {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    FileTree father = bt;
    father->fchild = NULL;
    father->father = NULL;
    father->sbi = NULL;
    strcpy(father->name, root);
    //char *fathername = root;
    int i;
    LinkStack s;
    initLStack(&s);//初始化
    int ntemp = n;
    while (n)
    {
        for (i = 0; i < ntemp; i++)
        {
            //实现层次遍历
            if (strcmp(file[i].fathername, father->name) == 0)//找到子节点
            {
                FileTree pchild = (FileTree)malloc(sizeof(FileNode));
                strcpy(pchild->name, file[i].name);//名字赋值
                pchild->father = father;
                pchild->fchild = NULL;
                pchild->sbi = NULL;
                if (father->fchild == NULL)//不存在第一个节点
                {
                    father->fchild = pchild;
                    pchild->father = father;
                }
                else//已存在子节点
                {
                    FileTree ptemp1 = father->fchild;//指向第一个子节点
                    FileTree ptemp2 = NULL;
                    while (ptemp1)
                    {
                        ptemp2 = ptemp1;//记住上一个节点的位置
                        ptemp1 = ptemp1->sbi;
                    }
                    ptemp2->sbi = pchild;//前一个兄弟节点指向当前的节点
                }
                pushLStack(&s, pchild);//入栈
                n--;
            }
        }
        if (isEmptyLStack(&s) == 0)
        {
            popLStack(&s, &father);//出栈，作为一层遍历的父节点
            //strcpy(fathername, father->name);
        }
        if (n == 1)//根节点不用遍历
            break;
    }
    return bt;
}
//FileTree CreateFileTree(char* root, FileType file[], int n)
//{
//    FileTree bt = (FileTree)malloc(sizeof(FileNode));
//    strcpy(bt->name, root);
//    bt->fchild = bt->sbi = bt->father = NULL;
//    int i, j;
//    for (i = 0; i < n && strcmp(file[i].fathername, root) != 0; i++)
//    {
//        ;
//    }
//    if (i < n) // 若找到第一个父节点名称为root的
//    {
//        FileTree p = (FileTree)malloc(sizeof(FileNode)); // 创建一个临时指针
//        p->fchild = p->sbi = p->father = NULL;
//        strcpy(p->name, file[i].name);
//        bt->fchild = p;
//
//        for (j = i; j < n; j++)
//        {
//            if (strcmp(file[j].fathername, root) == 0)
//            {
//                p = CreateFileTree(file[j].name, file, n); //! 递归
//                p = p->sbi;
//            }
//        }
//    }
//    return bt;
//}

FileType Findfile(FileType file[], int n, char *name)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].name, name) == 0)
        {
            return file[i];
        }
    }
}

/**
 * @brief ls: 显示当前目录下所有的笔记文件和文件夹
 *
 * @param pNode
 */
void ls(FileTree pNode, FileType file[], int n)
{
    FileTree p = pNode->fchild;
    if (p == NULL)
    {
        printf("当前目录下没有文件(夹)\n");
    }
    for (; p; p = p->sbi)
    {
        printf("%-10s\t", p->name);
        FileType pfile = Findfile(file, n, p->name);
        printf("%-20s\t", pfile.datetime);
        if (pfile.flag == 1)
            printf("文件\n");
        else
            printf("文件夹\n");
    }
}

//! 树状结构显示
/**
 * @brief ls -a: 按照树状结构显示所有的笔记文件夹以及笔记文件
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level, char *rootname)
{
    if (strcmp(pNode->name, rootname) == 0) // 首节点定义为的名称为Root
    {
        printf("%s\n", pNode->name);
    }
    else
    {

        for (int i = 0; i < level; i++)
        {
            printf("|    ");
        }
        printf("|---<%s>\n", pNode->name);
    }
    if (pNode->fchild) // 存在子节点
    {
        ls_a(pNode->fchild, level + 1, ""); // 递归调用
    }
    if (pNode->sbi)
    {
        ls_a(pNode->sbi, level, "");
    }
    return;
}

/**
 * @brief 模糊搜索判断是否符合筛选条件
 *
 * @param key 关键字
 * @param str 被查找的字符串
 * @return int 1为符合,0不符合
 */
int result_mohu(const char* key, char* str)
{
    typedef struct
    {
        char son[11];
    } Element;

    int i, j, k = 0, l = 0, m = 0;

    // f=1为符合筛选条件
    int f = 0;

    // N1为str的长度 N2为str连续子串的个数
    int N1 = 0, N2 = 0;
    N1 = strlen(str);
    /*计算连续子串的个数*/
    for (i = 1; i <= N1; i++)
        N2 += i;

    /*计算连续子串的个数*/
    // i控制子字符串的长度
    // j控制赋值
    // k控制新的线性结构b的下标
    // l控制子数组的首项在原数组中的位置
    // m控制即将用作赋值的str的下标
    Element* b = malloc(sizeof(Element) * N2);
    for (i = 1; i <= N1; i++)
    {
        l = 0;
        /*while循环内为给一个子字符串数组赋值*/
        while (1)
        {
            m = l;
            for (j = 0; j < i; j++)
            {
                b[k].son[j] = str[m];
                m++;
            }
            l++;
            k++;
            if (m == N1)
                break;
        }
    }

    //挨个比对
    for (i = 0; i < N2; i++)
        if (strcmp(key, b[i].son) == 0)
        {
            f = 1;
            break;
        }
    free(b);
    return f;
}

void PostOrderTraverse(FileTree pNode, FileType file[], int* n)
{
    if (pNode)
    {
        PostOrderTraverse(pNode->fchild, file, n);
        PostOrderTraverse(pNode->sbi, file, n);
        DeleteNode(pNode, file, n);
    }
    return; //如果结点为空，返回上一层
}

/**
 * @brief 通过file[i].name与pNode->name匹配
 * 用先序遍历递归查找匹配的节点
 *
 * @param pNode
 * @param filename
 * @param b 将要获取的目标节点
 */
void PreOrderFindNode_Path(FileTree pNode, char* filename, FileTree* b)
{
    if (pNode)
    {
        if (strcmp(pNode->name, filename) == 0)
        {
            *b = pNode;
            return;
        }
        PreOrderFindNode_Path(pNode->fchild, filename, b);
        PreOrderFindNode_Path(pNode->sbi, filename, b);
        return;
    }
}

//寻找节点
//返回找到的节点
FileTree Searchpath(FileTree bt, char* name)
{
    LinkStack s;
    initLStack(&s);
    FileTree p = bt, ptemp = NULL;
    do {
        coti:
        while (p)
        {
            if (p->fchild != NULL)
                if (p->sbi != NULL)
                    pushLStack(&s, p);//入栈
            if (strcmp(p->name, name) == 0)
            {
                return p;
            }
            ptemp = p;
            p = p->fchild;
        }
        p = ptemp;
        while (p)
        {
            if (p->fchild != NULL)
                pushLStack(&s, p);//入栈
            if (strcmp(p->name, name) == 0)
            {
                return p;
            }
            p = p->sbi;
        }
        if (!isEmptyLStack(&s))
        {
            popLStack(&s, &p);//出栈
            goto coti;
        }
    } while (!isEmptyLStack(&s));
    printf("错误\n");
}

/**
 * @brief ls <笔记文件夹路径> grep “搜索内容”：显示命令指定文件下所有的带
有搜索内容的文件夹名及文件名
 *
 * @param dirpath 笔记文件夹路径
 * @param SearchContent 搜索内容
 * @param file 数组
 * @param root 需要传入Root节点
 * @param n 数组长度
 */
void ls_grep(char* dirpath, char* SearchContent, FileType file[], FileTree root, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // 绝对路径匹配，通过路径找到file[i]
        {
            FileTree b = Searchpath(root, file[i].name);
            FileTree p = b->fchild;
            for (; p; p = p->sbi)
            {
                if (strstr(p->name, SearchContent) != NULL) // 模糊搜索判断是否符合筛选条件
                {
                    printf("%s ", p->name);
                }
            }
            printf("\n");
            return;
        }
    }
    printf("未找到该路径\n");
}


 /**
  * @brief ls <笔记文件夹路径>：显示命令指定文件下所有的内容(子笔记文件夹和笔记文件)
  * //!目前只支持绝对路径
  *
  * @param dirpath 输入的路径名称
  * @param file 数组
  * @param pNode 需要传入Root节点
  * @param n 数组长度
  */
void ls_dir(char* dirpath, FileType file[], FileTree pNode, int n)
{
    int i;
    for ( i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // 绝对路径匹配，通过路径找到file[i]
        {
            FileTree b;
            PreOrderFindNode_Path(pNode, file[i].name, &b); // 通过file[i]查找匹配的树节点
            ls(b, file, n);                                         // 调用ls()函数，打印路径下的所有内容
            return;
        }
    }
    if (i == n)
        printf("未能找到该路径");
}


/**
 * @brief cd ..：将路径切换为当前目录的父目录.若是根目录则则不进行切换
 * 现在操作函数里判断再进行调用，记得输出当前节点路径哟
 *
 * @param pNode 当前节点
 * @return FileTree
 */
FileTree cd(FileTree pNode, UserList user)
{
    if (strcmp(pNode->name, user->data->userid) == 0) // 如果传入的节点是根节点，不进行切换
    {
        printf("切换失败\n");
        return pNode; // 返回根节点
    }
    printf("切换成功\n");
    return pNode->father;
}


/**
 * @brief cd <笔记文件夹路径>：将路径切换为命令中输入的文件夹路径
 * //!目前只支持绝对路径
 *
 * @param dirpath 输入的路径名称
 * @param file 数组
 * @param pNode 先节点
 * @param root 需要传入Root节点
 * @param n 数组长度
 * @return FileTree 返回节点
 */
FileTree cd_dir(char* dirpath, FileType file[], FileTree pNode, FileTree root, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // 绝对路径匹配，通过路径找到file[i]
        {
            FileTree b;
            PreOrderFindNode_Path(root, file[i].name, &b); // 通过file[i]查找匹配的树节点
            return b;
        }
    }  
    printf("未能找到此路径\n");
    return pNode;
}

 /**
  * @brief rm <笔记文件名>：对笔记文件进行删除
  *
  * @param pNode
  * @param filename
  * @param file 数组
  * @param n 数组长度
  */
void rm(FileTree pNode, char* filename, FileType file[], int* n, UserList user)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (strcmp(file[i].fathername, pNode->name) != 0)
            {
                printf("此文件不在当前目录下\n");
                return;
            }

            if (file[i].flag == 0)
            {
                printf("这是一个文件夹,若要删除,请输入“rm -r <要删除的笔记文件夹名称>”\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // 如果是亲代的第一个子节点
            {
                pNode->fchild = p->sbi;
                free(p);
            }
            else // 如果是兄弟节点，“嫁接”
            {
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
                    }
                }
            }

            for (int j = i; j < *n; j++) // 后面的数据前移
            {
                file[j] = file[j + 1];
            }

            (*n)--;
            SaveFile(file, *n, user->data->userfilename);
            printf("删除成功\n");
            return;
        }
    }
    printf("未能找到次文件\n");
    return;
}

/**
 * @brief rm -r <笔记文件夹名称>：删除制定文件以及其内部所有内容
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void rm_r(FileTree pNode, char* filename, FileType file[], int* n, UserList user)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (strcmp(file[i].fathername, pNode->name) != 0)
            {
                printf("此文件不在当前目录下\n");
                return;
            }

            if (file[i].flag == 1)
            {
                printf("这是一个文件,若要删除,请输入“rm <要删除的笔记文件名>”\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // 如果是亲代的第一个子节点
            {
                pNode->fchild = p->sbi;
                PostOrderTraverse(p, file, n);
                free(p);
            }
            else // 如果是兄弟节点，“嫁接”
            {
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        PostOrderTraverse(q, file, n);
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
                    }
                }
                if (strcmp(q->name, filename) == 0)
                {
                    p->sbi = q->sbi;
                    PostOrderTraverse(q, file, n);
                    free(q);
                }
            }
            SaveFile(file, *n, user->data->userfilename);
            printf("删除成功\n");
            return;
        }
    }
    printf("未能找到次文件\n");
    return;
}
void DeleteNode(FileTree pNode, FileType file[], int* n)
{

    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, pNode->name) == 0)
        {
            for (int j = i; j < *n; j++) // 后面的数据前移
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
}

/**
 * @brief mkdir<笔记文件名>: 在当前文件夹pNode下新建文件
 *
 * @param pNode
 * @param filename
 * @param file 数组
 * @param n 数组长度
 */
void mkdir(FileTree *pNode, char* filename, FileType file[], int* n, UserList user)
{
    int locate = 0;
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("此文件（夹）名称已存在\n");
            return;
        }
        if (strcmp(file[i].name, (*pNode)->name) == 0)
        {
            locate = i;
        }

    }
    if (strcmp(file[locate].name, (*pNode)->name) == 0)
    {
        if (file[locate].flag == 1)
        {
            printf("这是一个文件，无法在次目录下创建文件\n");
            return;
        }
        strcpy(file[*n].fathername, (*pNode)->name);
        strcpy(file[*n].name, filename);
        file[*n].tagnum = 0;//初始化数量
        //生成当前路径
        char tmp[PATHMAXN];
        strcpy(tmp, file[locate].path);
        strcat(tmp, "\\");
        strcat(tmp, filename);
        strcpy(file[*n].path, tmp);

        file[*n].flag = 1; // 1表示这是一个文件
        strcpy(file[*n].datetime, getDateTime());
        FileTree p = (*pNode)->fchild, pttemp = (*pNode);
        FileTree ptemp = (FileTree)malloc(sizeof(FileNode));
        strcpy(ptemp->name, filename);
        ptemp->father = (*pNode);
        ptemp->fchild = NULL;
        ptemp->sbi = NULL;

        if (p == NULL)
        {
            pttemp->fchild = ptemp;
        }
        else
        {
            while (p)
            {
                pttemp = p;
                p = p->sbi;
            }
            pttemp->sbi = ptemp;
        }

        (*n)++;
        SaveFile(file, *n, user->data->userfilename);
        printf("添加成功\n");
    }

}

/**
 * @brief mkdir -r<笔记文件夹名>: 新建文件夹
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void mkdir_r(FileTree *pNode, char* filename, FileType file[], int* n, UserList user)
{
    int locate = 0;
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("此文件（夹）名称已存在\n");
            return;
        }
        if (strcmp(file[i].name, (*pNode)->name) == 0)
        {
            locate = i;
        }

    }
    if (strcmp(file[locate].name, (*pNode)->name) == 0)
    {
        if (file[locate].flag == 1)
        {
            printf("这是一个文件，无法在次目录下创建文件\n");
            return;
        }
        strcpy(file[*n].fathername, (*pNode)->name);
        strcpy(file[*n].name, filename);
        file[*n].tagnum = 0;//初始化数量
        //生成当前路径
        char tmp[PATHMAXN];
        strcpy(tmp, file[locate].path);
        strcat(tmp, "\\");
        strcat(tmp, filename);
        strcpy(file[*n].path, tmp);

        file[*n].flag = 0; // 0表示这是一个文件夹
        strcpy(file[*n].datetime, getDateTime());
        FileTree p = (*pNode)->fchild, pttemp = (*pNode);
        FileTree ptemp = (FileTree)malloc(sizeof(FileNode));
        strcpy(ptemp->name, filename);
        ptemp->father = (*pNode);
        ptemp->fchild = NULL;
        ptemp->sbi = NULL;

        if (p == NULL)
        {
            pttemp->fchild = ptemp;
        }
        else
        {
            while (p)
            {
                pttemp = p;
                p = p->sbi;
            }
            pttemp->sbi = ptemp;
        }

        (*n)++;
        SaveFile(file, *n, user->data->userfilename);
        printf("添加成功\n");
    }
}

/**
 * @brief tag <笔记文件名/笔记文件夹名> 显示当前目录下的指定笔记/文件夹的标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件 
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag(FileNode* pNode, char* filename, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//表示在该目录下
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    printf("标签%d: %s\n", j + 1, file[i].tag[j]);//打印标签
                }
                if (0 == file[i].tagnum)
                    printf("暂无标签\n");
                break;
            }
        }
    }
    if (i == n)//没有找到该文件(夹)
    {
        printf("该目录下没有指定的文件(夹)\n");
    }
}

/**
* @brief tag-add <笔记文件名/笔记文件夹名> 在当前目录下指定的笔记/笔记文件夹增加标签
*
* @param pNode,当前目录的节点
* @param filename 指定的文件夹或文件
* @param tagname 标签的名字
* @param file  该用户的数组
* @param n    数组的长度
*/
void tag_add(FileNode* pNode, char* filename, char* tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//表示在该目录下
            {
                if (file[i].tagnum > 2)//表示超过当前最大的标签数量
                {
                    printf("超过最大的标签数\n");
                }
                else
                {
                    for (j = 0; j < file[i].tagnum; j++)//寻找是否有相同的标签名字
                    {
                        if (strcmp(file[i].tag[j], tagname) == 0)
                        {
                            printf("添加失败, 该标签已存在\n");
                            break;
                        }
                    }
                    if (j == file[i].tagnum)//没有找到相同的标签名字
                    {
                        strcpy(file[i].tag[j], tagname);
                        file[i].tagnum++;
                        printf("添加成功\n");
                    }
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("该目录下没有找到指定的文件(夹)\n");
    }
}

/**
* @brief tag-add <笔记文件名/笔记文件夹名>> “标签内容”: 在当前目录下指定的笔记/笔记文件夹删除指定的标签
*
* @param pNode,当前目录的节点
* @param filename 指定的文件夹或文件
* @param tagname 标签的名字
* @param file  该用户的数组
* @param n    数组的长度
*/
void tag_del(FileNode* pNode, char* filename, char* tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//表示在该目录下
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    if (strcmp(file[i].tag[j], tagname) == 0)//找到该标签
                    {
                        file[i].tagnum--;//标签数量-1
                        memset(file[i].tag[j], 0, sizeof(file[i].tag[j]));//清空内容
                        printf("删除成功\n");
                    }
                }
                if (j == file[i].tagnum)
                {
                    printf("没有找到该标签\n");
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("该目录下没有找到指定的文件(夹)\n");
    }
}

/**
* @brief tag-s “标签内容”： 根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名
* @param pNode,当前目录的节点
* @param tagname 标签的名字
* @param file  该用户的数组
* @param n    数组的长度
*/
void tag_s(FileNode* pNode, char* tagname, FileType file[], int n)
{
    int i, j;
    int flag = 1;
    for (i = 0; i < n; i++) // 找到当前路径下的文件(夹)
    {
        if (strcmp(file[i].fathername, pNode->name) == 0)//在当前目录下的
        {
            for (j = 0; j < file[i].tagnum; j++)
            {
                if (strcmp(file[i].tag[j], tagname) == 0)//找到相同的标签
                {
                    printf("<%s>\n", file[i].name);//打印文件(夹)名字
                    flag = 0;
                }
            }
        }
    }
    if (flag)
        printf("该目录下不存在该标签\n");
}

/**
* @brief tag-sa “标签内容”： 根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径
* @param tagname 标签的名字
* @param file  该用户的数组
* @param n    数组的长度
*/
void tag_sa(char* tagname, FileType file[], int n)
{
    int i, j;
    int flag = 1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < file[i].tagnum; j++)
        {
            if (strcmp(tagname, file[i].tag[j]) == 0)//找到相同名称的标签
            {
                printf("%-20s\t%-20s\n",file[i].name, file[i].path);//打印文件名和文件路径
                flag = 0;
            }
        }
    }
    if (flag)
        printf("找不到该标签\n");
}

/**
 * @brief sort <笔记文件夹名>
 * 对指定文件夹内的笔记文件按文件名首字母进行排序；
 * 少了一步重新建树，可以在调用这个函数后加上
 *
 * @param root 传入根节点——user->data->userid
 * @param filename 输入的路径名
 * @param file 数组
 * @param n 数组长度
 * @param user UserLiset
 */
void sort(FileTree root, char* filename, FileType file[], int n, UserList user)
{
    int i, count = 0;
    for (i = 0; i < n; i++) // 判断输入是否为文件
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("这是一个文件,无法进行排序操作\n");
                return;
            }
        }
    }
    FileType tmparr[FILEMAXN], max; // 暂时存放
    for (i = 0; i < n; i++)
    {
        if (strcmp(file[i].fathername, filename) == 0) // 如果是filename文件夹下的文件
        {
            tmparr[count++] = file[i];
        }
    }
    for (i = 0; i < count - 1; i++) // 对数组tmparr进行冒泡排序
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (tmparr[j].name[0] > tmparr[j + 1].name[0])
            {
                max = tmparr[j];
                tmparr[j] = tmparr[j + 1];
                tmparr[j + 1] = max;
            }
        }
    }
    for (count = 0, i = 0; i < n; i++) // 将排序后的暂时数组存回原始数组里
    {
        if (strcmp(file[i].fathername, filename) == 0)
        {
            file[i] = tmparr[count++];
        }
    }
    SaveFile(file, n, user->data->userfilename);
    printf("排序成功\n");
    return;
}

//判断某一个字符出现的字数
int countnum(char* str, char ch)
{
    char* temp = str;
    int num = 0;
    int count = 0;
    while (*temp)
    {
        num++;
        temp++;
    }
    for (int i = 0; i < num; i++)
    {
        if (str[i] == ch)
            count++;
    }
    return count;
}

//寻找节点
//返回找到的节点
FileTree SearchpNode(FileTree bt, FileTree pNode)
{
    LinkStack s;
    initLStack(&s);
    FileTree p = bt, ptemp = NULL;
    do{
        con:
        while (p)
        {
            if (p->fchild != NULL)
                if (p->sbi != NULL)
                    pushLStack(&s, p);//入栈
            if (strcmp(p->name, pNode->name) == 0)
            {
                return p;
            }
            ptemp = p;
            p = p->fchild;
        }
        p = ptemp;
        while (p)
        {
            if (p->fchild != NULL)
                pushLStack(&s, p);//入栈
            if (strcmp(p->name, pNode->name) == 0)
            {
                return p;
            }
            p = p->sbi;
        }
        if (!isEmptyLStack(&s))
        {
            popLStack(&s, &p);//出栈
            goto con;
        }
    } while (!isEmptyLStack(&s));
    printf("错误\n");
}

/*获取字符串字符数*/
//返回字符数
int getstringnum(char* str)
{
    int num = 0;
    char* temp = str;
    while (*temp)
    {
        num++;
        temp++;
    }
    return num;
}

/*截取指定数量的字符串*/
char* getappointstr(char* str, int num)
{
    str[num] = '\0';
    return str;
}


/**
* @brief mv -r <被移动的文件夹> <目标文件夹>：将指定的笔记文件夹移动到目标文件夹目录下。
* @param file        该用户的数组
* @param n           数组长度
* @param movefile    被移动文件夹名字
* @param destination 目标文件夹名字
* @param bt          用户的树
* @param user        用户节点
*/
void mv_r(FileType file[], int n, char* movefile, char* destination, FileTree* bt, UserNode* user, FileTree* pNode)
{
    int i;
    int movefilelocate = 0, destinationlocate = 0;
    //char movefathername[100], movename[100], destinationName[100];
    int movefilelevel, destinationlevel = 0;//判断文件级别
    for (i = 0; i < n; i++)
    {
        if (strcmp(file[i].name, movefile) == 0)//寻找被移动文件夹名字
        {
            if (file[i].flag == 1)//若要移动的是文件
            {
                printf("要移动的是文件, 不符合该操作\n");
                return;
            }
            else
            {
                if (strcmp(file[i].fathername, destination) == 0)
                {
                    printf("文件已经在该目录下");
                    return;
                }
                //strcpy(movefathername, file[i].fathername);//记住上级目录名称 
                //strcpy(movename, file[i].name);//
                //strcpy(file[i].fathername, destination);
                movefilelocate = i;//记住被移动文件位置

                //break;
            }
        }
        if (strcmp(destination, file[i].name) == 0)//找到目标文件夹
        {
            if (file[i].flag == 1)//文件
            {
                printf("该目标不是文件夹\n");
                return;
            }
            //strcpy(destinationName, destination);
            destinationlocate = i;//记住目标文件夹位置
        }
    }
    destinationlevel = countnum(file[destinationlocate].path, '\\');
    movefilelevel = countnum(file[movefilelocate].path, '\\');
    int  movefilenum = getstringnum(file[movefilelocate].path);
    int  destinationnum = getstringnum(file[destinationlocate].path);
    if (movefilelevel < destinationlevel)//移动文件夹的级别小于目标文件夹
    {
        if (destinationnum > movefilenum)
        {
            char* pathtemp = getappointstr(file[destinationlocate].path, movefilenum);
            if (strcmp(pathtemp, file[movefilelocate].path) == 0)
            {
                printf("移动失败\n");
                return;
            }
        }
    }
    strcpy(file[movefilelocate].fathername, destination);
    //生成新路径
    char path[PATHMAXN];
    strcpy(path, file[destinationlocate].path);
    strcat(path, "\\");
    strcat(path, file[movefilelocate].name);
    strcpy(file[movefilelocate].path, path);
    //文件保存
    SaveFile(file, n, user->data->userfilename);
    (*bt) = CreateFileTree(user->data->userid, file, n);
    (*pNode) = SearchpNode(*bt, *pNode);
    //FileTree p = bt, ptemp = NULL, pfather = NULL, pchild = NULL, pre = NULL, movefather = NULL;
    //LinkStack s;
    //initLStack(&s);
    /*
    while (n)//遍历树
    {
        while (p)
        {
            if (p->fchild != NULL)
                if (p->sbi != NULL)
                    pushLStack(&s, p);//入栈
            if (strcmp(p->name, destination) == 0)//找到目标文件夹
                pfather = p;
            if (strcmp(p->name, movefile) == 0)//找到被移动文件夹
                pchild = p;
            if (p->sbi)
            {
                if (strcmp(p->sbi->name, movefile) == 0)//找到前节点
                    pre = p;
            }
            if (p->fchild)
            {
                if (strcmp(p->fchild->name, movefile) == 0)//找到父节点
                    movefather = p;
            }
            ptemp = p;
            p = p->fchild;
            n--;
        }
        p = ptemp;
        while (p)
        {
            if (p->fchild != NULL)
                pushLStack(&s, p);//入栈
            if (strcmp(p->name, destination) == 0)//找到目标文件夹
                pfather = p;
            if (strcmp(p->name, movefile) == 0)//找到被移动文件夹
                pchild = p;
            if (p->sbi)
            {
                if (strcmp(p->sbi->name, movefile) == 0)//找到前节点
                    pre = p;
            }
            if (p->fchild)
            {
                if (strcmp(p->fchild->name, movefile) == 0)//找到父节点
                    movefather = p;
            }
            p = p->sbi;
            n--;
        }
        if (!isEmptyLStack(&s))
            popLStack(&s, &p);//出栈
    }

    if (pre != NULL)//移动文件夹有前节点
    {
        pre->sbi = pre->sbi->sbi;
    }
    else//没有前节点
    {
        movefather->fchild = pchild->sbi;
    }
    FileTree pt = pfather->fchild;
    while (pt)
    {
        pt = pt->sbi;
    }
    pt = pchild;
    pchild->father = pfather;
    pchild->fchild = NULL;
    pchild->sbi = NULL;
    */
    printf("移动成功\n");
}

/**
* @brief mv <笔记文件名> <笔记文件夹目录>：将笔记文件移动到指定的文件夹目录下。
*        mv <笔记原文件名> <笔记目标文件名>：将笔记文件进行重命名，从原文件名改为目标文件名。
* @param file        该用户的数组
* @param n           数组长度
* @param pfile       文件夹名字
* @param destination 目标文件夹名字
* @param bt          用户的树
* @param user        用户节点
*/
void mv(FileType file[], int n, char* pfile, char* destination, FileTree* bt, UserNode* user, FileTree* pNode)
{
    int i;
    int pfilelocate = -1, destionationlocate = -1;
    int renameflag = 1;//1表示重命名，0表示移动
    for (i = 0; i < n; i++)//判断是否移动还是重命名
    {
        if (strcmp(destination, file[i].name) == 0)//找到相同名字，表移动操作
        {
            if (file[i].flag == 1) //如果目标名字是文件
            {
                printf("该目标是文件，无法移动到该目录下\n");
                return;
            }
            destionationlocate = i;//记住destionation位置
            renameflag = 0;
        }
        if (strcmp(pfile, file[i].name) == 0)//找到文件
        {
            if (file[i].flag == 0)//如果是文件夹
            {
                printf("你要操作的是文件夹, 不符合该操作\n");
                return;
            }
            else//文件
            {
                pfilelocate = i;//记住位置
            }
        }
    }
    if (pfilelocate == -1)//没有该文件
    {
        printf("找不到此文件\n");
        return;
    }
    if (renameflag == 1)//重命名
    {
        strcpy(file[pfilelocate].name, destination);//重命名
    }
    else//移动文件
    {
        //改变父节点
        strcpy(file[pfilelocate].fathername, file[destionationlocate].name);
        //重新生成路径
        char path[PATHMAXN];
        strcpy(path, file[destionationlocate].path);
        strcat(path, "\\");
        strcat(path, file[pfilelocate].name);
        strcpy(file[pfilelocate].path, path);
    }
    //文件保存
    SaveFile(file, n, user->data->userfilename);
    (*bt) = CreateFileTree(user->data->userid, file, n);//重新建树
    (*pNode) = SearchpNode(*bt, *pNode);
    /*
    //LinkStack s;
    //initLStack(&s);
    //FileTree p = bt, ptemp = NULL, pmove = NULL, pdestination = NULL, pre = NULL;
    //while (n)//遍历树
    //{
    //    while (p)
    //    {
    //        if (p->fchild != NULL)
    //            if (p->sbi != NULL)
    //                pushLStack(&s, p);//入栈
    //        if (strcmp(p->name, pfile) == 0)//找到该文件
    //        {
    //            if (renameflag == 1)//重命名
    //            {
    //                strcpy(p->name, destination);
    //                //文件更新
    //                SaveFile(file, n, user->data->userfilename);
    //                return;
    //             }
    //            pmove = p;//记住要移动的文件的节点位置
    //        }
    //        if (strcmp(p->name, destination) == 0)//找到目标文件夹名
    //        {
    //            pdestination = p;//记住该节点位置
    //        }
    //        if (p->sbi)
    //        {
    //            if (strcmp(p->sbi->name, pfile) == 0)//找到兄弟节点
    //                pre = p;//记住前一个兄弟节点
    //        }
    //        ptemp = p;
    //        p = p->fchild;
    //        n--;
    //    }
    //    p = ptemp;
    //    while (p)
    //    {
    //        if (strcmp(p->name, pfile) == 0)//找到该文件
    //        {
    //            if (renameflag == 1)//重命名
    //            {
    //                strcpy(p->name, destination);
    //                SaveFile(file, n, user->data->userfilename);
    //                return;
    //            }
    //            pmove = p;//记住要移动的文件的节点位置
    //        }
    //        if (strcmp(p->name, destination) == 0)//找到目标文件夹名
    //            pdestination = p;//记住目标节点位置
    //        if (p->sbi)
    //        {
    //            if (strcmp(p->sbi->name, pfile) == 0)//找到兄弟节点
    //                pre = p;//记住前一个兄弟节点
    //        }
    //        p = p->sbi;
    //        n--;
    //    } 
    //    if (!isEmptyLStack(&s))
    //        popLStack(&s, &p);//出栈
    //}
    */
    /*
    //if (pre == NULL)//移动的文件是firstchild节点
    //{
    //    pmove->father->fchild = pmove->sbi;
    //}
    //else //移动的文件不是firstchild
    //{
    //    pre->sbi = pre->sbi->sbi;
    //}
    //FileTree treetmp = pdestination->fchild;
    //while (treetmp)
    //{
    //    treetmp = treetmp->sbi;
    //}
    //treetmp = pmove;
    //pmove->father = pdestination;
    //pmove->fchild = NULL;
    //pmove->sbi = NULL;
    */
}

//初始化栈
Status initLStack(LinkStack* s)
{
    s->top = NULL;//指向空指针
    s->count = 0;//初始化数值
    return SUCCESS;
}

//判断栈是否为空
//返回0 表栈不为空
//返回1 表栈为空
Status isEmptyLStack(LinkStack* s)
{
    if (s->count)  //栈不为空
        return 0;
    else          //栈为空
        return 1;
}

//得到栈顶元素
Status getTopLStack(LinkStack* s, ElemType* e)
{
    if (isEmptyLStack(s))  //栈为空
    {
        return ERROR;
    }
    *e = s->top->data;  //将数据传给e
    return SUCCESS;
}


//清空栈
Status clearLStack(LinkStack* s)
{
    system("cls");
    LinkStackPtr p, q;
    p = s->top;  //指向栈顶
    while (p)
    {
        q = p->next; //指向下一个结点
        free(p);
        p = q;
    }
    s->top = NULL;  //指向空指针
    s->count = 0;   //清空计数
    return SUCCESS;
}

//销毁栈
Status destroyLStack(LinkStack* s)
{
    if (isEmptyLStack(s))  //栈为空
    {
        return ERROR;
    }
    LinkStackPtr p, q;
    p = s->top;  //指向栈顶
    while (p)
    {
        q = p->next; //指向下一个结点
        free(p);
        p = q;
    }
    s->top = NULL;  //指向空指针
    s->count = 0;   //清空计数
    return SUCCESS;
}

//检测栈长度
Status LStackLength(LinkStack* s, int* length)
{
    *length = s->count;//传递个数
    return SUCCESS;
}

//入栈
Status pushLStack(LinkStack* s, ElemType data)
{
    LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode)); //开辟一个新的空间
    if (p == NULL)
    {
        printf("%s\n", strerror(errno));
        return ERROR;
    }
    p->next = s->top; //p的next指向栈顶
    p->data = data;   //获取数据
    s->top = p;       //p改为栈顶
    s->count++;       //数量加1
    return SUCCESS;
}

//出栈
Status popLStack(LinkStack* s, ElemType* data)
{
    if (isEmptyLStack(s))  //栈为空
    {
        return ERROR;
    }
    LinkStackPtr p = s->top; //p指向栈顶
    *data = s->top->data;    //获取数据
    s->top = s->top->next;   //栈顶指向下一个结点
    s->count--;              //数量减1
    free(p);                 //释放空间
    return SUCCESS;
}


//获取当前路径
void getpath(int n, FileType file[], FileTree pNode,char* path)
{
    int i;
    //char pathtemp[PATHMAXN];
    for (i = 0; i < n; i++)
    {
        if (strcmp(file[i].name, pNode->name) == 0)
        {
            strcpy(path, file[i].path);
            //strcat(path, ">");
            //strcpy()
            //return path;
        }
    }
}

//获取点的个数直到\
//返回 0 表错误
//返回 1 2 表点的个数
int getpoint(char *str)
{
    int num = getstringnum(str);
    int count = 0, i;
    for (i = 0; i < num; i++)
    {
        if (str[i] == '.')
            count++;
        else if (str[i] == '\\')
            break;
    }
    if (i == num)
        return 0;
    if (count > 2)
        return 0;
    else
        return count;
}

//相对路径转绝对路径
//curpath 当前路径  relpath 绝对路径
//返回绝对路径
char* Changepath(const char* curpath, char* relpath)
{
    char ch;
    int curpathnum = getstringnum(curpath);
    int relpathnum = getstringnum(relpath);
    char* curpathtemp  = (char*)calloc(sizeof(curpathnum+ relpathnum), 1);
    if (curpathtemp == NULL)
    {
        printf("%s\n", strerror(errno));
        return relpath;
    }
    strcpy(curpathtemp, curpath);
    int pointnum = 0;
    int i = 0;
    if (pointnum = getpoint(relpath))
    {
        if (pointnum == 1)
        {
            for (i = 1; i < relpathnum; i++)
            {
                relpath[i-1] = relpath[i];
            }
            relpath[i - 1] = '\0';
            strcat(curpathtemp, relpath);
            return curpathtemp;
        }
        else
        {
            for (i = 3; i < relpathnum; i++)
            {
                relpath[i - 3] = relpath[i];
            }
            relpath[i - 3] = '\0';
            for (i = curpathnum - 1; i >= 0; i--)
            {
                if (curpathtemp[i] == '\\')
                    break;
            }
            if (i < 0)
                return relpath;
            else
                curpathtemp[i] = '\0';
            if (relpath[0] == '\0')
            {
                return curpathtemp;
            }
            else
            {
                strcat(curpathtemp, "\\");
                strcat(curpathtemp, relpath);
            }
            return curpathtemp;
        }
    }
    else
        return relpath;
}


void UsersOperation(int* n, FileType file[], FileTree Userrootfile, UserNode* user)
{
    FileTree pNode = Userrootfile;
    char operation[NAMEMAXN];
    char temp[NAMEMAXN];
    char path[PATHMAXN];
    system("cls");
    printf("  ******************************************************\n\n");
    printf("  *                欢迎使用笔记管理系统                *\n \n");
    printf("  *                输入help查看操作目录                *\n \n");
    printf("  ******************************************************\n\n");
    getpath(*n, file, pNode, path);
    printf("%s>", path);
    while ((getstring(100, operation) != -1) && strcpy(temp, operation)) //获取输入
    {                              // 分割出操作命令和参数
        char* op_1 = strtok(operation, " ");
        char* op_2 = strtok(NULL, " ");
        char* op_3 = strtok(NULL, " ");
        char* op_4 = strtok(NULL, " ");
        char* op_5 = strtok(NULL, " ");
        char* op_6 = strtok(NULL, " ");
        if (strcmp(op_1, "ls") == 0)
        {
            if (op_2 != NULL)
            {
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            op_2 = Changepath(path, op_2);
                            ls_dir(op_2, file, Userrootfile, *n);
                        }
                        else if (strcmp(op_3, "grep") == 0)
                        {
                            if (op_4 != NULL)
                            {
                                if ('\"' == *op_4)
                                {
                                    if (removechar(op_4, '\"'))
                                    {
                                        if (op_5 == NULL)
                                        {
                                            op_2 = Changepath(path, op_2);
                                            ls_grep(op_2, op_4,file, Userrootfile,*n);
                                        }
                                        else
                                            goto error;
                                    }
                                    else
                                    {
                                        goto error;
                                    }
                                }
                                else
                                    goto error;
                            }
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else if (strcmp("-a", op_2) == 0)
                {
                    if (op_3 == NULL)
                        ls_a(Userrootfile,-1,user->data->userid);
                    else
                        goto error;
                }
                else
                    goto error;
            }
            else
            {
                ls(pNode, file, *n);
            }

        }
        else if (strcmp(op_1, "cd") == 0)
        {
            if (op_2 != NULL)
            {
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            op_2 = Changepath(path, op_2);
                            pNode = cd_dir(op_2, file, pNode, Userrootfile, *n);
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else if (strcmp("..", op_2) == 0)
                {
                    if (op_3 == NULL)
                        pNode = cd(pNode, user);
                    else
                        goto error;
                }
                else
                    goto error;
            }
            else
                goto error;

        }
        else if (strcmp(op_1, "mv") == 0)
        {
            if(op_2 != NULL)
            { 
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 != NULL)
                        {
                            if (*op_3 == '<')
                            {
                                if (removechar(op_3, '>'))
                                {
                                    if (op_4 == NULL)
                                    {
                                        mv(file, *n, op_2, op_3, &Userrootfile, user, &pNode);
                                    }
                                    else
                                        goto error;
                                }
                                else
                                    goto error;
                            }
                            else
                                goto error;
                        }
                        else
                        {
                            goto error;
                        }
                    }
                    else
                    {
                        goto error;
                    }

                }
                else if (strcmp(op_2, "-r") == 0)
                {
                    if (op_3 != NULL)
                    {
                        if ('<' == *op_3)
                        {
                            if (removechar(op_3, '>'))
                            {
                                if (op_4 != NULL)
                                {
                                    if (*op_4 == '<')
                                    {
                                        if (removechar(op_4, '>'))
                                        {
                                            if (op_5 == NULL)
                                            {
                                                mv_r(file, *n, op_3, op_4, &Userrootfile, user, &pNode);
                                            }
                                            else
                                            {
                                                goto error;
                                            }
                                        }
                                        else
                                            goto error;
                                    }
                                    else
                                        goto error;
                                }
                                else
                                {
                                    goto error;
                                }
                            }
                            else
                            {
                                goto error;
                            }

                        }
                    }
                    else
                    {
                        goto error;
                    }
                }
                else
                {
                    goto error;
                }
            }
            else
            {
                goto error;
            }
        }
        else if (strcmp(op_1, "rm") == 0)
        {
            if (op_2 != NULL)
            {   
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            rm(pNode, op_2, file, n, user);
                        }
                        else
                        {
                            goto error;
                        }
                    }
                    else
                        goto error;
                }
                else if (strcmp(op_2, "-r") == 0)
                {
                    if (op_3 != NULL)
                    {
                        if ('<' == *op_3)
                        {
                            if (removechar(op_3, '>'))
                            {
                                if (op_4 == NULL)
                                {
                                    rm_r(pNode, op_3, file, n, user);
                                }
                                else
                                {
                                    goto error;
                                }
                            }
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else
                    goto error;
            }
            else
            {
                goto error;
            }

        }
        else if (strcmp(op_1, "mkdir") == 0)
        {
            if (op_2 != NULL)
            {
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            mkdir(&pNode, op_2, file, n, user);
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else if (strcmp("-r", op_2) == 0)
                {
                    if (op_3 != NULL)
                    {
                        if ('<' == *op_3)
                        {
                            if (removechar(op_3, '>'))
                            {
                                if (op_4 == NULL)
                                {
                                    mkdir_r(&pNode, op_3, file, n, user);
                                }
                                else
                                    goto error;
                            }
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    else
                    {
                        goto error;
                    }
                }
                else
                    goto error;
            }
            else
                goto error;
        }
        else if (strcmp(op_1, "sort") == 0)
        {
            if (op_2 != NULL)
            {
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            sort(Userrootfile, op_2, file, *n, user);
                            Userrootfile = CreateFileTree(Userrootfile, file, *n);
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else
                    goto error;
            }
            else
                goto error;
        }
        else if (strcmp(op_1, "tag") == 0)
        {
            if (op_2 != NULL)
            {
                if ('<' == *op_2)
                {
                    if (removechar(op_2, '>'))
                    {
                        if (op_3 == NULL)
                        {
                            tag(pNode, op_2,file,*n);
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else if (strcmp("-add", op_2) == 0)
                {
                    if ('<' == *op_3)
                    {
                        if (removechar(op_3, '>'))
                        {
                            if (op_4 != NULL)
                            {
                                if (*op_4 == '\"')
                                {
                                    if (removechar(op_4, '\"'))
                                    {
                                        if (op_5 == NULL)
                                        {
                                            tag_add(pNode, op_3, op_4, file, *n);
                                        }
                                        else
                                            goto error;
                                    }
                                    else
                                        goto error;
                                }
                                else
                                    goto error;
                            }
                            else
                            {
                                goto error;
                            }
                        }
                        else
                            goto error;
                    }
                }
                else if (strcmp("-del", op_2) == 0)
                {
                    if ('<' == *op_3)
                    {
                        if (removechar(op_3, '>'))
                        {
                            if (op_4 != NULL)
                            {
                                if (*op_4 == '\"')
                                {
                                    if (removechar(op_4, '\"'))
                                    {
                                        if (op_5 == NULL)
                                        {
                                            tag_del(pNode, op_3, op_4, file, *n);
                                        }
                                        else
                                        {
                                            goto error;
                                        }
                                    }
                                    else
                                        goto error;
                                }
                                else
                                    goto error;
                            }
                            else
                            {
                                goto error;
                            }
                        }
                        else
                            goto error;
                    }
                }
                else if (strcmp("-s", op_2) == 0)
                {
                    if (op_3 != NULL)
                    {
                        if ('\"' == *op_3)
                        {
                            if (removechar(op_3, '\"'))
                            {
                                if (op_4 == NULL)
                                {
                                    tag_s(pNode, op_3, file, *n);
                                }
                                else
                                    goto error;
                            }
                            else
                                goto error;
                        }
                    }
                    else
                        goto error;
                }
                else if (strcmp("-sa", op_2) == 0)
                {
                    if ('\"' == *op_3)
                    {
                        if (removechar(op_3, '\"'))
                        {
                            if (op_4 == NULL)
                            {
                                tag_sa(op_3, file, *n);
                            }
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    else
                    {
                        goto error;
                    }
                }
            }
            else
            {
                goto error;
            }
            SaveFile(file, *n, user->data->userfilename);//保存标签内容到文件
        }
        else if (strcmp(op_1, "help") == 0)
        {
        if (op_2 == NULL)
        {
            ShowInfo();
        }
        else
            goto error;
        }
        else if (strcmp(op_1, "cls") == 0)
        {
        if (op_2 == NULL)
        {
            system("cls");
        }
        else
            goto error;
        }
        else if (strcmp(op_1, "exit") == 0)
        {
        if (op_2 == NULL)
        {
            return;
        }
        else
            goto error;
        }
        else
        {
        error:  printf("ERROR:不支持\" %s \"命令, 请重新输入!\n", temp);
        }
        getpath(*n, file, pNode, path);
        printf("%s>", path);
    }
}



