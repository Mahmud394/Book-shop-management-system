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

// Global variables
Book books[100];
int bookCount = 0;
float totalProfit = 0.0;

// Function declarations
int login();
void addBook();
void searchBooks();
void displayBooks();
void sellBooks();
void updateBooks();
void salesTrack();

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

    while (1)
     {
        printf("\n==== Main Menu ====\n");
        printf("1. Add Book\n");
        printf("2. Search & Filter Books\n");
        printf("3. Display Books\n");
        printf("4. Sell Books\n");
        printf("5. Update Books\n");
        printf("6. Sales Track\n");
        printf("7. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
         {
            case 1: addBook(); break;
            case 2: searchBooks(); break;
            case 3: displayBooks(); break;
            case 4: sellBooks(); break;
            case 5: updateBooks(); break;
            case 6: salesTrack(); break;
            case 7: printf("Logging out...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
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
    if (bookCount >= 100) {
        printf("Book inventory is full!\n");
        return;
    }
    Book newBook;
    printf("Enter book title: ");
    getchar(); // Clear newline buffer
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline

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

    printf("Sell price: ");
    scanf("%f",&newBook.sellPrice);

    printf("Enter stock quantity: ");
    scanf("%d", &newBook.stockQuantity);

    
    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
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
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, query) || strstr(books[i].author, query) || strstr(books[i].category, query))
         {
            // printf("%d", i + 1 );
            printf("Title: %s\n",books[i].title);
            printf("Author: %s\n",books[i].author);
            printf("Language: %s\n",books[i].language);
            printf("Category: %s\n",books[i].category);
            printf("Sell Price:- %.2f\n",books[i].sellPrice);
        }
    }
}

// Function to display all books
void displayBooks()
 {
    printf("Book Inventory:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d.",i + 1);
             printf("Title: %s\n",books[i].title);
            printf("Author: %s\n",books[i].author);
            printf("Language: %s\n",books[i].language);
            printf("Category: %s\n",books[i].category);
            printf("Buy Price: %.2f\n",books[i].buyPrice);
            printf("Sell Price: %.2f\n",books[i].sellPrice);
            printf("Stock: %d\n",books[i].stockQuantity);
    }
}

// Function to sell books
void sellBooks()
 {
    char title[100];
    int quantity;
    printf("Enter book title to sell: ");
    getchar(); // Clear newline buffer
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);
            if (quantity > books[i].stockQuantity) {
                printf("Not enough stock available!\n");
                return;
            }
            books[i].stockQuantity -= quantity;
            float totalPrice = quantity * books[i].sellPrice;
            totalProfit += totalPrice - (quantity * books[i].buyPrice);
            printf("Sold %d copies of %s for %.2f\n", quantity, books[i].title, totalPrice);
            return;
        }
    }
    printf("Book not found!\n");
}

// Function to update book quantity
void updateBooks()
 {
    char title[100];
    int newQuantity;
    printf("Enter book title to update: ");
    getchar(); // Clear newline buffer
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
            return;
        }
    }
    printf("Book not found!\n");
}

//Function to track sales
void salesTrack()
 {
    printf("Total profit: %.2f\n", totalProfit);
    
}


