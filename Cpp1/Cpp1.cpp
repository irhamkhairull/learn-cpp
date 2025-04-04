#include <stdio.h>
main()
{
	// Declare and initialize variables
	char header1[5], header2[5], header3[10], header4[10], header5[5], header6[5], header7[10];
	char receipt[10], ITEM[100][20], item[100][20];
	int ID[50], STOCK[50], id[100], i=0, j, l, m;
	float PRICE[50], price[100], sales, overallsales=0.0;
	
	// Display welcome message
	printf("=========WELCOME TO SMART ENTERPRISE=========\n\n");
	printf("---------------------------------------------\n\n");
	
	// Open product file to read and check if the file exist
	FILE *abc=fopen("product.txt", "r");
	if(abc==NULL)
	{
		printf("Error: product.txt\n");
	}
	
	// Load headers from product file
	fscanf(abc, "%s %s %s %s", header1, header2, header3, header4);
	
	// Load product data into arrays
	while(fscanf(abc, "%d %s %f %d", &ID[i], ITEM[i], &PRICE[i], &STOCK[i])!=EOF)
	{
		i++; // Increment product index
	}
	fclose(abc); // Close the product file
	
	// Open all receipt file to read and check if the file exist
	for(j=1; j<6; j++)
	{
		int k=0, sold[30]={0};
		float totalsales=0.0;
		
		// Format receipt file name (e.g., receipt_1)
		sprintf(receipt, "receipt_%d.txt", j);
		FILE *def=fopen(receipt, "r");
		
		// Check if the receipt file exists
		if(def==NULL)
		{
			printf("Error: %s\n", receipt);
			continue; // Execute next iteration of loop if the file doesn't exist
		}
		
		// Load data from all receipt file
		fscanf(def, "%s %s %s", header5, header6, header7);
		while(fscanf(def, "%d %s %f", &id[k], item[k], &price[k])!=EOF)
		{
			for(l=0; l<i; l++)
			{
				if(id[k]==ID[l])
				{
					STOCK[l]--;
					sold[l]++;
				}
			}
			k++;
		}
		fclose(def);
		
		// Display the details for all receipt file
		printf("Summary of %s:\n", receipt);
		printf("%-10s%-20sQuantity\tTotal\n", header1, header2);
		for(m=0; m<i; m++)
		{
			if(sold[m]>0)
			{
				sales=sold[m]*PRICE[m]; // Calculate sales for each item
				totalsales=totalsales+sales; // Accumulate total sales for each receipt
				printf("%-10d%-20s%-10d%-10.2f\n", ID[m], ITEM[m], sold[m], sales);
			}
		}
		printf("Total sales for %s: RM%.2f\n\n", receipt, totalsales);
		overallsales=overallsales+totalsales; // Accumulate overall sales across all receipts
	}
	
	// Display overal sales summary
	printf("Overall sales for all receipt: RM%.2f\n\n", overallsales);
	printf("---------------------------------------------\n\n");
	
	// Display final stocks for all items
	printf("Balance quantities for each item:\n");
	printf("%-10s%-20s%-10s\n", header1, header2, header4);
	for(m=0; m<i; m++)
	{
		printf("%-10d%-20s%-10d\n", ID[m], ITEM[m], STOCK[m]);
	}
	for(m=0; m<i; m++)
	{
		if(STOCK[m]<7)
		{
			printf("\nALERT! Item %d(%s) has low stocks.", ID[m], ITEM[m]);
		}
	}
	printf("\n");
}
