#include <stdio.h>
#include <string.h>


// Structure to hold book details
typedef struct
{
    char title[100];
    char author[100];
    char language[50];
    char category[50];
    float buyPrice;
    float sellPrice;
    int stockQuantity;
} Book;



// Structure to hold sales record
typedef struct
{
    char title[100];
    int quantitySold;
    float buyPrice;
    float sellPrice;
} Sale;



// Global variables
Book books[100];
Sale sales[100];
int bookCount = 0;
int salesCount = 0;



// Function declarations
int login();
void addBook();
void searchBooks();
void displayBooks();
void sellBooks();
void updateBooks();
void salesTrack();
void deleteBook();
void loadBooksFromFile();
void saveBooksToFile();



// Main function
int main()
{
    int choice;
    printf("==== Book Store Management ====\n");

    if (!login())
    {
        printf("Invalid login! Exiting program...\n");
        return 0;
    }

    loadBooksFromFile(); // Load books from file on startup

    while (1)
    {
        printf("\n==== Main Menu ====\n");
        printf("1. Add Book\n");
        printf("2. Search & Filter Books\n");
        printf("3. Display Books\n");
        printf("4. Sell Books\n");
        printf("5. Update Books\n");
        printf("6. Sales Track\n");
        printf("7. Delete Book\n");
        printf("8. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            displayBooks();
            break;
        case 4:
            sellBooks();
            break;
        case 5:
            updateBooks();
            break;
        case 6:
            salesTrack();
            break;
        case 7:
            deleteBook();
            break;
        case 8:
            printf("Logging out...\n");
            saveBooksToFile(); // Save books to file on exit
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}





// Function to load books from a file
void loadBooksFromFile()
{
    FILE *file = fopen("books.txt", "r");
    
    if (file == NULL)
    {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%s,%s,%s,%s,%f,%f,%d\n",
                  books[bookCount].title,
                  books[bookCount].author,
                  books[bookCount].language,
                  books[bookCount].category,
                  &books[bookCount].buyPrice,
                  &books[bookCount].sellPrice,
                  &books[bookCount].stockQuantity) != EOF)
    {
        bookCount++;
    }
    fclose(file);
    printf("Loaded %d books from file.\n", bookCount);
}



// Function to save books to a file
void saveBooksToFile()
{
    FILE *file = fopen("books.txt", "w");

    if (file == NULL)
    {
        printf("Error saving data to file!\n");
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        fprintf(file,"Title: %s\n",books[i].title);
        fprintf(file,"Author: %s\n", books[i].author);
        fprintf(file,"language: %s\n",books[i].language);
        fprintf(file,"Category: %s\n",books[i].category);
        fprintf(file,"BuyPrice: %.2f\n",books[i].buyPrice);
        fprintf(file,"sellPrice: %.2f\n",books[i].sellPrice);
        fprintf(file,"stockQuantity: %d\n\n",books[i].stockQuantity);
    }

    fclose(file);
    printf("Data saved successfully.\n");
}



// Function to perform login
int login()
{
    char username[50], password[50];

    printf("LOGIN:\n");
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    return (strcmp(username, "mahmud") == 0 && strcmp(password, "394") == 0);
}



// Function to add a book
void addBook()
{
    if (bookCount >= 100)
    {
        printf("Book inventory is full!\n");
        return;
    }


    Book newBook;
    printf("Enter book title: ");
    getchar();
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    printf("Enter language: ");
    fgets(newBook.language, sizeof(newBook.language), stdin);
    newBook.language[strcspn(newBook.language, "\n")] = 0;

    printf("Enter category: ");
    fgets(newBook.category, sizeof(newBook.category), stdin);
    newBook.category[strcspn(newBook.category, "\n")] = 0;

    printf("Enter buy price: ");
    scanf("%f", &newBook.buyPrice);

    printf("Enter sell price: ");
    scanf("%f", &newBook.sellPrice);

    printf("Enter stock quantity: ");
    scanf("%d", &newBook.stockQuantity);

    books[bookCount++] = newBook;
    printf("Book added successfully!\n");


    saveBooksToFile();
}



// Function to search for books
void searchBooks()
{
    char query[100];

    printf("Enter title, author, or category to search: ");
    getchar();
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;

    printf("Search Results:\n");


    for (int i = 0; i < bookCount; i++)
    {
        if (strstr(books[i].title, query) || strstr(books[i].author, query) || strstr(books[i].category, query))
        {
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Language: %s\n", books[i].language);
            printf("Category: %s\n", books[i].category);
            printf("Sell Price: %.2f\n", books[i].sellPrice);
        }
    }
}

// Function to display all books
void displayBooks()
{
    printf("Book Inventory:\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("%d.\n", i + 1);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Language: %s\n", books[i].language);
        printf("Category: %s\n", books[i].category);
        printf("Buy Price: %.2f\n", books[i].buyPrice);
        printf("Sell Price: %.2f\n", books[i].sellPrice);
        printf("Stock: %d\n", books[i].stockQuantity);
    }
}



