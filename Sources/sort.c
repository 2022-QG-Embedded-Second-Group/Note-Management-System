/**
 * @brief sort<�ʼ��ļ�����>: ���ļ�������ļ�������ĸ��������
 *
 * @param pNode
 * @param filename �ļ����У���
 */
void sort(FileTree pNode, char* filename)
{

    if (strcmp(pNode->name, filename) == 0 && pNode->fchild)
    {
        FileTree tem = (FileTree)malloc(sizeof(FileNode));
        for (int i = 0; i < *n; i++)
        {
            FileTree p = pNode->fchild;
            while (p->sbi) {
                if (p->name[0] > p->sbi->name[0]) {
                    tem = p;
                    p = p->sbi;
                    p->sbi = tem;
                }
                p = p->sbi;
            }
        }
    }
    else {
        if (pNode->fchild)
        {
            pNode = pNode->fchild;
            sort(pNode, filename);
        }
        else
        {
            printf("δ���ҵ����ļ���\n");
            return;
        }
    }


}