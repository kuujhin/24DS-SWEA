#include <stdio.h>
#include <iostream>
using namespace std;

void init(void);

void insert(int buffer_size, char *buf);

int query(int buffer_size, char *buf);

int main(void)
{
    freopen("3135.txt", "r", stdin);
    int TestCase;
    for (scanf("%d", &TestCase); TestCase--;)
    {
        int Query_N;
        scanf("%d", &Query_N);

        init();

        static int tc = 0;
        printf("#%d", ++tc);

        for (int i = 1; i <= Query_N; i++)
        {
            int type;
            scanf("%d", &type);

            if (type == 1)
            {
                char buf[15] = {
                    0,
                };
                scanf("%s", buf);

                int buffer_size = 0;
                while (buf[buffer_size])
                    buffer_size++;

                insert(buffer_size, buf);
            }
            else
            {
                char buf[15] = {
                    0,
                };
                scanf("%s", buf);

                int buffer_size = 0;
                while (buf[buffer_size])
                    buffer_size++;

                printf(" %d", query(buffer_size, buf));
            }
        }
        printf("\n");
        fflush(stdout);
    }
}

struct Tree
{
    int cnt;
    Tree *next[26];

    Tree *init()
    {
        cnt = 0;
        for (int i = 0; i < 26; i++)
        {
            next[i] = nullptr;
        }
        return this;
    }
} pool[1000000];

int poolCnt;
Tree *root;

void init(void)
{
    poolCnt = 0;
    root = pool[poolCnt++].init();
}

void insert(int buffer_size, char *buf)
{
    Tree *cur = root;
    for (int i = 0; i < buffer_size; i++)
    {
        int alphabet = buf[i] - 'a';
        if (cur->next[alphabet] == nullptr)
        {
            cur->next[alphabet] = pool[poolCnt++].init();
            cur->next[alphabet]->cnt = 0;
            for (int j = 0; j < 27; j++)
            {
                cur->next[alphabet]->next[j] = nullptr;
            }
        }
        cur->cnt++;
        cur = cur->next[alphabet];
    }
    cur->cnt++;
}

int query(int buffer_size, char *buf)
{
    Tree *cur = root;
    for (int i = 0; i < buffer_size; i++)
    {
        int alphabet = buf[i] - 'a';
        if (cur->next[alphabet] == nullptr)
        {
            return 0;
        }
        cur = cur->next[alphabet];
    }
    return cur->cnt;
}