// Function to sell books
void sellBooks()
{
    char title[100];
    int quantity;
    printf("Enter book title to sell: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);

            if (quantity > books[i].stockQuantity)
            {
                printf("Not enough stock available!\n");
                return;
            }

            books[i].stockQuantity -= quantity;

            float totalPrice = quantity * books[i].sellPrice;

            // Record sale
            sales[salesCount].quantitySold = quantity;
            strcpy(sales[salesCount].title, books[i].title);
            sales[salesCount].sellPrice = books[i].sellPrice;
            sales[salesCount].buyPrice = books[i].buyPrice;
            salesCount++;

            printf("Sold %d copies of %s for %.2f.\n", quantity, books[i].title, totalPrice);

            saveBooksToFile();
            return;
        }
    }

    printf("Book not found!\n");
}



// Function to track sales


void salesTrack()
{
    printf("\n==== Sales Report ====\n");

    if (salesCount == 0)
    {
        printf("No sales recorded yet.\n");
        return;
    }

    printf("Title           Quantity Sold    Sell Price    Buy Price    Profit_Per_Book\n");
    printf("-----------------------------------------------------------------------------\n");

    float totalSellPrice = 0.0, totalBuyPrice = 0.0, totalProfit = 0.0;

    
    for (int i = 0; i < salesCount; i++)
    {
       
        float profitPerBook = sales[i].sellPrice - sales[i].buyPrice;

        
        totalSellPrice += sales[i].sellPrice * sales[i].quantitySold;

        
        totalProfit += profitPerBook * sales[i].quantitySold;

       
        printf("%-15s %-15d %-15.2f %-15.2f %.2f\n",
               sales[i].title, sales[i].quantitySold,
               sales[i].sellPrice, sales[i].buyPrice, profitPerBook);
    }
    for (int i = 0; i < bookCount; i++)
    {
        totalBuyPrice += (books[i].buyPrice * books[i].stockQuantity)+totalSellPrice; 
    }

    
    printf("--------------------------------------------------------------------\n");
    printf("Total Buy Price: %.2f\n", totalBuyPrice);  
    printf("Total Sell Price: %.2f\n", totalSellPrice); 
    printf("Total Profit: %.2f\n", totalProfit); 
}





// Function to update book quantity
void updateBooks()
{
    char title[100];
    int newQuantity;

    printf("Enter book title to update: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            printf("Enter new stock quantity: ");
            scanf("%d", &newQuantity);

            books[i].stockQuantity = newQuantity;
            printf("Updated stock quantity for %s to %d\n", books[i].title, newQuantity);


            saveBooksToFile();
            return;
        }
    }

    printf("Book not found!\n");
}



// Function to delete a book
void deleteBook()
{
    char title[100];
    printf("Enter book title to delete: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            for (int j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1];
            }
            bookCount--;

            printf("Book '%s' deleted successfully!\n", title);


            saveBooksToFile();
            return;
        }
    }


    printf("Book not found!\n");
}
