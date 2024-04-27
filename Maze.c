#include<stdio.h>
#include<stdlib.h>

struct enode
{
	int v;
	struct enode *next;
};

struct node
{
	int size;
	struct enode *head;
	struct enode *tail;
};

struct graph
{
	int n;
	struct node *adjList[144];
};

struct queue
{
    int *arr;
    int size;
    int front;
    int rear;
};

typedef struct queue que;
que* createQueue()
{
    que *q = (que *)malloc(sizeof(que));
    q->arr = (int *)malloc(4*sizeof(int));
    q->size = 4;
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(que *q)
{
    int s = -1;
    if(q->rear == -1 && q->front == -1){
        s = 0; //queue is empty    
    }
    return s;
}

void enqueue(que *q, int e)
{
    int isempty = isEmpty(q);
    if(isempty == 0)
    {//printf("%d",e);
        //q is empty case
        q->front = q->rear = 0;
        q->arr[q->rear] = e;
    }
    //q is full
    else if((q->front == 0 && q->rear == q->size-1) || (q->front == q->rear + 1))
    {
      //  printf("QF QSD ");
        int *temp = q->arr;
        q->arr = malloc(2*q->size*sizeof(int));
        for(int i = 0;i < q->size;i++){
            q->arr[i] = temp[(q->front + i) % q->size];
        }
        free(temp);
        q->front = 0;
        q->rear = q->size - 1;
        q->size = 2*q->size;
        q->rear = q->rear + 1;
        q->arr[q->rear] = e;
    }
    //q neither empty nor full
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->arr[q->rear] = e;
        
    }
}

int dequeue(que *q)
{
    int e;
    //q empty
    if(isEmpty(q) == 0)
    {
       // printf("QE ");
    }
    //single element
    else if(q->front == q->rear)
    {
        e = q->arr[q->front];
        q->front = q->front - 1;
        q->rear = -1;
        q->front = -1;
      //  printf("%d ",e);
    }
    //more than one element
    else
    {
        e = q->arr[q->front];
        q->front = (q->front + 1) % q->size;
     //   printf("%d ",e);
        
    }
    
    return e;
    
}

struct graph *createGraph(struct graph *g)
{
	g=(struct graph *)malloc(sizeof(struct graph));
	g->n=144;
	for(int i=0;i<144;i++)
	{
		g->adjList[i]=NULL;
	}
	return g;
}

struct graph *addEdge(struct graph *g,int u,int v)
{
	if(g->adjList[u] == NULL)
	{
		g->adjList[u]=(struct node *)malloc(sizeof(struct node));
		g->adjList[u]->size=1;
		g->adjList[u]->head=(struct enode*)malloc(sizeof(struct enode));
		g->adjList[u]->head->v=v;
		g->adjList[u]->head->next=NULL;
		g->adjList[u]->tail=g->adjList[u]->head;
	}
	else
	{
		g->adjList[u]->size++;
		g->adjList[u]->tail->next=(struct enode*)malloc(sizeof(struct enode));
		g->adjList[u]->tail->next->v=v;
		g->adjList[u]->tail=g->adjList[u]->tail->next;
		g->adjList[u]->tail->next=NULL;
	}
	return g;
}

void printGraph(struct graph *g)
{
	for(int i=0;i<144;i++)
	{
		printf("%d : ",i);
		if(g->adjList[i]!=NULL)
		{
			printf("%d ",g->adjList[i]->head->v);
		}
		printf("\n");
	}
}

int BFS(struct graph *g,int s)
{
	struct queue *q = createQueue();
	int visited[144];
	for(int i = 0; i < 144; i++)
	{
		visited[i] = 0;
	}
	int path[12][12];
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			path[i][j]=0;
		}
	}
	
	enqueue(q, s);
	visited[s] = 1;
	while(isEmpty(q)!=0)
	{
		int u = dequeue(q);//printf("%d ",u);
		visited[u]=1;
		int ui=u/12;
		int uj=u%12;
		if(uj==11)
		{
			return path[ui][uj];
		}
		if(g->adjList[u]!=NULL)
		{
			while(g->adjList[u]->head!=NULL)
			{if(visited[g->adjList[u]->head->v]!=1)
				enqueue(q,g->adjList[u]->head->v);
				int vi=g->adjList[u]->head->v/12;
				int vj=g->adjList[u]->head->v%12;
				if(visited[g->adjList[u]->head->v]!=1)
					path[vi][vj]=path[ui][uj]+1;
				//visited[g->adjList[u]->head->v]=1;
				g->adjList[u]->head=g->adjList[u]->head->next;
			}
		}
	}
	return -2;
}

int path(struct graph *g,int x,int y)
{
	int count = BFS(g,x);
	return count;
}

int main(int argc, const char * argv[])
{
	FILE *fptr;
	fptr=fopen(argv[1],"r");
	char maze[13][12];
	for(int i=0;i<12;i++)
	{
		fscanf(fptr,"%s",maze[i]);
	}
	int convertMaze[12][12];
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			if(maze[i][j]=='.')
			{
				convertMaze[i][j]=1;
			}
			else if(maze[i][j]=='#')
			{
				convertMaze[i][j]=0;
			}
		}
	}
	
	struct graph *g;
	g = createGraph(g);
	int c=-1;
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			c++;
			if(convertMaze[i][j]==1)
			{
				if((i-1)>=0 && convertMaze[i-1][j]==1)
				{
					g=addEdge(g,c,c-12);
					g=addEdge(g,c-12,c);
				}
				if((i+1)<=11 && convertMaze[i+1][j]==1)
				{
					g=addEdge(g,c,c+12);
					g=addEdge(g,c+12,c);
				}
				if((j-1)>=0 && convertMaze[i][j-1]==1)
				{
					g=addEdge(g,c,c-1);
					g=addEdge(g,c-1,c);
				}
				if((j+1)<=11 && convertMaze[i][j+1]==1)
				{
					g=addEdge(g,c,c+1);
					g=addEdge(g,c+1,c);
				}
			}
		}
	}
	
	int x;
	for(int i=0;i<12;i++)
	{
		if(convertMaze[i][0]==1)
		x= i*12+i;
	}
	int y;
	for(int i=0;i<12;i++)
	{
		if(convertMaze[i][11]==1)
		y=i*12+i;
	}
	//printGraph(g);
	int steps=path(g,x,y);//printf("%d %d \n",x,y);
	printf("%d\n",steps+1);
	return 0;
}
