#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "file.h"
//#include <Windows.h>

//ȥ����һ���ַ������һ���ַ�
//����0  ��ʧ��
//����1  ��ɹ�
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
    //printf("  *                ��ӭʹ���ļ�ģ��ϵͳ                 *\n \n");
    //printf("  ******************************************************\n\n");
    printf("  ��ϵͳĿǰ֧�����¹��ܣ�\n");
    printf("  1. ls : ��ʾ��ǰĿ¼�����еıʼ��ļ�\n");
    printf("  2. ls -a : ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�\n");
    printf("  3. ls <�ļ���·��> : ��ʾ����ָ���ļ������е�����\n");
    printf("  4. ls <�ʼ��ļ���·��> grep ���������� : ��ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ�����\n");

    printf("  5. cd .. : �л�����ǰ·�����ϼ��ļ���\n");
    printf("  6. cd <�ʼ��ļ���·��> : ��·���л�Ϊ������������ļ���·��\n");

    printf("  7. mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼> : ���ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼��\n");
    printf("  8. mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���> : ���ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ���\n");
    printf("  9. mv -r <���ƶ����ļ���> <Ŀ���ļ���>: ��ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼��\n");

    printf("  10. rm <�ʼ��ļ���> : �Աʼ��ļ�����ɾ��\n");
    printf("  11. rm -r <�ʼ��ļ�������> : ɾ��ָ���ļ����Լ����ڲ���������\n");

    printf("  12. mkdir <�ļ���> : �ڵ�ǰ·�����½��ļ�\n");
    printf("  13. mkdir -r <�ļ�����> : �ڵ�ǰ·�����½��ļ���\n");

    printf("  14. sort <�ʼ��ļ�����> : ��ָ���ļ����ڵıʼ��ļ����ļ�������ĸ��������\n");

    printf("  15. tag <�ʼ��ļ���/�ʼ��ļ�����> : ��ʾָ���ʼ�/�ļ��еı�ǩ\n");
    printf("  16. tag -add <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ� : Ϊָ���ʼ�/�ʼ��ļ������ӱ�ǩ\n");
    printf("  17. tag -del <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ� : ɾ��ָ���ʼ�/�ļ��е�ָ����ǩ\n");
    printf("  18. tag -s ����ǩ���ݡ� : �ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���\n");
    printf("  19. tag -sa ����ǩ���ݡ� : �����бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��\n");
    printf("  20. help ��ʾ�����ĵ�\n");
    printf("  21. cls  ����\n");
    printf("  22. exit ����\n");
    printf("  \n");
    //printf("  ������ָ��: ");
    //system("pause");
}

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char* getDateTime()
{
    static char cur_time[20]; // ���ؾֲ��������ʼ�static
    time_t t;
    struct tm* lt;
    time(&t);
    lt = localtime(&t); //תΪʱ��ṹ
    sprintf(cur_time, "%04d/%02d/%02d %02d:%02d:%02d", lt->tm_year + 1900, (lt->tm_mon+1), lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    return cur_time;
}

/**
 * @brief �����������ݵ����鱣�浽�ļ���ȥ
 *
 * @param file �������ݵ�����
 * @param n ���������
 * @param filename �û��ļ�����
 */
void SaveFile(FileType file[], int n, char* filename)
{
    int i;
    FILE* fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("�����ļ��޷���");
        return;
    }
    for (i = 0; i < n; i++)
    {
        fwrite(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief ���ļ��ж�ȡ���������ݵ�����
 *
 * @param file
 * @param n ���֣���ʾ����ĳ��ȣ��ĵ�ֵַ
 * @param filename �û��ļ�����
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
    fseek(fp, 0, SEEK_END);         // �ض�λ���ϵ��ļ�ָ��,��fpָ���˻ص����ļ���β0�ֽڴ�
    long length = ftell(fp);        // ���ú���ftell()��õ�ǰλ��������ļ��׵�λ�ƣ���λ��ֵ�����ļ������ֽ���
    rewind(fp);                     // ��λ��ָ������ָ���ļ��Ŀ�ͷ
    *n = length / sizeof(FileType); // �õ�һ���ж��ٸ��ṹ����
    for (int i = 0; i < *n; i++)
    {
        fread(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief Create a File Tree object
 *
 * @param root ���ڵ㴫��"Root"
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
    initLStack(&s);//��ʼ��
    int ntemp = n;
    while (n)
    {
        for (i = 0; i < ntemp; i++)
        {
            //ʵ�ֲ�α���
            if (strcmp(file[i].fathername, father->name) == 0)//�ҵ��ӽڵ�
            {
                FileTree pchild = (FileTree)malloc(sizeof(FileNode));
                strcpy(pchild->name, file[i].name);//���ָ�ֵ
                pchild->father = father;
                pchild->fchild = NULL;
                pchild->sbi = NULL;
                if (father->fchild == NULL)//�����ڵ�һ���ڵ�
                {
                    father->fchild = pchild;
                    pchild->father = father;
                }
                else//�Ѵ����ӽڵ�
                {
                    FileTree ptemp1 = father->fchild;//ָ���һ���ӽڵ�
                    FileTree ptemp2 = NULL;
                    while (ptemp1)
                    {
                        ptemp2 = ptemp1;//��ס��һ���ڵ��λ��
                        ptemp1 = ptemp1->sbi;
                    }
                    ptemp2->sbi = pchild;//ǰһ���ֵܽڵ�ָ��ǰ�Ľڵ�
                }
                pushLStack(&s, pchild);//��ջ
                n--;
            }
        }
        if (isEmptyLStack(&s) == 0)
        {
            popLStack(&s, &father);//��ջ����Ϊһ������ĸ��ڵ�
            //strcpy(fathername, father->name);
        }
        if (n == 1)//���ڵ㲻�ñ���
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
//    if (i < n) // ���ҵ���һ�����ڵ�����Ϊroot��
//    {
//        FileTree p = (FileTree)malloc(sizeof(FileNode)); // ����һ����ʱָ��
//        p->fchild = p->sbi = p->father = NULL;
//        strcpy(p->name, file[i].name);
//        bt->fchild = p;
//
//        for (j = i; j < n; j++)
//        {
//            if (strcmp(file[j].fathername, root) == 0)
//            {
//                p = CreateFileTree(file[j].name, file, n); //! �ݹ�
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
 * @brief ls: ��ʾ��ǰĿ¼�����еıʼ��ļ����ļ���
 *
 * @param pNode
 */
void ls(FileTree pNode, FileType file[], int n)
{
    FileTree p = pNode->fchild;
    if (p == NULL)
    {
        printf("��ǰĿ¼��û���ļ�(��)\n");
    }
    for (; p; p = p->sbi)
    {
        printf("%-10s\t", p->name);
        FileType pfile = Findfile(file, n, p->name);
        printf("%-20s\t", pfile.datetime);
        if (pfile.flag == 1)
            printf("�ļ�\n");
        else
            printf("�ļ���\n");
    }
}

//! ��״�ṹ��ʾ
/**
 * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level, char *rootname)
{
    if (strcmp(pNode->name, rootname) == 0) // �׽ڵ㶨��Ϊ������ΪRoot
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
    if (pNode->fchild) // �����ӽڵ�
    {
        ls_a(pNode->fchild, level + 1, ""); // �ݹ����
    }
    if (pNode->sbi)
    {
        ls_a(pNode->sbi, level, "");
    }
    return;
}

/**
 * @brief ģ�������ж��Ƿ����ɸѡ����
 *
 * @param key �ؼ���
 * @param str �����ҵ��ַ���
 * @return int 1Ϊ����,0������
 */
int result_mohu(const char* key, char* str)
{
    typedef struct
    {
        char son[11];
    } Element;

    int i, j, k = 0, l = 0, m = 0;

    // f=1Ϊ����ɸѡ����
    int f = 0;

    // N1Ϊstr�ĳ��� N2Ϊstr�����Ӵ��ĸ���
    int N1 = 0, N2 = 0;
    N1 = strlen(str);
    /*���������Ӵ��ĸ���*/
    for (i = 1; i <= N1; i++)
        N2 += i;

    /*���������Ӵ��ĸ���*/
    // i�������ַ����ĳ���
    // j���Ƹ�ֵ
    // k�����µ����Խṹb���±�
    // l�����������������ԭ�����е�λ��
    // m���Ƽ���������ֵ��str���±�
    Element* b = malloc(sizeof(Element) * N2);
    for (i = 1; i <= N1; i++)
    {
        l = 0;
        /*whileѭ����Ϊ��һ�����ַ������鸳ֵ*/
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

    //�����ȶ�
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
    return; //������Ϊ�գ�������һ��
}

/**
 * @brief ͨ��file[i].name��pNode->nameƥ��
 * ����������ݹ����ƥ��Ľڵ�
 *
 * @param pNode
 * @param filename
 * @param b ��Ҫ��ȡ��Ŀ��ڵ�
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

//Ѱ�ҽڵ�
//�����ҵ��Ľڵ�
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
                    pushLStack(&s, p);//��ջ
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
                pushLStack(&s, p);//��ջ
            if (strcmp(p->name, name) == 0)
            {
                return p;
            }
            p = p->sbi;
        }
        if (!isEmptyLStack(&s))
        {
            popLStack(&s, &p);//��ջ
            goto coti;
        }
    } while (!isEmptyLStack(&s));
    printf("����\n");
}

/**
 * @brief ls <�ʼ��ļ���·��> grep ���������ݡ�����ʾ����ָ���ļ������еĴ�
���������ݵ��ļ��������ļ���
 *
 * @param dirpath �ʼ��ļ���·��
 * @param SearchContent ��������
 * @param file ����
 * @param root ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 */
void ls_grep(char* dirpath, char* SearchContent, FileType file[], FileTree root, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // ����·��ƥ�䣬ͨ��·���ҵ�file[i]
        {
            FileTree b = Searchpath(root, file[i].name);
            FileTree p = b->fchild;
            for (; p; p = p->sbi)
            {
                if (strstr(p->name, SearchContent) != NULL) // ģ�������ж��Ƿ����ɸѡ����
                {
                    printf("%s ", p->name);
                }
            }
            printf("\n");
            return;
        }
    }
    printf("δ�ҵ���·��\n");
}


 /**
  * @brief ls <�ʼ��ļ���·��>����ʾ����ָ���ļ������е�����(�ӱʼ��ļ��кͱʼ��ļ�)
  * //!Ŀǰֻ֧�־���·��
  *
  * @param dirpath �����·������
  * @param file ����
  * @param pNode ��Ҫ����Root�ڵ�
  * @param n ���鳤��
  */
void ls_dir(char* dirpath, FileType file[], FileTree pNode, int n)
{
    int i;
    for ( i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // ����·��ƥ�䣬ͨ��·���ҵ�file[i]
        {
            FileTree b;
            PreOrderFindNode_Path(pNode, file[i].name, &b); // ͨ��file[i]����ƥ������ڵ�
            ls(b, file, n);                                         // ����ls()��������ӡ·���µ���������
            return;
        }
    }
    if (i == n)
        printf("δ���ҵ���·��");
}


/**
 * @brief cd ..����·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼.���Ǹ�Ŀ¼���򲻽����л�
 * ���ڲ����������ж��ٽ��е��ã��ǵ������ǰ�ڵ�·��Ӵ
 *
 * @param pNode ��ǰ�ڵ�
 * @return FileTree
 */
FileTree cd(FileTree pNode, UserList user)
{
    if (strcmp(pNode->name, user->data->userid) == 0) // �������Ľڵ��Ǹ��ڵ㣬�������л�
    {
        printf("�л�ʧ��\n");
        return pNode; // ���ظ��ڵ�
    }
    printf("�л��ɹ�\n");
    return pNode->father;
}


/**
 * @brief cd <�ʼ��ļ���·��>����·���л�Ϊ������������ļ���·��
 * //!Ŀǰֻ֧�־���·��
 *
 * @param dirpath �����·������
 * @param file ����
 * @param pNode �Ƚڵ�
 * @param root ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 * @return FileTree ���ؽڵ�
 */
FileTree cd_dir(char* dirpath, FileType file[], FileTree pNode, FileTree root, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath) == 0) // ����·��ƥ�䣬ͨ��·���ҵ�file[i]
        {
            FileTree b;
            PreOrderFindNode_Path(root, file[i].name, &b); // ͨ��file[i]����ƥ������ڵ�
            return b;
        }
    }  
    printf("δ���ҵ���·��\n");
    return pNode;
}

 /**
  * @brief rm <�ʼ��ļ���>���Աʼ��ļ�����ɾ��
  *
  * @param pNode
  * @param filename
  * @param file ����
  * @param n ���鳤��
  */
void rm(FileTree pNode, char* filename, FileType file[], int* n, UserList user)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (strcmp(file[i].fathername, pNode->name) != 0)
            {
                printf("���ļ����ڵ�ǰĿ¼��\n");
                return;
            }

            if (file[i].flag == 0)
            {
                printf("����һ���ļ���,��Ҫɾ��,�����롰rm -r <Ҫɾ���ıʼ��ļ�������>��\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // ������״��ĵ�һ���ӽڵ�
            {
                pNode->fchild = p->sbi;
                free(p);
            }
            else // ������ֵܽڵ㣬���޽ӡ�
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

            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j] = file[j + 1];
            }

            (*n)--;
            SaveFile(file, *n, user->data->userfilename);
            printf("ɾ���ɹ�\n");
            return;
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}

/**
 * @brief rm -r <�ʼ��ļ�������>��ɾ���ƶ��ļ��Լ����ڲ���������
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void rm_r(FileTree pNode, char* filename, FileType file[], int* n, UserList user)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (strcmp(file[i].fathername, pNode->name) != 0)
            {
                printf("���ļ����ڵ�ǰĿ¼��\n");
                return;
            }

            if (file[i].flag == 1)
            {
                printf("����һ���ļ�,��Ҫɾ��,�����롰rm <Ҫɾ���ıʼ��ļ���>��\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // ������״��ĵ�һ���ӽڵ�
            {
                pNode->fchild = p->sbi;
                PostOrderTraverse(p, file, n);
                free(p);
            }
            else // ������ֵܽڵ㣬���޽ӡ�
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
            printf("ɾ���ɹ�\n");
            return;
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}
void DeleteNode(FileTree pNode, FileType file[], int* n)
{

    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, pNode->name) == 0)
        {
            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
}

/**
 * @brief mkdir<�ʼ��ļ���>: �ڵ�ǰ�ļ���pNode���½��ļ�
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
void mkdir(FileTree *pNode, char* filename, FileType file[], int* n, UserList user)
{
    int locate = 0;
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("���ļ����У������Ѵ���\n");
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
            printf("����һ���ļ����޷��ڴ�Ŀ¼�´����ļ�\n");
            return;
        }
        strcpy(file[*n].fathername, (*pNode)->name);
        strcpy(file[*n].name, filename);
        file[*n].tagnum = 0;//��ʼ������
        //���ɵ�ǰ·��
        char tmp[PATHMAXN];
        strcpy(tmp, file[locate].path);
        strcat(tmp, "\\");
        strcat(tmp, filename);
        strcpy(file[*n].path, tmp);

        file[*n].flag = 1; // 1��ʾ����һ���ļ�
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
        printf("��ӳɹ�\n");
    }

}

/**
 * @brief mkdir -r<�ʼ��ļ�����>: �½��ļ���
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void mkdir_r(FileTree *pNode, char* filename, FileType file[], int* n, UserList user)
{
    int locate = 0;
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("���ļ����У������Ѵ���\n");
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
            printf("����һ���ļ����޷��ڴ�Ŀ¼�´����ļ�\n");
            return;
        }
        strcpy(file[*n].fathername, (*pNode)->name);
        strcpy(file[*n].name, filename);
        file[*n].tagnum = 0;//��ʼ������
        //���ɵ�ǰ·��
        char tmp[PATHMAXN];
        strcpy(tmp, file[locate].path);
        strcat(tmp, "\\");
        strcat(tmp, filename);
        strcpy(file[*n].path, tmp);

        file[*n].flag = 0; // 0��ʾ����һ���ļ���
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
        printf("��ӳɹ�\n");
    }
}

/**
 * @brief tag <�ʼ��ļ���/�ʼ��ļ�����> ��ʾ��ǰĿ¼�µ�ָ���ʼ�/�ļ��еı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ� 
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag(FileNode* pNode, char* filename, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//��ʾ�ڸ�Ŀ¼��
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    printf("��ǩ%d: %s\n", j + 1, file[i].tag[j]);//��ӡ��ǩ
                }
                if (0 == file[i].tagnum)
                    printf("���ޱ�ǩ\n");
                break;
            }
        }
    }
    if (i == n)//û���ҵ����ļ�(��)
    {
        printf("��Ŀ¼��û��ָ�����ļ�(��)\n");
    }
}

/**
* @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����> �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ������ӱ�ǩ
*
* @param pNode,��ǰĿ¼�Ľڵ�
* @param filename ָ�����ļ��л��ļ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_add(FileNode* pNode, char* filename, char* tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//��ʾ�ڸ�Ŀ¼��
            {
                if (file[i].tagnum > 2)//��ʾ������ǰ���ı�ǩ����
                {
                    printf("�������ı�ǩ��\n");
                }
                else
                {
                    for (j = 0; j < file[i].tagnum; j++)//Ѱ���Ƿ�����ͬ�ı�ǩ����
                    {
                        if (strcmp(file[i].tag[j], tagname) == 0)
                        {
                            printf("���ʧ��, �ñ�ǩ�Ѵ���\n");
                            break;
                        }
                    }
                    if (j == file[i].tagnum)//û���ҵ���ͬ�ı�ǩ����
                    {
                        strcpy(file[i].tag[j], tagname);
                        file[i].tagnum++;
                        printf("��ӳɹ�\n");
                    }
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("��Ŀ¼��û���ҵ�ָ�����ļ�(��)\n");
    }
}

/**
* @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����>> ����ǩ���ݡ�: �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ���ɾ��ָ���ı�ǩ
*
* @param pNode,��ǰĿ¼�Ľڵ�
* @param filename ָ�����ļ��л��ļ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_del(FileNode* pNode, char* filename, char* tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0)//�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0)//��ʾ�ڸ�Ŀ¼��
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    if (strcmp(file[i].tag[j], tagname) == 0)//�ҵ��ñ�ǩ
                    {
                        file[i].tagnum--;//��ǩ����-1
                        memset(file[i].tag[j], 0, sizeof(file[i].tag[j]));//�������
                        printf("ɾ���ɹ�\n");
                    }
                }
                if (j == file[i].tagnum)
                {
                    printf("û���ҵ��ñ�ǩ\n");
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("��Ŀ¼��û���ҵ�ָ�����ļ�(��)\n");
    }
}

/**
* @brief tag-s ����ǩ���ݡ��� ���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���
* @param pNode,��ǰĿ¼�Ľڵ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_s(FileNode* pNode, char* tagname, FileType file[], int n)
{
    int i, j;
    int flag = 1;
    for (i = 0; i < n; i++) // �ҵ���ǰ·���µ��ļ�(��)
    {
        if (strcmp(file[i].fathername, pNode->name) == 0)//�ڵ�ǰĿ¼�µ�
        {
            for (j = 0; j < file[i].tagnum; j++)
            {
                if (strcmp(file[i].tag[j], tagname) == 0)//�ҵ���ͬ�ı�ǩ
                {
                    printf("<%s>\n", file[i].name);//��ӡ�ļ�(��)����
                    flag = 0;
                }
            }
        }
    }
    if (flag)
        printf("��Ŀ¼�²����ڸñ�ǩ\n");
}

/**
* @brief tag-sa ����ǩ���ݡ��� ���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_sa(char* tagname, FileType file[], int n)
{
    int i, j;
    int flag = 1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < file[i].tagnum; j++)
        {
            if (strcmp(tagname, file[i].tag[j]) == 0)//�ҵ���ͬ���Ƶı�ǩ
            {
                printf("%-20s\t%-20s\n",file[i].name, file[i].path);//��ӡ�ļ������ļ�·��
                flag = 0;
            }
        }
    }
    if (flag)
        printf("�Ҳ����ñ�ǩ\n");
}

/**
 * @brief sort <�ʼ��ļ�����>
 * ��ָ���ļ����ڵıʼ��ļ����ļ�������ĸ��������
 * ����һ�����½����������ڵ���������������
 *
 * @param root ������ڵ㡪��user->data->userid
 * @param filename �����·����
 * @param file ����
 * @param n ���鳤��
 * @param user UserLiset
 */
void sort(FileTree root, char* filename, FileType file[], int n, UserList user)
{
    int i, count = 0;
    for (i = 0; i < n; i++) // �ж������Ƿ�Ϊ�ļ�
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("����һ���ļ�,�޷������������\n");
                return;
            }
        }
    }
    FileType tmparr[FILEMAXN], max; // ��ʱ���
    for (i = 0; i < n; i++)
    {
        if (strcmp(file[i].fathername, filename) == 0) // �����filename�ļ����µ��ļ�
        {
            tmparr[count++] = file[i];
        }
    }
    for (i = 0; i < count - 1; i++) // ������tmparr����ð������
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
    for (count = 0, i = 0; i < n; i++) // ����������ʱ������ԭʼ������
    {
        if (strcmp(file[i].fathername, filename) == 0)
        {
            file[i] = tmparr[count++];
        }
    }
    SaveFile(file, n, user->data->userfilename);
    printf("����ɹ�\n");
    return;
}

