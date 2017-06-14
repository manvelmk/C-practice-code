#include <stdio.h>
#include <stdlib.h>

/* Define page table as dynamic structure containing virtual page and page frame
and initialize variable as pointer to structure */
struct node{
	int vp;
	int pf;
}
*PT = NULL;
typedef struct node PageTable;

/* Declare global vars */
int memSize, pageSize, pageTableSize, repPolicy = 0;

void enterParams(){
	/* Prompt for main memory size, page size, and replacement policy */
	printf("Enter main memory size (words): ");
	scanf("%d", &memSize);
	printf("Enter page size (words/page): ");
	scanf("%d", &pageSize);
	printf("Enter replacement policy (0=LRU, 1=FIFO): ");
	scanf("%d", &repPolicy);

	pageTableSize = memSize / pageSize;

	/* Allocate and initialize page table based on number of entries */
	PT = (PageTable*)malloc(pageTableSize * sizeof(PageTable));
	int i;
	for (i = 0; i < pageTableSize; i++)
	{
		PT[i].vp = -1;
	}
	return;
}

void drawTable()
{
	printf("-----------------\n| VP	| PF	|\n-----------------\n");
	for (int i = 0; i < pageTableSize; i++)
	{
		if (PT[i + 1].vp == -1) break;
		printf("| %d	| %d	|\n", PT[i].vp, PT[i].pf);
		printf("-----------------\n");
	}
	return;
}

void mapVirtAddr(){
	/* Declare local var's */
	int addrAccess, virtPage, offset = 0;

	/* Prompt for virtual address */
	printf("Enter virtual memory address to access: ");
	scanf("%d", &addrAccess);

	/* Translate virtual mem addr to virtual page and offset*/
	virtPage = addrAccess / pageSize;
	offset = addrAccess % pageSize;

	int index = 0;
	while ((index < pageTableSize) && (PT[index].vp != -1) && (PT[index].vp != virtPage))
		index++;

	if (index == pageTableSize)
	{
		printf("Page fault!\n");
		int i;
		int pf = PT[0].pf;
		for (i = 0; i <= pageTableSize - 2; i++)
		{
			PT[i].vp = PT[i + 1].vp;
			PT[i].pf = PT[i + 1].pf;
		}
		PT[pageTableSize - 1].vp = virtPage;
		PT[pageTableSize - 1].pf = pf;
	}
	
	else if (PT[index].vp == -1)
	{
		printf("Page fault!\n");
		PT[index].vp = virtPage;
		PT[index].pf = index;
	}
	/* In case of hit in page table, calculate physical address and print message */
	else
	{
		//for FIFO
		int tempPageFrame = PT[index].pf;
		//for LRU
		if (repPolicy == 0) {
			int i;
			for (i = index; i < pageTableSize - 1; i++)
			{
				if (PT[i + 1].vp == -1) break;
				PT[i] = PT[i + 1];
			}
			PT[i].vp = virtPage;
			PT[i].pf = tempPageFrame;
		}

		int physAddress = tempPageFrame * pageSize + offset;
		printf("Virtual address %d maps to physical address %d \n", addrAccess, physAddress);
	}
	/* Print out current state of page table */
	drawTable();
	return;
}


int main()
{
	/* Declare local var's */
	int input = 0;

	/* Until user quits, print menu of options, prompt for user input, and select appropriate option */
	while (input <= 3)
	{
		printf("\nVirtual memory to Main memory mapping:\n");
		printf("--------------------------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Map virtual address\n");
		printf("3) Quit \n");
		printf("\nEnter selection: ");

		scanf("%d", &input);
		switch (input)
		{
		case 1: enterParams();
			break;
		case 2: mapVirtAddr();
			break;
		case 3:
			return;
		default:
			printf("\nInvalid input, try again.\n");
			input = 0;
			break;
		}
	}
	return 1;
}