#include <stdio.h>
#include <sqlite3.h>

void executeSafeQuerySQLite(const char* userInput) {
    sqlite3 *db;
    sqlite3_stmt *res;
    
    // Open database connection (replace 'example.db' with your database file)
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    // Prepare a parameterized query
    const char *sql = "SELECT * FROM Users WHERE name = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) != SQLITE_OK) {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    } else {
        // Bind the user input to the parameter (parameter indexes start from 1)
        sqlite3_bind_text(res, 1, userInput, -1, SQLITE_STATIC);
        
        // Execute and iterate over the results
        while (sqlite3_step(res) == SQLITE_ROW) {
            printf("User found: %s\n", sqlite3_column_text(res, 0)); // Adjust column index as needed
        }
        
        // Clean up
        sqlite3_finalize(res);
    }
    
    sqlite3_close(db);
}