//�ж�ĳһ���ַ����ֵ�����
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

//Ѱ�ҽڵ�
//�����ҵ��Ľڵ�
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
                    pushLStack(&s, p);//��ջ
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
                pushLStack(&s, p);//��ջ
            if (strcmp(p->name, pNode->name) == 0)
            {
                return p;
            }
            p = p->sbi;
        }
        if (!isEmptyLStack(&s))
        {
            popLStack(&s, &p);//��ջ
            goto con;
        }
    } while (!isEmptyLStack(&s));
    printf("����\n");
}

/*��ȡ�ַ����ַ���*/
//�����ַ���
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

/*��ȡָ���������ַ���*/
char* getappointstr(char* str, int num)
{
    str[num] = '\0';
    return str;
}


/**
* @brief mv -r <���ƶ����ļ���> <Ŀ���ļ���>����ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼�¡�
* @param file        ���û�������
* @param n           ���鳤��
* @param movefile    ���ƶ��ļ�������
* @param destination Ŀ���ļ�������
* @param bt          �û�����
* @param user        �û��ڵ�
*/
void mv_r(FileType file[], int n, char* movefile, char* destination, FileTree* bt, UserNode* user, FileTree* pNode)
{
    int i;
    int movefilelocate = 0, destinationlocate = 0;
    //char movefathername[100], movename[100], destinationName[100];
    int movefilelevel, destinationlevel = 0;//�ж��ļ�����
    for (i = 0; i < n; i++)
    {
        if (strcmp(file[i].name, movefile) == 0)//Ѱ�ұ��ƶ��ļ�������
        {
            if (file[i].flag == 1)//��Ҫ�ƶ������ļ�
            {
                printf("Ҫ�ƶ������ļ�, �����ϸò���\n");
                return;
            }
            else
            {
                if (strcmp(file[i].fathername, destination) == 0)
                {
                    printf("�ļ��Ѿ��ڸ�Ŀ¼��");
                    return;
                }
                //strcpy(movefathername, file[i].fathername);//��ס�ϼ�Ŀ¼���� 
                //strcpy(movename, file[i].name);//
                //strcpy(file[i].fathername, destination);
                movefilelocate = i;//��ס���ƶ��ļ�λ��

                //break;
            }
        }
        if (strcmp(destination, file[i].name) == 0)//�ҵ�Ŀ���ļ���
        {
            if (file[i].flag == 1)//�ļ�
            {
                printf("��Ŀ�겻���ļ���\n");
                return;
            }
            //strcpy(destinationName, destination);
            destinationlocate = i;//��סĿ���ļ���λ��
        }
    }
    destinationlevel = countnum(file[destinationlocate].path, '\\');
    movefilelevel = countnum(file[movefilelocate].path, '\\');
    int  movefilenum = getstringnum(file[movefilelocate].path);
    int  destinationnum = getstringnum(file[destinationlocate].path);
    if (movefilelevel < destinationlevel)//�ƶ��ļ��еļ���С��Ŀ���ļ���
    {
        if (destinationnum > movefilenum)
        {
            char* pathtemp = getappointstr(file[destinationlocate].path, movefilenum);
            if (strcmp(pathtemp, file[movefilelocate].path) == 0)
            {
                printf("�ƶ�ʧ��\n");
                return;
            }
        }
    }
    strcpy(file[movefilelocate].fathername, destination);
    //������·��
    char path[PATHMAXN];
    strcpy(path, file[destinationlocate].path);
    strcat(path, "\\");
    strcat(path, file[movefilelocate].name);
    strcpy(file[movefilelocate].path, path);
    //�ļ�����
    SaveFile(file, n, user->data->userfilename);
    (*bt) = CreateFileTree(user->data->userid, file, n);
    (*pNode) = SearchpNode(*bt, *pNode);
    //FileTree p = bt, ptemp = NULL, pfather = NULL, pchild = NULL, pre = NULL, movefather = NULL;
    //LinkStack s;
    //initLStack(&s);
    /*
    while (n)//������
    {
        while (p)
        {
            if (p->fchild != NULL)
                if (p->sbi != NULL)
                    pushLStack(&s, p);//��ջ
            if (strcmp(p->name, destination) == 0)//�ҵ�Ŀ���ļ���
                pfather = p;
            if (strcmp(p->name, movefile) == 0)//�ҵ����ƶ��ļ���
                pchild = p;
            if (p->sbi)
            {
                if (strcmp(p->sbi->name, movefile) == 0)//�ҵ�ǰ�ڵ�
                    pre = p;
            }
            if (p->fchild)
            {
                if (strcmp(p->fchild->name, movefile) == 0)//�ҵ����ڵ�
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
                pushLStack(&s, p);//��ջ
            if (strcmp(p->name, destination) == 0)//�ҵ�Ŀ���ļ���
                pfather = p;
            if (strcmp(p->name, movefile) == 0)//�ҵ����ƶ��ļ���
                pchild = p;
            if (p->sbi)
            {
                if (strcmp(p->sbi->name, movefile) == 0)//�ҵ�ǰ�ڵ�
                    pre = p;
            }
            if (p->fchild)
            {
                if (strcmp(p->fchild->name, movefile) == 0)//�ҵ����ڵ�
                    movefather = p;
            }
            p = p->sbi;
            n--;
        }
        if (!isEmptyLStack(&s))
            popLStack(&s, &p);//��ջ
    }

    if (pre != NULL)//�ƶ��ļ�����ǰ�ڵ�
    {
        pre->sbi = pre->sbi->sbi;
    }
    else//û��ǰ�ڵ�
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
    printf("�ƶ��ɹ�\n");
}

/**
* @brief mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>�����ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼�¡�
*        mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>�����ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ�����
* @param file        ���û�������
* @param n           ���鳤��
* @param pfile       �ļ�������
* @param destination Ŀ���ļ�������
* @param bt          �û�����
* @param user        �û��ڵ�
*/
void mv(FileType file[], int n, char* pfile, char* destination, FileTree* bt, UserNode* user, FileTree* pNode)
{
    int i;
    int pfilelocate = -1, destionationlocate = -1;
    int renameflag = 1;//1��ʾ��������0��ʾ�ƶ�
    for (i = 0; i < n; i++)//�ж��Ƿ��ƶ�����������
    {
        if (strcmp(destination, file[i].name) == 0)//�ҵ���ͬ���֣����ƶ�����
        {
            if (file[i].flag == 1) //���Ŀ���������ļ�
            {
                printf("��Ŀ�����ļ����޷��ƶ�����Ŀ¼��\n");
                return;
            }
            destionationlocate = i;//��סdestionationλ��
            renameflag = 0;
        }
        if (strcmp(pfile, file[i].name) == 0)//�ҵ��ļ�
        {
            if (file[i].flag == 0)//������ļ���
            {
                printf("��Ҫ���������ļ���, �����ϸò���\n");
                return;
            }
            else//�ļ�
            {
                pfilelocate = i;//��סλ��
            }
        }
    }
    if (pfilelocate == -1)//û�и��ļ�
    {
        printf("�Ҳ������ļ�\n");
        return;
    }
    if (renameflag == 1)//������
    {
        strcpy(file[pfilelocate].name, destination);//������
    }
    else//�ƶ��ļ�
    {
        //�ı丸�ڵ�
        strcpy(file[pfilelocate].fathername, file[destionationlocate].name);
        //��������·��
        char path[PATHMAXN];
        strcpy(path, file[destionationlocate].path);
        strcat(path, "\\");
        strcat(path, file[pfilelocate].name);
        strcpy(file[pfilelocate].path, path);
    }
    //�ļ�����
    SaveFile(file, n, user->data->userfilename);
    (*bt) = CreateFileTree(user->data->userid, file, n);//���½���
    (*pNode) = SearchpNode(*bt, *pNode);
    /*
    //LinkStack s;
    //initLStack(&s);
    //FileTree p = bt, ptemp = NULL, pmove = NULL, pdestination = NULL, pre = NULL;
    //while (n)//������
    //{
    //    while (p)
    //    {
    //        if (p->fchild != NULL)
    //            if (p->sbi != NULL)
    //                pushLStack(&s, p);//��ջ
    //        if (strcmp(p->name, pfile) == 0)//�ҵ����ļ�
    //        {
    //            if (renameflag == 1)//������
    //            {
    //                strcpy(p->name, destination);
    //                //�ļ�����
    //                SaveFile(file, n, user->data->userfilename);
    //                return;
    //             }
    //            pmove = p;//��סҪ�ƶ����ļ��Ľڵ�λ��
    //        }
    //        if (strcmp(p->name, destination) == 0)//�ҵ�Ŀ���ļ�����
    //        {
    //            pdestination = p;//��ס�ýڵ�λ��
    //        }
    //        if (p->sbi)
    //        {
    //            if (strcmp(p->sbi->name, pfile) == 0)//�ҵ��ֵܽڵ�
    //                pre = p;//��סǰһ���ֵܽڵ�
    //        }
    //        ptemp = p;
    //        p = p->fchild;
    //        n--;
    //    }
    //    p = ptemp;
    //    while (p)
    //    {
    //        if (strcmp(p->name, pfile) == 0)//�ҵ����ļ�
    //        {
    //            if (renameflag == 1)//������
    //            {
    //                strcpy(p->name, destination);
    //                SaveFile(file, n, user->data->userfilename);
    //                return;
    //            }
    //            pmove = p;//��סҪ�ƶ����ļ��Ľڵ�λ��
    //        }
    //        if (strcmp(p->name, destination) == 0)//�ҵ�Ŀ���ļ�����
    //            pdestination = p;//��סĿ��ڵ�λ��
    //        if (p->sbi)
    //        {
    //            if (strcmp(p->sbi->name, pfile) == 0)//�ҵ��ֵܽڵ�
    //                pre = p;//��סǰһ���ֵܽڵ�
    //        }
    //        p = p->sbi;
    //        n--;
    //    } 
    //    if (!isEmptyLStack(&s))
    //        popLStack(&s, &p);//��ջ
    //}
    */
    /*
    //if (pre == NULL)//�ƶ����ļ���firstchild�ڵ�
    //{
    //    pmove->father->fchild = pmove->sbi;
    //}
    //else //�ƶ����ļ�����firstchild
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

//��ʼ��ջ
Status initLStack(LinkStack* s)
{
    s->top = NULL;//ָ���ָ��
    s->count = 0;//��ʼ����ֵ
    return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
//����0 ��ջ��Ϊ��
//����1 ��ջΪ��
Status isEmptyLStack(LinkStack* s)
{
    if (s->count)  //ջ��Ϊ��
        return 0;
    else          //ջΪ��
        return 1;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack* s, ElemType* e)
{
    if (isEmptyLStack(s))  //ջΪ��
    {
        return ERROR;
    }
    *e = s->top->data;  //�����ݴ���e
    return SUCCESS;
}


//���ջ
Status clearLStack(LinkStack* s)
{
    system("cls");
    LinkStackPtr p, q;
    p = s->top;  //ָ��ջ��
    while (p)
    {
        q = p->next; //ָ����һ�����
        free(p);
        p = q;
    }
    s->top = NULL;  //ָ���ָ��
    s->count = 0;   //��ռ���
    return SUCCESS;
}

//����ջ
Status destroyLStack(LinkStack* s)
{
    if (isEmptyLStack(s))  //ջΪ��
    {
        return ERROR;
    }
    LinkStackPtr p, q;
    p = s->top;  //ָ��ջ��
    while (p)
    {
        q = p->next; //ָ����һ�����
        free(p);
        p = q;
    }
    s->top = NULL;  //ָ���ָ��
    s->count = 0;   //��ռ���
    return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack* s, int* length)
{
    *length = s->count;//���ݸ���
    return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack* s, ElemType data)
{
    LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode)); //����һ���µĿռ�
    if (p == NULL)
    {
        printf("%s\n", strerror(errno));
        return ERROR;
    }
    p->next = s->top; //p��nextָ��ջ��
    p->data = data;   //��ȡ����
    s->top = p;       //p��Ϊջ��
    s->count++;       //������1
    return SUCCESS;
}

//��ջ
Status popLStack(LinkStack* s, ElemType* data)
{
    if (isEmptyLStack(s))  //ջΪ��
    {
        return ERROR;
    }
    LinkStackPtr p = s->top; //pָ��ջ��
    *data = s->top->data;    //��ȡ����
    s->top = s->top->next;   //ջ��ָ����һ�����
    s->count--;              //������1
    free(p);                 //�ͷſռ�
    return SUCCESS;
}


//��ȡ��ǰ·��
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

//��ȡ��ĸ���ֱ��\
//���� 0 �����
//���� 1 2 ���ĸ���
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

//���·��ת����·��
//curpath ��ǰ·��  relpath ����·��
//���ؾ���·��
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
    printf("  *                ��ӭʹ�ñʼǹ���ϵͳ                *\n \n");
    printf("  *                ����help�鿴����Ŀ¼                *\n \n");
    printf("  ******************************************************\n\n");
    getpath(*n, file, pNode, path);
    printf("%s>", path);
    while ((getstring(100, operation) != -1) && strcpy(temp, operation)) //��ȡ����
    {                              // �ָ����������Ͳ���
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
            SaveFile(file, *n, user->data->userfilename);//�����ǩ���ݵ��ļ�
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
        error:  printf("ERROR:��֧��\" %s \"����, ����������!\n", temp);
        }
        getpath(*n, file, pNode, path);
        printf("%s>", path);
    }
}



