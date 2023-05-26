#include <stdio.h>

#define MAX_TREE_HT 100

struct MinHeapNode {

    char data;
    unsigned frequency;
    struct MinHeapNode *left, *right;
};

struct MinHeap {

    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned frequency)
{
    struct MinHeapNode* temp= (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->frequency = frequency;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{

    struct MinHeap* minHeap=(struct MinHeap*)malloc(sizeof(struct MinHeap));minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
        = (struct MinHeapNode**)malloc(minHeap->
capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b)
{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int index)

{

    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}


struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}


void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}


int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {

        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top)

{

    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
void HuffmanCodes(char data[], int freq[], int size)

{
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}


int main()
{
    int choice;
    printf("Enter your  option (1-encode/ 2-decode): ");
    scanf("%d",&choice);
    if(choice==1)
    {
        char destination[51];
        char source[51];
        printf("Enter the name of the DESTINATION file (encoded file): ");
        scanf("%s",destination);
        printf("Enter the name of the SOURCE file (to be encoded): ");
        scanf("%s",source);
        FILE *output = fopen(destination,"w+");
        FILE *input = fopen(source,"r");
        char strin[10000];
        fgets(strin,10000,input);
        char arr[8];
        int freq[8];
        int  i,j,k,count=0,n;
        for(j=0;strin[j];j++);
        n=j;

        for(i=0;i<n;i++)
        {
            count=1;
            if(strin[i])
            {
                arr[i]=strin[i];
                for(j=i+1;j<n;j++)
                {

                    if(strin[i]==strin[j])
                    {
                        count++;
                        strin[j]='\0';
                    }
                }
                freq[i]=count;
                printf("(%c, %d) \n",strin[i],count);
            }
        }
        char strout[10000];
        fprintf(output,"Huffman Tree Encoding Huffman File Encoding");

        fclose(output);
        fclose(input);
        return 0;
    }
    else if(choice==2)
    {
        char destination[51];
        printf("Enter the name of the DESTINATION file (encoded file): ");
        scanf("%s",destination);
        FILE *input = fopen(destination,"r");
        char strin[10000];
        fgets(strin,10000,input);
        char strout[10000];
        printf("decoded string: %s",strout);
        fclose(input);
        return 0;
    }
    else
    {
        printf("Invalid Option\n");
        return 0;

    }
}
