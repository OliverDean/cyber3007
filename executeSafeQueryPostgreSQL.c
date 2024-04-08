#include <stdio.h>
#include <libpq-fe.h>

void executeSafeQueryPostgreSQL(const char* userInput) {
    PGconn *conn;
    PGresult *res;
    
    // Connect to the database (adjust connection info accordingly)
    conn = PQconnectdb("user=username dbname=mydatabase");
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return;
    }
    
    // Prepare and execute a parameterized query
    const char *paramValues[1] = { userInput };
    res = PQexecParams(conn,
                       "SELECT * FROM Users WHERE name = $1",
                       1,       /* number of params */
                       NULL,    /* param types (let the backend deduce) */
                       paramValues,
                       NULL,    /* param lengths (not needed for text types) */
                       NULL,    /* param formats (text) */
                       0);      /* result format (text) */
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved\n");        
        PQclear(res);
        PQfinish(conn);
        return;
    }
    
    // Process results
    for (int i = 0; i < PQntuples(res); i++) {
        printf("User found: %s\n", PQgetvalue(res, i, 0)); // Adjust column index as needed
    }
    
    // Clean up
    PQclear(res);
    PQfinish(conn);
}
