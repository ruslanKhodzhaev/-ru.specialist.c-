#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <stdbool.h>

struct product {
	char name[30];
	int qnt;
	float price;
};

int create_shop_by_filepath (struct product ** shop, char filepath[])
{
	FILE * f;
	f = fopen(filepath, "r");
	
	if (f == NULL) 
	{
		printf("File not found!");
		exit(99);
	}
	
	int product_array_size = 1, iterations_count = 0;
	* shop = (struct product *) malloc(product_array_size * sizeof(struct product));

	do
	{
		fscanf(f, "%s", &(*shop + iterations_count) -> name);
		fscanf(f, "%d", &(*shop + iterations_count) -> qnt);
		fscanf(f, "%f", &(*shop + iterations_count) -> price);
		iterations_count++;
		product_array_size++;
		* shop = (struct product *) realloc (*shop, product_array_size * sizeof(struct product));
	} while (getc(f) != EOF);

	fclose(f);
	
	return iterations_count;
}

void print_shop (struct product * p, int qnt_products)
{
	int i;
	for(i = 0; i < qnt_products; i++)
	{
		printf("\n%d. %s ", i + 1, (p + i) -> name);
		printf("\t%d", (p + i) -> qnt);
		printf("\t%.2f", (p + i) -> price);
	}
}

float calculate_total_price (struct product * p, int qnt_products)
{
	int i;
	float total_price = 0;
	for(i = 0; i < qnt_products; i++)
		total_price += (p+i) -> qnt * (p+i) -> price;
	return total_price;
}

void find_product_by_name(struct product * shop, char product_name[], int qnt_products)
{
	int i;
	bool product_is_found = false;
	for(i = 0; i < qnt_products; i++)
	{
		if (strcmp(product_name, (shop+i) -> name) == 0) 
		{
			printf("\nPrice is. %.2f ", (shop + i) -> price);
			product_is_found = true;
		}
	}
	if (!product_is_found)
	{
		printf("\nProduct not found!");
	}
}

void write_shop_to_file(struct product * shop, char filepath[], int qnt_products)
{
	int i;
	FILE * fout;
	fout = fopen(filepath, "w");
	
	if (fout != NULL) 
	{
		for(i = 0; i < qnt_products; i++)
		{
			fputs(&(shop + i) -> name, fout);
			fputs("\n", fout);
		}
		fclose(fout);
		printf("\Copying successful!");
	} else 
		printf("\Directory not found!");
}


int main()
{
	int qnt_products;
	char input_string[30];
	struct product * shop;
	
	printf("\nInput filepath with filename (char 30): ");
	gets(input_string);
	
	qnt_products = create_shop_by_filepath(&shop, input_string);
		
	print_shop(shop, qnt_products);
	
	printf("\nsum is\t%.2f", calculate_total_price (shop, qnt_products));
	
	printf("\n\nInput name of product\t");
	gets(input_string);
	
	find_product_by_name(shop, input_string, qnt_products);
	
	printf("\nProcess of copying the products name is ready. Input target filename with filepath. If file not exist, it'll be created.\n");
	gets(input_string);
	
	write_shop_to_file(shop, input_string, qnt_products);

	free(shop);
	
	return 0;
}

